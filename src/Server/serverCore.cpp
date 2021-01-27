/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#include "serverCore.hpp"
#include "tcpConnection.hpp"

serverCore::serverCore(boost::asio::io_context& ioContext, const std::string& configPath) : _acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080))
{
    startAccept();
}

void serverCore::startAccept()
{
    tcpConnection::pointer newConnection = tcpConnection::create(_acceptor.get_executor().context());

    _acceptor.async_accept(newConnection->getSocket(), boost::bind(&serverCore::handleAccept, 
    this, newConnection,boost::asio::placeholders::error));
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

void serverCore::stop()
{
    if (_acceptor.is_open() == true)
        _acceptor.get_io_service().stop();
}