/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule
*/

#ifndef SSLMODULE_HPP_
#define SSLMODULE_HPP_

#include "IModule.hpp"

class sslModule : public IModule {
    public:
        sslModule();
        void processRequest(HTTP::HTTPObject& req);
        void onReceive(const boost::asio::ip::tcp::socket& sock);
        void onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend);
        moduleType getModuleType() const;
        sslModule(const sslModule& other) = default;
        sslModule& operator=(const sslModule& other) = default;
        ~sslModule() = default;

    protected:
    private:
};

#endif /* !SSLMODULE_HPP_ */
