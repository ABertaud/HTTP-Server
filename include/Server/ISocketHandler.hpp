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
/** @class ISocketHandler
    *  @brief The ISocketHandler class is an interface class that gather common methods between all class considered as socketHandlers
*/
class ISocketHandler {
    public:
        /** @brief Dtor of ISocketHandler (virtual cause Interface) */
        virtual ~ISocketHandler() = default;
        /** @brief This function will prepare the socketHandler to be able to work autonomously
            *  @param ioContext Context of the accepted connection, needed to create a socket
            *  @param modManager Class moduleManager
            *  @param ctx Boost asio ssl context, useful for the ssl certificate
        */
        virtual void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx) = 0;
        /** @brief This function will reload the modules and the processing list used by the appropriate ISocketHandler
            *  @param modulePaths Map containing the type of the module and on the other hand containing the exact path to its .so
            *  @param cgiPath Exact path to the dir where CGI scripts are stocked
            *  @param processList Class processingList
        */
        virtual void reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList) = 0;
        /** @brief This function launches the asynchronous usage of the socket */
        virtual void start() = 0;
        /** @brief This function will return the socket of the ISocketHandler
            * @return boost::asio::basic_socket<boost::asio::ip::tcp> The lowest layer of a tcp socket
        */
        virtual boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket() = 0;
    private:
    protected:
    private:
};

#endif /* !ISOCKETHANDLER_HPP_ */
