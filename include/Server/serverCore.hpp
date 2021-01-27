/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#ifndef SERVERCORE_HPP_
#define SERVERCORE_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include "tcpConnection.hpp"

class serverCore {
    public:
        serverCore(boost::asio::io_context& ioContext, const std::string& configPath);
        void start();
        void stop();
        serverCore(const serverCore& other) = default;
        serverCore& operator=(const serverCore& other) = default;
        ~serverCore() = default;
    private:
        void startAccept();
        void handleAccept(tcpConnection::pointer newConnection, const boost::system::error_code& error);
        boost::asio::ip::tcp::acceptor _acceptor;

};

#endif /* !SERVERCORE_HPP_ */
