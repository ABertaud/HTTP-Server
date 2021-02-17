/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule.cpp
*/

#include "sslModule.hpp"
#include <memory>

sslModule::sslModule()
: _ctx(boost::asio::ssl::context::sslv23), _isInit(false)
{
}

void sslModule::processRequest(HTTP::HTTPObject& req)
{
    (void)req;
}

void sslModule::init(const std::string& path, boost::asio::ip::tcp::socket& sock)
{
    // Load certificate in context (file = "mycert.pem")
    // Send the path in the config file
    _ctx.set_verify_mode(boost::asio::ssl::verify_peer);
    _ctx.load_verify_file(path);
    // Create a ssl stream from the given socket and class context (_ctx)
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_sock(sock.get_executor().context(), _ctx);

    // Resolve the hostname
    boost::asio::ip::tcp::resolver resolver(sock.get_executor().context());
    boost::asio::ip::tcp::resolver::query query("127.0.0.1", "https");
    boost::asio::connect(ssl_sock.lowest_layer(), resolver.resolve(query));
    ssl_sock.lowest_layer().set_option(boost::asio::ip::tcp::no_delay(true));

    ssl_sock.set_verify_mode(boost::asio::ssl::verify_peer);
    ssl_sock.set_verify_callback(boost::asio::ssl::rfc2818_verification("127.0.0.1"));
    ssl_sock.handshake(boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::client);
    _isInit = true;
}

void sslModule::onReceive(const boost::asio::ip::tcp::socket& sock)
{
    (void)sock;
}

void sslModule::onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend)
{
    (void)sock;
    (void)toSend;
}

moduleType sslModule::getModuleType() const
{
    return (moduleType::SSL_MODULE);
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
