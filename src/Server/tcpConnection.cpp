/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#include "tcpConnection.hpp"
#include <boost/filesystem/operations.hpp>
#include "Error.hpp"
#include <iostream>

tcpConnection::tcpConnection(boost::asio::io_context& ioContext, const configPaths& paths) : _socket(ioContext), _confHandler(paths), _t(ioContext, boost::asio::chrono::seconds(1))
{
    _reqManager.reload(_confHandler.getListModules());
    boost::filesystem::path p(paths.configPath);
    if (boost::filesystem::exists(p)) {
        lastUpdate = boost::filesystem::last_write_time(p);
        _t.async_wait(boost::bind(&tcpConnection::handleConfigUpdate, this, boost::asio::placeholders::error, paths.configPath));
    } else
        throw ErrorConfigPath();
    
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
    if (_reqManager.doesModuleExist(moduleType::SSL)) {
        _reqManager.getModule(moduleType::SSL);
    } else {
        _socket.async_read_some(boost::asio::buffer(_data, BUFFER_SIZE),
        boost::bind(&tcpConnection::handleRead, shared_from_this(),
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}

void tcpConnection::handleWrite(const boost::system::error_code& /*error*/, size_t /*bytesTransferred*/)
{

}

void tcpConnection::handleRead(const boost::system::error_code& err, size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (!err) {
        auto pList = _confHandler.getCopyProcessList();
        std::string req(_data);
        std::thread reqThread(&requestManager::launchRequest, _reqManager, std::ref(req), std::ref(pList), std::ref(_socket));
        // reqThread.detach();
        // _reqManager.launchRequest(req, pList, _socket);
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

void tcpConnection::handleConfigUpdate(const boost::system::error_code& err, const std::string& configPath)
{
    boost::filesystem::path p(configPath);
    if (boost::filesystem::exists(p)) {
        if (lastUpdate != boost::filesystem::last_write_time(p)) {
            _confHandler.reload();
            _reqManager.reload(_confHandler.getListModules());
            lastUpdate = boost::filesystem::last_write_time(p);
        }
        _t.async_wait(boost::bind(&tcpConnection::handleConfigUpdate, this, boost::asio::placeholders::error, configPath));
    } else
        throw ErrorConfigPath();
}