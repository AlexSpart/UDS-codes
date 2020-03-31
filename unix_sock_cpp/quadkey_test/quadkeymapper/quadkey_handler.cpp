/*
 * quadkey_handler.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: EURECOM
 */

#include "quadkey_handler.hpp"
#include "quadkey.hpp"  // external library for the effective quadkey

using boost::asio::local::datagram_protocol;
using namespace std::chrono;

QuadKeyHandler::QuadKeyHandler(boost::asio::steady_timer& timer, boost::asio::local::datagram_protocol::socket& unix_quadkey_socket)
    : timer_(timer), unix_quadkey_socket_(unix_quadkey_socket)
{

       std::cout << "QuadKey MicroService - UNIX domain socket open...waiting for connection on the QuadKey_SAP interface..."<<std::endl;
       unix_quadkey_socket_.async_receive(boost::asio::buffer(receive_buffer_),
           boost::bind(&QuadKeyHandler::handle_read_unix,
             this,
             boost::asio::placeholders::error,
             boost::asio::placeholders::bytes_transferred));
}

void QuadKeyHandler::handle_read_unix(const boost::system::error_code& error, size_t bytes_transferred)
{
    std::cout << "QuadKey MicroService - Received a connection on the QUADK_SAP interface..."<<std::endl;

    if (!error)
    {
        /**
         * JHNOTE: once we receive a trigger from the geoserver,
         *         we send convert what we need
         */
        std::string s(receive_buffer_.begin(), receive_buffer_.end());
	    receive_buffer_.assign(0);    // zero the buffer
		s.resize(bytes_transferred);  // trimming dummy bits

#ifdef DEBUG
        std::cout << "QuadKey: content of message: "<<s<<std::endl;
#endif
        // Resize the string to the size of the incoming message so that excess zeros are not included
        /**
         * creating a bson from the received string (assuming it is a JSON string)
         */
       /* try{
            bsoncxx::document::value document = bsoncxx::from_json(s);
            convert(document);
        }
        catch(std::exception const& e){
            std::cout << "[DENMApplication::handle_read_unix] String to JSON conversion failed: " << e.what() << std::endl;
        }*/
        receive_buffer_.empty();

        std::string return_value = "TEST";

        boost::system::error_code ignored_error;
        auto bytes_sent = unix_quadkey_socket_.send_to(boost::asio::buffer(return_value), unix_quadkey_socket_.remote_endpoint(), 0, ignored_error);
        std::cout << "[QuadKeyHandler::handle_read_unix()] converted value sent back on the QUADKEY_SAP interface...bytes sent:"<<bytes_sent<<std::endl;
        /**
          * conversion done and value sent, go back to listening mode
        */
        std::cout<<"QuadKey Service: Conversion done...listening to new triggers"<<std::endl;
        unix_quadkey_socket_.async_receive(boost::asio::buffer(receive_buffer_),
            boost::bind(&QuadKeyHandler::handle_read_unix,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
}


