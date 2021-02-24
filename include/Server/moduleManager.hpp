/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** moduleManager
*/

#ifndef MODULEMANAGER_HPP_
#define MODULEMANAGER_HPP_

#include "IModule.hpp"
#include "DLLoader.hpp"
#include <vector>
#include <unordered_map>

class moduleManager {
    public:
        moduleManager();
        ~moduleManager() = default;
        moduleManager(const moduleManager& other);
        moduleManager& operator=(const moduleManager& other);
        bool doesModuleExist(const moduleType& type);
        bool doesLoaderExist(const moduleType& type);
        std::shared_ptr<IModule> &getModule(const moduleType& type);
        void loadLoaders(std::unordered_map<moduleType, std::string>& modulePaths);
        void loadModules();
        std::shared_ptr<IModule> getNewModule(const moduleType& type);
    private:
        std::unordered_map<moduleType, std::shared_ptr<DLLoader>> _loaders;
        std::vector<std::shared_ptr<IModule>> _modules;
};


#endif /* !MODULEMANAGER_HPP_ */
