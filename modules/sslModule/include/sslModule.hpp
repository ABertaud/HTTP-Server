/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule
*/

#ifndef SSLMODULE_HPP_
#define SSLMODULE_HPP_

#include "IModule.hpp"
#include "ASocketHandler.hpp"

// using boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLType;
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslSocket;

class sslModule : public IModule, public ASocketHandler {
    public:
        sslModule();
        void processRequest(HTTP::HTTPObject& req);
        void init(const std::string& path);
        moduleType getModuleType() const;
        void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx);
        void start();
        boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket();
        sslModule(const sslModule& other) = default;
        sslModule& operator=(const sslModule& other) = default;
        ~sslModule() = default;
    private:
        void handleRead(const boost::system::error_code& err, size_t bytesTransferred);
        void handleHandshake(const boost::system::error_code& error);
        // boost::asio::ssl::context _ctx;
        std::shared_ptr<sslSocket> _socket;
};

#endif /* !SSLMODULE_HPP_ */
