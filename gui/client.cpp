#ifndef CLIENT_H
#define CLIENT_H

    #include <boost/asio.hpp>
    #include <string>
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <iterator>
    #include <algorithm>
    #include <wx/dialog.h>
    #include <wx/msgdlg.h>

    enum {
        IDX_BACKUP =9765,
        IDX_RESTORE = 9766,
        IDX_LICENCE = 9767,
        IDX_CHECK_LICENCE = 9768

    };

    struct Session {
        std::shared_ptr<boost::asio::ip::tcp::socket> sock;
        std::string buf;
    };

   inline std::string get_user_info(int request_id){

        std::string id = std::to_string(request_id);
        std::string txt = "***+" + std::string("Userid6547a+");
        return txt + id + "+asa}}";

    }

    inline void callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s)
        {
        if (ec.value() != 0) {
        std::cout << "Error occured! Error code = "
        << ec.value()
        << ". Message: " << ec.message();
        return;
        } else {
            std::cout << s->buf.size() << std::endl;
        }
    // Here we know that all the data has
    // been written to the socket.
    }

    inline void writeToSocket(std::shared_ptr<boost::asio::ip::tcp::socket> sock, int request_id) {
        std::shared_ptr<Session> s(new Session);
        // Step 4. Allocating and filling the buffer.

        //read the database file in memory as binary data
        std::ifstream file("/home/alan/House/gui/build/fileowner.db", std::ios::binary );
        std::vector<char> txtvec;

        std::ostringstream data;

        //copy the binary data into vector char
        std::copy( 
            std::istreambuf_iterator<char>(file), 
            std::istreambuf_iterator<char>( ),
            std::back_inserter(txtvec));

        std::ostringstream out;
        for (char c: txtvec) {
            out << c;
        }

        std::string txt(out.str());
        
        std::string tx = get_user_info(request_id);
        
        s->buf = txt + tx;
        //std::string("Hello");
        s->sock = sock;

        std::cout << txtvec.size() << std::endl;
        // Step 5. Initiating asynchronous write operation.
        boost::asio::async_write(*sock, boost::asio::buffer(s->buf), std::bind(callback, std::placeholders::_1, 
            std::placeholders::_2, s));
    }
    /**********************************************************************************/


    inline void restore_callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s)
    {
        if (ec.value() != 0) {
            wxMessageBox(wxT_2(ec.message()), wxT("Error"));
        return;
        
        } else {
            

            std::vector<char> v;

            std::copy(s->buf.begin(), s->buf.end(), std::back_inserter(v));

            //writes the content of vector char to fileowner.db 
            std::ofstream output( "fileowner1.db", std::ios::binary );

            std::copy(v.begin(), v.end(), std::ostreambuf_iterator<char>(output));

            wxMessageBox(wxT("Restore Complete\nplease restart \nthe application"), wxT("Success"));
        }
    }

    inline void restore(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
    {
        std::shared_ptr<Session> s(new Session);
        
        
        boost::asio::async_read_until(*sock, boost::asio::dynamic_buffer(s->buf), "}", std::bind(restore_callback, std::placeholders::_1, 
            std::placeholders::_2, s));      
        
    }

    /******************************************* check licence*************************************************************************/

    inline void check_licence_callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s)
    {
        if (ec.value() != 0) {
            wxMessageBox(wxT_2(ec.message()), wxT("Error"));
        return;
        
        } else {
            wxMessageBox(wxT_2(s->buf), wxT("Feedback"));
        }
    }

    inline void check_licence(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
    {
        std::shared_ptr<Session> s(new Session);
        
        
        boost::asio::async_read_until(*sock, boost::asio::dynamic_buffer(s->buf), "}", std::bind(check_licence_callback, std::placeholders::_1, 
            std::placeholders::_2, s));
            
          
        
    }


    /**********************************************renew licence **********************************************************************/

    inline void renew_licence_callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s)
    {
        if (ec.value() != 0) {
            wxMessageBox(wxT_2(ec.message()), wxT("Error"));
        
        } else {
            
            
            std::cout << "Done reading data" << std::endl;

            std::vector<char> v;

            std::copy(s->buf.begin(), s->buf.end(), std::back_inserter(v));

            //writes the content of vector char to fileowner.db 
            std::ofstream output( "licence.txt", std::ios::binary);

            std::copy(v.begin(), v.end(), std::ostreambuf_iterator<char>(output));

             wxMessageBox(wxT("Licence renewal done\nrestart the system"), wxT("Feedback"));
        }
    }

    inline void renew_licence(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
    {
        std::shared_ptr<Session> s(new Session);
        
        
        boost::asio::async_read_until(*sock, boost::asio::dynamic_buffer(s->buf), "}", std::bind(renew_licence_callback, std::placeholders::_1, 
            std::placeholders::_2, s));
  
        
    }

    /************************************************************************************************************************/

    inline void read_callback(const boost::system::error_code& ec, std::size_t bytes_transferred, std::shared_ptr<Session> s,
        std::shared_ptr<boost::asio::ip::tcp::socket> sock, int request_id)
    {
        if (ec.value() != 0) {
             wxMessageBox(wxT_2(ec.message()), wxT("Error"));
            return;
        } else {

            if (request_id == IDX_RESTORE){
                restore(sock);
            } else if (request_id == IDX_CHECK_LICENCE){
                check_licence(sock);
            } else if (request_id ==IDX_LICENCE){
                renew_licence(sock);
            } else{

                //std::cout << "Request unknown" << std::endl;
                wxMessageBox(wxT("Request unknown"), wxT("Error"));
            }
        
        }
        
    }


    inline void read_from_server(std::shared_ptr<boost::asio::ip::tcp::socket> sock, int request_id)
    {
        std::shared_ptr<Session> s(new Session);
        
        std::string txt = get_user_info(request_id);
        
        boost::asio::async_write(*sock, boost::asio::buffer(txt), std::bind(read_callback, std::placeholders::_1, 
            std::placeholders::_2, s, sock, request_id));
        
        
    }

    inline void process_data(int request_id){

        std::string raw_ip = "127.0.0.1";
        unsigned short port = 3333;

        boost::system::error_code ec;

        boost::asio::ip::address Ip = boost::asio::ip::address::from_string(raw_ip, ec);

        if (ec.value() !=0){
           // std::cout << "Error :" << ec.message() << std::endl;
           wxMessageBox(wxT_2(ec.message()), wxT("Error"));

        } else{
            
            boost::asio::ip::tcp::endpoint ep(Ip, port);

            boost::asio::io_context io_context;

            std::shared_ptr<boost::asio::ip::tcp::socket> socket( new boost::asio::ip::tcp::socket(io_context, ep.protocol()));

            socket->connect(ep, ec);

            


            if (ec.value() !=0){
                wxMessageBox(wxT_2(ec.message()), wxT("Error"));
            }else{
                //std::cout << "Connection succesfull" << std::endl;
                if (request_id == IDX_BACKUP){
                writeToSocket(socket, request_id);
                } else {
                    read_from_server(socket, request_id);
                }
                io_context.run();
            }
        }
    }

#endif