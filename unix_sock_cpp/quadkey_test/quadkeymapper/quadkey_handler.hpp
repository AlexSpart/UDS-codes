/*
 * quadkey_handler.hpp
 *
 *  Created on: Mar 19, 2020
 *      Author: EURECOM
 */

#ifndef QUADKEY_HANDLER_HPP_
#define QUADKEY_HANDLER_HPP_

#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/generic/raw_protocol.hpp>
#include <boost/asio/generic/datagram_protocol.hpp>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <boost/optional/optional.hpp>
#include <boost/asio/buffer.hpp>


class QuadKeyHandler
{
public:

QuadKeyHandler(boost::asio::steady_timer& timer, boost::asio::local::datagram_protocol::socket& unix_quadkey_socket);
void handle_read_unix(const boost::system::error_code& error, size_t bytes_transferred);

boost::asio::steady_timer& timer_;
boost::asio::local::datagram_protocol::socket& unix_quadkey_socket_;
boost::array<char, 1024> receive_buffer_;
};

#endif /* QUADKEY_HANDLER_HPP_ */
