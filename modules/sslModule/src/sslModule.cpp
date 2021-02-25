/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule.cpp
*/

#include "sslModule.hpp"
#include <memory>
#include <cstring>

sslModule::sslModule()
{
}

void sslModule::processRequest([[maybe_unused]] HTTP::HTTPObject& req)
{
}

void sslModule::init([[maybe_unused]] const std::string& path)
{
}

moduleType sslModule::getModuleType() const
{
    return (moduleType::SSL_MODULE);
}

void sslModule::prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx)
{
    _socket = std::make_shared<sslSocket>(ioContext, ctx);
    _reqManager.addModuleManager(modManager);
}

void sslModule::start()
{
    std::memset(_data, '\0', BUFFER_SIZE);
    _socket->async_handshake(boost::asio::ssl::stream_base::server,
    boost::bind(&sslModule::handleHandshake, this,
    boost::asio::placeholders::error));
}

boost::asio::basic_socket<boost::asio::ip::tcp>& sslModule::getSocket()
{
    return (_socket->lowest_layer());
}

void sslModule::handleHandshake(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "Handshake Done!" << std::endl;
        _socket->async_read_some(boost::asio::buffer(_data, 1024),
            boost::bind(&sslModule::handleRead, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else {
        std::cout << "Session ended ..." << std::endl;
        if (this)
            delete this;
    }
}

void sslModule::reset(void)
{
    std::memset(_data, '\0', BUFFER_SIZE);
    _socket->async_read_some(boost::asio::buffer(_data, 1024),
        boost::bind(&sslModule::handleRead, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void sslModule::handleRead(const boost::system::error_code& err, size_t bytesTransferred)
{
    (void)bytesTransferred;
    if (!err) {
        std::cout << "ssl :";
        std::cout << _data << std::endl;
        std::string req(_data);
        std::thread reqThread(static_cast<void (requestManager::*)(const std::string&, sslSocket&)>(&requestManager::launchRequest), _reqManager, std::ref(req), std::ref(*_socket));
        reqThread.join();

        boost::asio::write(*_socket.get(), boost::asio::buffer("HTTP/1.1 200 OK\n", 17));

        reset();
        // _reqManager.launchRequest(req, pList, _socket);
        // start();
    } else {
        std::cerr << "error: " << err.message() << std::endl;
        _socket->lowest_layer().close();
    }
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<sslModule>(new sslModule));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<sslModule>());
    }

#endif
