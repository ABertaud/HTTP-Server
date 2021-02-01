/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** requestManager
*/

#ifndef REQUESTMANAGER_HPP_
#define REQUESTMANAGER_HPP_

#include <vector>
#include <unordered_map>
#include <memory>
#include <boost/asio.hpp>
#include "processingList.hpp"
#include "IModule.hpp"
#include "DLLoader.hpp"

class requestManager {
    public:
        requestManager();
        void reload(std::unordered_map<moduleType, std::string>& modulePaths);
        void launchRequest(const std::string& req, processingList& list, boost::asio::ip::tcp::socket& socket);
    private:
        void loadModules(std::unordered_map<moduleType, std::string>& modulePaths);
        bool doesModuleExist(const moduleType& type);
        std::unordered_map<moduleType, std::unique_ptr<DLLoader>> _loaders;
        std::vector<std::unique_ptr<IModule>> _modules;
};

#endif /* !REQUESTMANAGER_HPP_ */
