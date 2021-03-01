/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** configHandler.hpp
*/

#ifndef CONFIGHANDLER_HPP_
#define CONFIGHANDLER_HPP_

#include "pathHandler.hpp"
#include "processingList.hpp"
#include <unordered_map>
#include "moduleType.hpp"
#include "jsonReader.hpp"
#include <string>
#include "Error.hpp"
#include <fstream>
#include <map>
#include <filesystem>

enum ConfigType {
    MODULE
};

class configHandler
{
    private:
        std::ifstream _fileErr;
        processingList _processList;
        jsonReader _json;
        std::unordered_map<moduleType, std::string> _modulePaths;
        configPaths _paths;
        std::string _certificatePath;
        std::string _CgiDir;
        const std::map<std::string, moduleType> _moduleType {
        {"phpCgiModule", PHPCGI},
        {"sslModule", SSL_MODULE},
        {"snakeModule", SNAKE},
        {"file_Server", FILE_SERVER},
        };
        void load();
        void addModuleJson(const std::string& name);
        bool checktagModule(std::string& line);
        std::string getName(std::string line);
        void fileExists(const std::filesystem::path& p);
        void checkTag(std::string line);
        int nthOccurrence(const std::string& str, const std::string& findMe, int nth);

    public:
        configHandler(const configPaths& paths);
        configHandler(const configHandler& other) = default;
        configHandler& operator=(const configHandler& other) = default;
        void reload();
        std::string getCgiPath()const;
        std::string getCertificatePath()const;
        processingList getCopyProcessList();
        std::unordered_map<moduleType, std::string>& getListModules();
        ~configHandler() = default;
};

#endif