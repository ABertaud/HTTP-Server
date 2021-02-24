/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ASocketHandler.hpp"

class tcpConnection : public ASocketHandler {
    public:
        tcpConnection();
        void start();
        void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx);
        boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket();
        tcpConnection(const tcpConnection& other) = default;
        tcpConnection& operator=(const tcpConnection& other) = default;
        ~tcpConnection() = default;
    private:
        void handleRead(const boost::system::error_code& err, size_t bytesTransferred);
        std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
};
#endif /* !TCPCONNECTION_HPP_ */