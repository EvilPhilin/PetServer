#include "Headers/TCPServer.h"
#include <boost/asio/io_context.hpp>

int runServer()
{
    std::shared_ptr<boost::asio::io_context> ioContext = std::make_shared<boost::asio::io_context>();
    std::unique_ptr<TCPServer> serv = std::make_unique<TCPServer>(ioContext);

    serv->start();
    ioContext->run();

    return 0;
}