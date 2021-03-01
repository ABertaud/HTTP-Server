/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#include "tcpConnection.hpp"
#include "Error.hpp"
#include <iostream>

tcpConnection::tcpConnection() : ASocketHandler()
{
}

boost::asio::basic_socket<boost::asio::ip::tcp>& tcpConnection::getSocket()
{
    return (*_socket);
}

void tcpConnection::prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, [[maybe_unused]] boost::asio::ssl::context& ctx)
{
    _socket = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);
    _reqManager.addModuleManager(modManager);
}

void tcpConnection::start()
{
    // std::string s = std::to_string(_socket->remote_endpoint().port());
    // std::string s2 = _socket->remote_endpoint().address().to_string();
    // std::cout << s  + ", " + s2 << std::endl;
    std::memset(_data, '\0', BUFFER_SIZE);
    _socket->async_read_some(boost::asio::buffer(_data, BUFFER_SIZE),
    boost::bind(&tcpConnection::handleRead, this,
    boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcpConnection::handleRead(const boost::system::error_code& err, size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (!err) {
        std::cout << _data << std::endl;
        std::string req(_data);
        std::thread reqThread(static_cast<void (requestManager::*)(const std::string&, boost::asio::ip::tcp::socket&)>(&requestManager::launchRequest), _reqManager, std::ref(req), std::ref(*_socket));
        if (reqThread.joinable() == true)
            reqThread.join();
        // _reqManager.launchRequest(req, pList, _socket);
        start();
    } else {
        // std::cerr << "error: " << err.message() << "kk" << std::endl;
        _socket->close();
    }
}