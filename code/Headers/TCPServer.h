#pragma once
#include "TCPSession.h"
#include "Constants.h"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <memory>
#include <array>

class TCPServer
{
public:
	void start();
	TCPServer(std::shared_ptr<boost::asio::io_context> outerContext);

private:
	void doAccept();
	void addSession(boost::asio::ip::tcp::socket&& connectionSocket);

private:
	std::shared_ptr<boost::asio::io_context> ioContext;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> tcpAcceptor;

	std::array<std::unique_ptr<TCPSession>, Constants::maxSessions> sessions;
};