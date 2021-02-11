/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include "moduleType.hpp"
#include "HTTPObject.hpp"
#include <boost/asio.hpp>

class IModule {
    public:
        virtual ~IModule() = default;
        virtual void processRequest(HTTP::HTTPObject& req)= 0;
        virtual void onReceive(const boost::asio::ip::tcp::socket& sock) = 0;
        virtual void onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend) = 0;
        virtual moduleType getModuleType() const = 0;
};

#endif /* !IMODULE_HPP_ */
