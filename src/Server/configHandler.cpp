/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** configHandler.cpp
*/

#include "configHandler.hpp"
#include <iostream>

configHandler::configHandler(const configPaths& paths) try : _fileErr(), _processList(), _json(paths.configPath), \
_modulePaths(), _paths(), _certificatePath(), _CgiDir()
{
    std::string pathDirclean;
    _fileErr.open(paths.configPath);
    if (!_fileErr)
        throw ErrorConfigPath();
    size_t found = paths.dirPath.find_last_of("/");
    if (found == std::string::npos) {
        pathDirclean = paths.dirPath + "/";
        _paths.dirPath = pathDirclean;
    } else
        _paths.dirPath = paths.dirPath;    
    _paths.configPath = paths.configPath;
    load();
} catch (Error const &err) {
    throw err;
}

void configHandler::fileExists(const std::filesystem::path& p)
{
    std::filesystem::file_status s = std::filesystem::file_status{};
    if(std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p))
        return;
    else
        throw ErrorConfigPhpFile();
}

void configHandler::checkTag(std::string line)
{
    std::string tag = line;
    std::string path = line;
    std::size_t found = line.find("\"");
    std::size_t foundLast = line.find("\"", found+1);
    std::size_t foundPath = line.find("\"", foundLast+1);
    std::size_t foundPath_s = line.find("\"", foundPath+1);
        
    if (found == std::string::npos || foundLast == std::string::npos || foundPath == std::string::npos || foundPath_s == std::string::npos)
        return;
    foundLast -= found;
    found++;
    foundLast--;
    foundPath_s -= foundPath;
    foundPath++;
    foundPath_s--;
    tag = tag.substr(found, foundLast);
    path = path.substr(foundPath, foundPath_s);
    if (tag == "SSL Certificate Path") {
        _certificatePath = path;
        fileExists(_certificatePath);
    } else if (tag == "CGI Dir Path") {
        _CgiDir = path;
        fileExists(_CgiDir);
    }
}

void configHandler::load()
{
    _json.loadConfigFile();
    std::string line("");
    std::string name("");
    bool PosModule = false;
    std::ifstream jsonFile(_paths.configPath);
    size_t endModule = std::string::npos;

    try {
        while (std::getline(jsonFile, line, '\n')) {
            checkTag(line);
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

std::string configHandler::getCgiPath()const
{
    return _CgiDir;
}

std::string configHandler::getCertificatePath()const
{
    return _certificatePath;
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
    std::size_t foundLast = line.find("\"", found+1);

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