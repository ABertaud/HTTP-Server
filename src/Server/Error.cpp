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
