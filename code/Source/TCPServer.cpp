#include "../Headers/TCPServer.h"
#include "../Headers/TCPSession.h"
#include <boost/bind.hpp>
#include <iostream>
#include <array>
#include <thread>

using namespace boost::asio;
using namespace boost::asio::ip;

TCPServer::TCPServer(std::shared_ptr<boost::asio::io_context> outerContext)
{
	ioContext = outerContext;

	tcp::endpoint endPoint(tcp::v4(), 2014);
	tcpAcceptor = std::make_unique<tcp::acceptor>(*ioContext, endPoint);
	
	std::cout << "Server created at " << endPoint.address() << ":" << endPoint.port() << std::endl;
}

void TCPServer::start()
{
	doAccept();
}

void TCPServer::doAccept()
{
	tcpAcceptor->async_accept([this](const boost::system::error_code& ec, tcp::socket& tcpSocket)
	{
		if (!ec)
		{
			std::cout << "Creating session with " << tcpSocket.remote_endpoint().address().to_string()
				<< ":" << tcpSocket.remote_endpoint().port() << std::endl;

			addSession(std::move(tcpSocket));

			doAccept();
		}
		else std::cout << ec << std::endl;
	});
}

void TCPServer::addSession(tcp::socket&& connectionSocket)
{
	for (int i = 0; i < Constants::maxSessions; i++)
	{
		if (!sessions[i])
		{
			sessions[i] = std::make_unique<TCPSession>(std::move(connectionSocket), sessions, i);

			std::thread(&TCPSession::startSession, sessions[i].get()).detach();
			return;
		}
	}
	// If we dont have enough slots, session will be silently rejected
	// TODO: only accept connection if we have enough slots
}