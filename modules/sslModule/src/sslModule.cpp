/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule.cpp
*/

#include "sslModule.hpp"
#include <memory>

sslModule::sslModule()
{
}

void sslModule::processRequest(HTTP::HTTPObject& req)
{
    (void)req;
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
