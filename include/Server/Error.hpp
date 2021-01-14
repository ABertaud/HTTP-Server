/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Error.hpp
*/


#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <fstream>

class Error : public std::exception
{
    private:
        const std::string _message;

    public:
        Error(std::string const& message);
        Error(const Error& other) = default;
        const char *what() const noexcept override;
        Error& operator=(const Error& other) = default;
        ~Error() = default;
};

class ErrorJsonReader : public Error
{
    public:
        ErrorJsonReader(const std::string& err);
        ErrorJsonReader(const ErrorJsonReader& other) = default;
        ErrorJsonReader& operator=(const ErrorJsonReader& other) = default;
        ~ErrorJsonReader() = default;
};

class ErrorBadConfigPath : public ErrorJsonReader 
{
    public:
        ErrorBadConfigPath();
        ErrorBadConfigPath(const ErrorBadConfigPath& other) = default;
        ErrorBadConfigPath& operator=(const ErrorBadConfigPath& other) = default;
        ~ErrorBadConfigPath() = default;
};

#endif /* !ERROR_HPP_ */
