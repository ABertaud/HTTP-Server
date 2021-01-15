/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** jsonReader.cpp
*/

#include "jsonReader.hpp"
#include "Error.hpp"
#include <iostream>

jsonReader::jsonReader(const std::string& configPath)
try : _configPath(configPath)
{
    loadConfigFile();
}
catch(const ErrorJsonReader& e)
{
    throw e;
}

nlohmann::json jsonReader::getJsonFile() const
{
    return (_jsonFile);
}

void jsonReader::loadConfigFile()
{
    std::ifstream config(_configPath);
    if (!config)
        throw ErrorBadConfigPath();
    _jsonFile = nlohmann::json::parse(config);
}