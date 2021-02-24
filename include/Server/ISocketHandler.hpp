/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** ISocketHandler
*/

#ifndef ISOCKETHANDLER_HPP_
#define ISOCKETHANDLER_HPP_

#include <openssl/ssl.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string>
#include "moduleManager.hpp"
#include "processingList.hpp"

class ISocketHandler {
    public:
        virtual ~ISocketHandler() = default;
        virtual void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx) = 0;
        virtual void reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList) = 0;
        virtual void start() = 0;
        virtual boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket() = 0;
    private:
    protected:
    private:
};

#endif /* !ISOCKETHANDLER_HPP_ */
