/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#include "serverCore.hpp"
#include "tcpConnection.hpp"

serverCore::serverCore(boost::asio::io_context& ioContext, const std::string& configPath, const std::string& dirPath) :
 _acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)), _paths({dirPath ,configPath}), _sigHandler(), _t(ioContext, boost::asio::chrono::seconds(1))
{
    startAccept();
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, boost::asio::placeholders::error));
}

void serverCore::startAccept()
{
    // tcpConnection::pointer newConnection;
    // try {
    tcpConnection::pointer newConnection = tcpConnection::create(_acceptor.get_executor().context(), _paths);
    _acceptor.async_accept(newConnection->getSocket(), boost::bind(&serverCore::handleAccept, 
    this, newConnection,boost::asio::placeholders::error));
    // } catch (Error& e) {
    //     std::cout << "close + " << e.what() << std::endl;
    //     if (newConnection)
    //         newConnection.reset();
    //     startAccept();
    // }
}

void serverCore::handleAccept(tcpConnection::pointer newConnection, const boost::system::error_code& error)
{
    if (!error)
    {
      newConnection->start();
    }
    startAccept();
}

void serverCore::start()
{
    _acceptor.get_io_service().run();
}

void serverCore::serverEndHandler(const boost::system::error_code&)
{
    if (_sigHandler.isInterrupted() == true) {
        std::cerr << "Server's leaving." << std::endl;
        stop();
    }
    _t.expires_at(_t.expires_at() + boost::asio::chrono::seconds(1));
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, boost::asio::placeholders::error));
}

void serverCore::stop()
{
    if (_acceptor.is_open() == true)
        _acceptor.get_io_service().stop();
}