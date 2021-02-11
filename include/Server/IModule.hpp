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

class IModule {
    public:
<<<<<<< HEAD
    virtual ~IModule() = default;
    virtual void processRequest(HTTP::HTTPObject& req) = 0;
    virtual moduleType getModuleType() const = 0;
    private:
=======
        virtual ~IModule() = default;
        virtual void processRequest(HTTP::HTTPObject& req) = 0;
        virtual void onReceive(const boost::asio::ip::tcp::socket& sock) = 0;
        virtual void onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend) = 0;
        virtual moduleType getModuleType()= 0;
>>>>>>> b13a327d0903042c16e417e08d46de20a585b5aa
};

#endif /* !IMODULE_HPP_ */
