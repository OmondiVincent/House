#ifndef WX_CLIENT
#define WX_CLIENT

    #include <boost/asio.hpp>
    #include <boost/core/noncopyable.hpp>
    #include <boost/system/error_code.hpp>
    #include <thread>
    #include <mutex>
    #include <memory>
    #include <iostream>
    #include <string>

    typedef void(*Callback) (unsigned int request_id, const std::string& response, const boost::system::error_code& ec);

    struct Session {

        Session(boost::asio::io_service& ios, const std::string& raw_ip_address,unsigned short port_num, const std::string& request,unsigned int id, Callback callback) : m_sock(ios),
        m_ep(boost::asio::ip::address::from_string(raw_ip_address), port_num),
        m_request(request),
        m_id(id),
        m_callback(callback),
        m_was_cancelled(false) {}
        boost::asio::ip::tcp::socket m_sock; // Socket used for communication
        boost::asio::ip::tcp::endpoint m_ep; // Remote endpoint.
        std::string m_request; // Request string.
        
        boost::asio::streambuf m_response_buf; // streambuf where the response will be stored.
        std::string m_response; // Response represented as a string.
        
        
        boost::system::error_code m_ec; // Contains the description of an error if one occurs during
                                // the request life cycle.
        unsigned int m_id; // Unique ID assigned to the request.
        // Pointer to the function to be called when the request
        // completes.
        Callback m_callback;
        bool m_was_cancelled;
        std::mutex m_cancel_guard;
    };

    class Client : public boost::noncopyable

    {
        private:
        
            boost::asio::io_service m_ios;
            std::map<int, std::shared_ptr<Session>> m_active_sessions;
            std::mutex m_active_sessions_guard;
            std::unique_ptr<boost::asio::io_service::work> m_work;
            std::unique_ptr<std::thread> m_thread;
            
        public:
            Client();
            ~Client();
            void emulateLongComputationOp(unsigned int duration_sec, const std::string& raw_ip_address, 
                                       unsigned short port_num, Callback callback,unsigned int request_id);
            void cancelRequest(unsigned int request_id);
            void close();
                                       
        private:
            void onRequestComplete(std::shared_ptr<Session> session);
    };
    
#endif
