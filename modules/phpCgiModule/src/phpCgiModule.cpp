/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule.cpp
*/

#include "phpCgiModule.hpp"
#include <memory>

phpCgiModule::phpCgiModule()
{
}

void phpCgiModule::processRequest(HTTP::HTTPObject& req)
{
    (void)req;
}

void phpCgiModule::onReceive(const boost::asio::ip::tcp::socket& sock)
{
    (void)sock;
}

void phpCgiModule::onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend)
{
    (void)sock;
    (void)toSend;
}

moduleType phpCgiModule::getModuleType() const
{
    return (moduleType::PHPCGI);
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<phpCgiModule>(new phpCgiModule));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<phpCgiModule>());
    }

#endif
