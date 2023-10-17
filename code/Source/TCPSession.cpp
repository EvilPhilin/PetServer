#include "../Headers/TCPSession.h"
#include <boost/bind.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace boost::asio;
using namespace boost::asio::ip;

// Main session's algorithm
void TCPSession::startSession()
{
	readData();
	executeTask();
	sendResponse();
	closeSession();
}

TCPSession::TCPSession(boost::asio::ip::tcp::socket connectionSocket,
	std::array<std::unique_ptr<TCPSession>, Constants::maxSessions>& nest, int id) : nest(nest), idInNest(id)
{
	std::cout << "Creating " << id << "'th session";
	tcpSocket = std::make_unique<tcp::socket>(std::move(connectionSocket));
	std::cout << " using socket with address " << tcpSocket.get() << std::endl;
}

TCPSession::~TCPSession()
{
	tcpSocket->release();
}

void TCPSession::readData()
{
	std::size_t received = tcpSocket->read_some(buffer(inputBuff, Constants::maxBuffSize));
	std::cout << std::string(inputBuff.begin(), inputBuff.begin() + received) << std::endl;
}

void TCPSession::executeTask()
{
	std::this_thread::sleep_for(chrono::seconds(5));
}

void TCPSession::sendResponse()
{
	tcpSocket->write_some(buffer(outputBuff, outputBuff.length()));
}

void TCPSession::closeSession()
{
	std::cout << "Closing session with " << tcpSocket->remote_endpoint().address() <<
		":" << tcpSocket->remote_endpoint().port() << std::endl;

	tcpSocket->close();
	this->nest[idInNest].reset(nullptr);
}