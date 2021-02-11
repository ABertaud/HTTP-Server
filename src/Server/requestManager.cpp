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
    try {
        HTTP::HTTPObject request(req);
        moduleType type = list.getCurrentType();

        while (type != moduleType::NONE) {
            for (auto &mod : _modules)
                if (mod->getModuleType() == type)
                    mod->processRequest(request);
            list.remove();
            type = list.getCurrentType();
        }
        auto answer = request.toString();
        socket.send(boost::asio::buffer(answer));
    } catch (ErrorHTTPObject& e) {
        socket.send(boost::asio::buffer("400 Bad Request Error"));
        return;
    }
}

void requestManager::loadModules(std::unordered_map<moduleType, std::string>& modulePaths)
{
    for (auto& path : modulePaths) {
        if (_loaders.count(path.first) == 0)
            _loaders.insert(std::make_pair(path.first, std::shared_ptr<DLLoader>{new DLLoader(path.second)}));
    }
    for (auto& load : _loaders) {
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

std::shared_ptr<IModule> &requestManager::getModule(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (module);
    return (_modules.front());
}