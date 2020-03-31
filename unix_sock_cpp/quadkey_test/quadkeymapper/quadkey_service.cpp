/*
 * quadkey_service.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: EURECOM
 */

#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/generic/raw_protocol.hpp>
#include <boost/asio/generic/datagram_protocol.hpp>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>

#include "quadkey_handler.hpp"


namespace asio = boost::asio;
namespace po = boost::program_options;

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

int main(int argc, const char** argv)
{
    po::options_description options("Allowed options");
    options.add_options()
        ("help", "Print out available options.")
        ("server-port-number", po::value<unsigned>()->default_value(3000), "Port Number the V2X-Manager is listening to incoming RX.")
        ("client-port-number", po::value<unsigned>()->default_value(3000), "Port Number the V2X-Manager is sending to the distant client.")
    	;


    po::variables_map vm;

    try {
        po::store(
            po::command_line_parser(argc, argv)
                .options(options)
                .run(),
            vm
        );
        po::notify(vm);
    } catch (po::error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << options << std::endl;
        return 1;
    }

    if (vm.count("help")) {
        std::cout << options << std::endl;
        return 1;
    }

    int server_port = 0;
    if (vm.count("server-port-number")) {
        std::string port = vm["server-port-number"].as<std::string>();
        server_port = std::stoi(port);
    }

    int client_port = 0;
    if (vm.count("client-port-number")) {
        std::string port = vm["client-port-number"].as<std::string>();
        client_port = std::stoi(port);
    }


    try {
        asio::io_service io_service;

        // Creating UDP Server...
      //  V2XMQTTAgent* mqtt = V2XMQTTAgent::getInstance();
      //  mqtt->Log("5gcroco/quadkey/status", "Starting the QuadKey service");

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       // Creating a UNIX domain socket between Geoserver and V2X Manager
       std::cout << "Creating UNIX domain sockets"<< std::endl;
       using boost::asio::local::datagram_protocol;

       ::unlink("/tmp/QUADKEY_SAP"); // Remove previous binding.
       boost::asio::local::datagram_protocol::endpoint quadkey_ep("/tmp/QUADKEY_SAP");
       boost::asio::local::datagram_protocol::socket unix_quadkey_socket(io_service, quadkey_ep);
       //done

#else // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
    std::cout << "ERROR: UNIX domain NOT supported on that platform"<< std::endl;
#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
 // UNIX done...


	// One single call of this method is required for the entire v2x-manager
	//mongocxx::instance&  inst =  mongocxx::instance::current();

    auto signal_handler = [&io_service](const boost::system::error_code& ec, int signal_number) {
        if (!ec) {
            std::cout << "Termination requested." << std::endl;
            io_service.stop();
        }
    };
    asio::signal_set signals(io_service, SIGINT, SIGTERM);
    signals.async_wait(signal_handler);

    asio::steady_timer quadkey_timer(io_service);

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
        QuadKeyHandler handler(quadkey_timer, unix_quadkey_socket);
#else
        std::cout << "ERROR: UNIX domain NOT supported on that platform"<< std::endl;
#endif

     // running quadkey microservicer
     io_service.run();

    }
    catch (std::exception& e) {
        std::cerr << "Exit: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}




