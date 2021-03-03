/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** moduleManager
*/

#include "moduleManager.hpp"

moduleManager::moduleManager()
{
}

moduleManager::moduleManager(const moduleManager& other)
{
    this->_loaders = other._loaders;
}

moduleManager& moduleManager::operator=(const moduleManager& other)
{
    this->_loaders = other._loaders;
    return (*this);
}

void moduleManager::loadLoaders(std::unordered_map<moduleType, std::string>& modulePaths)
{
    for (auto& path : modulePaths) {
        if (_loaders.count(path.first) == 0)
            _loaders.insert(std::make_pair(path.first, std::shared_ptr<DLLoader>{new DLLoader(path.second)}));
    }
}

bool moduleManager::doesModuleExist(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (true);
    return (false);
}

bool moduleManager::doesLoaderExist(const moduleType& type)
{
    for (auto& load : _loaders) {
        if (load.first == type)
            return (true);
    }
    return (false);
}

std::shared_ptr<IModule> moduleManager::getNewModule(const moduleType& type)
{
    for (auto& load : _loaders) {
        if (load.first == type)
                return (load.second->getInstance<IModule>("entryPoint"));
    }
    return (nullptr);
}

std::shared_ptr<IModule>& moduleManager::getModule(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (module);
    return (_modules.front());
}

void moduleManager::loadModules()
{
    for (auto& load : _loaders) {
        if (doesModuleExist(load.first) == false) {
            _modules.push_back(load.second->getInstance<IModule>("entryPoint"));
        }
    }
}