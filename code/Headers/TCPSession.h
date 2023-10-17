#pragma once
#include "Constants.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <array>
#include <unordered_set>

class TCPSession
{
public:
	TCPSession(boost::asio::ip::tcp::socket connectionSocket,
			   std::array<std::unique_ptr<TCPSession>, Constants::maxSessions>& nest, int id);
	~TCPSession();
	void startSession();

private:
	void readData();
	void executeTask();
	void sendResponse();
	void performTask(boost::system::error_code ec, std::size_t received);
	void closeSession();

private:
	std::array<std::unique_ptr<TCPSession>, Constants::maxSessions>& nest;
	int idInNest;

	std::unique_ptr<boost::asio::ip::tcp::socket> tcpSocket;

	std::array<char, Constants::maxBuffSize> inputBuff;
	std::string outputBuff = "HTTP/1.1 200 OK\n\r";
};