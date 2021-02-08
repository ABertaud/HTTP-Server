/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Error.cpp
*/

#include "Error.hpp"

Error::Error(const std::string& err) : _message(err)
{
}

const char *Error::what() const noexcept
{
    return (_message.c_str());
}

ErrorJsonReader::ErrorJsonReader(const std::string& err) : Error(err)
{
}

ErrorBadConfigPath::ErrorBadConfigPath() : ErrorJsonReader("Error: The given path isn't valid.")
{
}


ErrorArgs::ErrorArgs(const std::string& err) : Error(err)
{
}

ErrorNbArgs::ErrorNbArgs() : ErrorArgs("Error: wrong number of arguments.")
{
}

ErrorConfigPath::ErrorConfigPath(): ErrorArgs("Error: the default's path or the path given as argument isn't valid.")
{
}

ErrorDirPath::ErrorDirPath() : ErrorArgs("Error: the path given as argument isn't a directory.")
{
}

ErrorConfigFile::ErrorConfigFile(const std::string& err) : Error(err)
{
}

ErrorConfigTag::ErrorConfigTag() : ErrorConfigFile("Error config file: the tag doesn't exist")
{
}

ErrorConfigSo::ErrorConfigSo() : ErrorConfigFile("Error config file: one module doesn't exist")
{
}