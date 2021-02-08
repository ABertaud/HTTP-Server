/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "pathHandler.hpp"
#include "requestManager.hpp"
#include "configHandler.hpp"

#define BUFFER_SIZE (4096)

class tcpConnection : public boost::enable_shared_from_this<tcpConnection> {
    public:
        typedef boost::shared_ptr<tcpConnection> pointer;

        static pointer create(boost::asio::io_context& ioContext, const configPaths& paths);
        void start();
        boost::asio::ip::tcp::socket& getSocket();
        tcpConnection(const tcpConnection& other) = default;
        tcpConnection& operator=(const tcpConnection& other) = default;
        ~tcpConnection() = default;
    private:
        tcpConnection(boost::asio::io_context& ioContext, const configPaths& paths);
        void handleWrite(const boost::system::error_code& /*error*/, size_t /*bytesTransferred*/);
        void handleRead(const boost::system::error_code& err, size_t bytesTransferred);
        void send(const std::string& toSend);
        boost::asio::ip::tcp::socket _socket;
        std::string _message;
        requestManager _reqManager;
        configHandler _confHandler;
        char _data[BUFFER_SIZE];
};
#endif /* !TCPCONNECTION_HPP_ */