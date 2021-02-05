/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#include "tcpConnection.hpp"
#include <iostream>

tcpConnection::tcpConnection(boost::asio::io_context& ioContext, const configPaths& paths) : _socket(ioContext)
{
    (void)paths;
}

tcpConnection::pointer tcpConnection::create(boost::asio::io_context& ioContext, const configPaths& paths)
{
    return pointer(new tcpConnection(ioContext, paths));
}

boost::asio::ip::tcp::socket& tcpConnection::getSocket()
{
    return (_socket);
}

void tcpConnection::start()
{
    std::memset(_data, '\0', BUFFER_SIZE);
    _socket.async_read_some(boost::asio::buffer(_data, BUFFER_SIZE),
    boost::bind(&tcpConnection::handleRead, shared_from_this(),
    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcpConnection::handleWrite(const boost::system::error_code& /*error*/, size_t /*bytesTransferred*/)
{

}

void tcpConnection::handleRead(const boost::system::error_code& err, size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (!err) {
        // _reqManager.launchRequest(req, socket);
        start();
    } else {
        std::cerr << "error: " << err.message() << std::endl;
        _socket.close();
    }
}

void tcpConnection::send(const std::string& toSend)
{
    _socket.send(boost::asio::buffer(toSend));
}