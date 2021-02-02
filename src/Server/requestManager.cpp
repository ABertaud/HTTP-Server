/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** requestManager
*/

#include "requestManager.hpp"

requestManager::requestManager()
{
}

void requestManager::reload(std::unordered_map<moduleType, std::string>& modulePaths)
{
    loadModules(modulePaths);
}

void requestManager::launchRequest(const std::string& req, processingList& list, boost::asio::ip::tcp::socket& socket)
{

}

void requestManager::loadModules(std::unordered_map<moduleType, std::string>& modulePaths)
{
    for (auto& path : modulePaths) {
        if (_loaders.count(path.first) == 0)
            _loaders.insert(std::make_pair(path.first, std::unique_ptr<DLLoader>{new DLLoader(path.second)}));
    }
    for (auto &load : _loaders) {
        if (doesModuleExist(load.first) == false)
            _modules.push_back(load.second->getInstance<IModule>("entryPoint"));
    }
}

bool requestManager::doesModuleExist(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (true);
    return (false);
}