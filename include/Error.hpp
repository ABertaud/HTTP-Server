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

class ErrorArgs : public Error
{
    public:
        ErrorArgs(const std::string& err);
        ErrorArgs(const ErrorArgs& other) = default;
        ErrorArgs& operator=(const ErrorArgs& other) = default;
        ~ErrorArgs() = default;
};

class ErrorNbArgs : public ErrorArgs
{
    public:
        ErrorNbArgs();
        ErrorNbArgs(const ErrorNbArgs& other) = default;
        ErrorNbArgs& operator=(const ErrorNbArgs& other) = default;
        ~ErrorNbArgs() = default;
};

class ErrorConfigPath : public ErrorArgs
{
    public:
        ErrorConfigPath();
        ErrorConfigPath(const ErrorConfigPath& other) = default;
        ErrorConfigPath& operator=(const ErrorConfigPath& other) = default;
        ~ErrorConfigPath() = default;
};

class ErrorDirPath : public ErrorArgs
{
    public:
        ErrorDirPath();
        ErrorDirPath(const ErrorDirPath& other) = default;
        ErrorDirPath& operator=(const ErrorDirPath& other) = default;
        ~ErrorDirPath() = default;
};

class ErrorConfigFile : public Error
{
    public:
        ErrorConfigFile(const std::string& err);
        ErrorConfigFile(const ErrorConfigFile& other) = default;
        ErrorConfigFile& operator=(const ErrorConfigFile& other) = default;
        ~ErrorConfigFile() = default;
};

class ErrorConfigTag : public ErrorConfigFile
{
    public:
        ErrorConfigTag();
        ErrorConfigTag(const ErrorConfigTag& other) = default;
        ErrorConfigTag& operator=(const ErrorConfigTag& other) = default;
        ~ErrorConfigTag() = default;
};

class ErrorConfigSo : public ErrorConfigFile
{
    public:
        ErrorConfigSo();
        ErrorConfigSo(const ErrorConfigSo& other) = default;
        ErrorConfigSo& operator=(const ErrorConfigSo& other) = default;
        ~ErrorConfigSo() = default;
};

#endif /* !ERROR_HPP_ */
