/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** requestManager
*/

#ifndef REQUESTMANAGER_HPP_
#define REQUESTMANAGER_HPP_

#include <memory>
#include <boost/asio.hpp>
#include "processingList.hpp"
#include "moduleManager.hpp"
#include <openssl/ssl.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>


class requestManager {
    public:
        requestManager();
        void reload(std::unordered_map<moduleType, std::string>& modulePaths, const processingList &processList, const std::string& cgiPath);
        void addModuleManager(const moduleManager& modManager);
        void launchRequest(const std::string& req, boost::asio::ip::tcp::socket& socket);
        void launchRequest(const std::string& req, boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket);
        requestManager(const requestManager& other) = default;
        requestManager& operator=(const requestManager& other) = default;
        ~requestManager() = default;
    private:
        moduleManager _modManager;
        processingList _processList;
        
};

#endif /* !REQUESTMANAGER_HPP_ */
