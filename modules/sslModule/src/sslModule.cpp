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

moduleType sslModule::getModuleType() const
{
    return (moduleType::SSL);
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
