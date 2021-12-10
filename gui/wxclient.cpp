#include "wxclient.h"

Client::Client()
{
     m_work.reset(new boost::asio::io_service::work(m_ios)); //initiates an object of the asio::io_service::work class passing an
                                                             // instance of the asio::io_service class named m_ios to its constructor
                                                             
                                                             
    // Then, it spawns a thread that calls the run() method
    //of the m_ios object. The object of the asio::io_service::work class keeps threads
    //running event loop from exiting this loop when there are no pending asynchronous operations.
    // The spawned thread plays the role of I/O thread in our application
    
     m_thread.reset(new std::thread([this](){ //pass a lamda function as an argument to the constructor
                           m_ios.run();
                    }));
                    
    std::cout << "Hello" << std::endl;
}

Client::~Client()
{
    //
}

//initiates an asynchronous request 
void Client::emulateLongComputationOp(unsigned int duration_sec, const std::string& raw_ip_address, 
                                      unsigned short port_num, Callback callback,unsigned int request_id)
                                      
{

    // Preparing the request string.
    std::string request = "EMULATE_LONG_CALC_OP " + std::to_string(duration_sec)+ "\n";
    
    //allocates an instance of the Session structure that keeps the data associated with the
    //request including a socket object that is used to communicate with the server.
    std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(m_ios, raw_ip_address, port_num,request,request_id,callback));
    
    //opens the connection 
    session->m_sock.open(session->m_ep.protocol());
    
   
    std::unique_lock<std::mutex> lock(m_active_sessions_guard); //locks the mutex
    
    //Session object is added to the m_active_sessions map
    // The request_id argument is used as a key of the corresponding Session object added
    //to the map.
    m_active_sessions[request_id] = session;
    lock.unlock(); //unlocks the mutex
    
    //responsible for creating connection to the server 
    //receives two argument, an endpoint and a lambda which is a callback
    //function to be called when the connection is complete or an error occurs
    session->m_sock.async_connect(session->m_ep,[this, session](const boost::system::error_code& ec)
            {
                if (ec.value() != 0) { //any error code which is not 0 mean the connection has failed
                    session->m_ec = ec; //stores the ec to the session->m_ec object
                    onRequestComplete(session); //call the onRequestComplete private function and passing
                                                //session as an argument
                    return;
                }
                
                //If the ec object designates success, we lock the m_cancel_guard mutex (the member
                //of the request descriptor object) and check whether the request has not been canceled yet
                std::unique_lock<std::mutex>cancel_lock(session->m_cancel_guard);
                
                if (session->m_was_cancelled) { //checks if the request was canceled 
                    onRequestComplete(session); // if it is canceled calls the OnRequestComplete private function and
                                                // we pass session as an argument
                    return;
                }
                
                //if the request is not canceled , initiates the next asynchronous operation calling the
                // Boost.Asio free function async_write() to send the request data to the server
                //receives 2 arguments, 1 the socket, the 2 is a lambda which is a callback function
                
                boost::asio::async_write(session->m_sock, boost::asio::buffer(session->m_request),[this, session](const boost::system::error_code& ec, std::size_t bytes_transferred)
                {
                    if (ec.value() != 0) { //checks the error code 
                        session->m_ec = ec; //stores the ec to the session->m_ec object
                        onRequestComplete(session);
                        return;
                    }
                    
                    //checks on the error code if it indicates success, checks whether or not the request has been canceled
                    std::unique_lock<std::mutex>cancel_lock(session->m_cancel_guard);
                    
                    if (session->m_was_cancelled) { //check whether or not the request has been canceled
                        onRequestComplete(session);
                        return;
                    }
                    
                    //if the request has not been canceled, initiates the next asynchronous
                    // operation—async_read_until() —in order to receive a response from the server
                    //It checks the error code and in the case of success, it stores the received response data in
                    //the corresponding Session object. Then, the onRequestComplete() is called and the Session object
                    // is passed to it as an argument.
                    boost::asio::async_read_until(session->m_sock,session->m_response_buf, '\n', [this, session](const boost::system::error_code& ec, std::size_t bytes_transferred)
                    {
                        if (ec.value() != 0) {
                            session->m_ec = ec;
                        } else {
                            std::istream strm(&session->m_response_buf);
                            std::getline(strm, session->m_response);
                        }
                        onRequestComplete(session);
                        
                    });
               });
        });
}
             
            
void Client::onRequestComplete(std::shared_ptr<Session> session) {
    // Shutting down the connection. This method may
    // fail in case socket is not connected. We don’t care
    // about the error code if this function fails.
    boost::system::error_code ignored_ec;


     session->m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
    // Remove session form the map of active sessions.
    std::unique_lock<std::mutex>lock(m_active_sessions_guard);

    auto it = m_active_sessions.find(session->m_id);
    if (it != m_active_sessions.end())
        m_active_sessions.erase(it);
    lock.unlock();
    boost::system::error_code ec;
    if (session->m_ec.value() == 0 && session->m_was_cancelled)
        ec = boost::asio::error::operation_aborted;
    else
        ec = session->m_ec;
    // Call the callback provided by the user.
    session->m_callback(session->m_id, session->m_response, ec);  
}   

void Client::cancelRequest(unsigned int request_id) {

    std::unique_lock<std::mutex> lock(m_active_sessions_guard);
    auto it = m_active_sessions.find(request_id);
    if (it != m_active_sessions.end()) {
        std::unique_lock<std::mutex>
        cancel_lock(it->second->m_cancel_guard);
        it->second->m_was_cancelled = true;
        it->second->m_sock.cancel();
    }
}
void Client::close() {
    // Destroy work object. This allows the I/O thread to
    // exits the event loop when there are no more pending
    // asynchronous operations.
    m_work.reset(NULL);
    // Wait for the I/O thread to exit.
    m_thread->join();
} 


void handler(unsigned int request_id,const std::string& response,const boost::system::error_code& ec)
{
    if (ec.value() == 0) {
        std::cout << "Request #" << request_id << " has completed. Response: " << response << std::endl;
    } else if (ec == boost::asio::error::operation_aborted) {
        std::cout << "Request #" << request_id << " has been cancelled by the user." << std::endl;
    } else {
        std::cout << "Request #" << request_id << " failed! Error code = " << ec.value()
                    << ". Error message = " << ec.message() << std::endl;
    }
    return;
}                               
                          
               
                                      

/*int main()
{
    try {
        Client client;
        // Here we emulate the user's behavior.
        // User initiates a request with id 1.
        client.emulateLongComputationOp(10, "127.0.0.1", 3333, handler, 1);
        // Then does nothing for 5 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Then initiates another request with id 2.
        client.emulateLongComputationOp(11, "127.0.0.1", 3334, handler, 2);
        // Then decides to cancel the request with id 1.
        client.cancelRequest(1);
        // Does nothing for another 6 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(6));
        // Initiates one more request assigning ID3 to it.
        client.emulateLongComputationOp(12, "127.0.0.1", 3335,
        handler, 3);
        // Does nothing for another 15 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(15));
        // Decides to exit the application.
        client.close();
        }
    catch (boost::system::system_error &e) {
        std::cout << "Error occured! Error code = " << e.code()
        << ". Message: " << e.what();
        return e.code().value();
        } 
        return 0;
   
}*/































