/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** configHandler.cpp
*/

#include "configHandler.hpp"
#include <iostream>

configHandler::configHandler(const configPaths& paths) try : _fileErr(), _processList(), _json(paths.configPath), \
_modulePaths(), _paths()
{
    _fileErr.open(paths.configPath);
    if (!_fileErr)
        throw ErrorConfigPath();
    _paths.configPath = paths.configPath;
    _paths.dirPath = paths.dirPath;
    load();
} catch (Error const &err) {
    throw err;
}

void configHandler::load()
{
    std::string line("");
    std::string name("");
    bool PosModule = false;
    std::ifstream jsonFile(_paths.configPath);
    size_t endModule = std::string::npos;

    try {
        while (std::getline(jsonFile, line, '\n')) {
            if (line.find("\"") != std::string::npos) {
                if (PosModule == true) {
                    name = getname(line);
                    addModuleJson(name);
                }
                if (checktagModule(line) == true)
                    PosModule = true;
            }
            endModule = line.find("]");
            if (PosModule == true && endModule != std::string::npos)
               PosModule = false;
        }
    } catch (Error const &err) {
        throw err;
    }
}

processingList configHandler::getCopyProcessList()
{
    return _processList;
}

std::unordered_map<moduleType, std::string>& configHandler::getListModules()
{
    return _modulePaths;
}

std::string configHandler::getname(std::string line)
{
    std::string name = "";
    size_t found = line.find("\"");
    std::size_t foundLast = line.find_last_of("\"");

    foundLast -= found;
    found++;
    foundLast--;
    name = line.substr(found, foundLast);
    return name;
}

bool configHandler::checktagModule(std::string& line)
{
    std::string tag = getname(line);
    size_t pos = line.find("[");
    
    if (tag == "modules" && pos != std::string::npos)
        return true;
    return false;
}

void configHandler::addModuleJson(const std::string& name)
{
    std::string path = _paths.dirPath + name + ".so";

    if (_moduleType.find(name) == _moduleType.end()) {
        throw ErrorConfigTag();
        return;
    }
    std::ifstream infile(path);
    if (infile.good() == false) {
        throw ErrorConfigSo();
        return;
    }
    _modulePaths.insert({_moduleType.find(name)->second, path});
    _processList.add(_moduleType.find(name)->second);
}

void configHandler::reload()
{   
    _modulePaths.clear();
    _processList.clear();
    try {
        load();
    } catch (Error const &err) {
        throw err;
    }
}