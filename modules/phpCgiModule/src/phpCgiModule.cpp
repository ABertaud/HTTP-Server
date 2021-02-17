/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule.cpp
*/

#include "phpCgiModule.hpp"
#include <memory>

phpCgiModule::phpCgiModule()
{
    _methods.insert(std::make_pair("helloWorld", &phpCgiModule::helloWorld));
}

void phpCgiModule::helloWorld(HTTP::HTTPObject& req)
{
    (void)req; 
}

void phpCgiModule::processRequest(HTTP::HTTPObject& req)
{
    std::string phpFile = req[HTTP::BODY]["Body"][0];
    std::ofstream tmpFile ("tmp.php");

    tmpFile << phpFile;
    tmpFile.close();
    std::string output = exec("php-cgi tmp.php");
    std::cout << "output =" << output <<std::endl;
    std::remove("tmp.php");
    req.setBody(output);
}

void phpCgiModule::init(const std::string& path, boost::asio::ip::tcp::socket& sock) 
{ 
    (void)path; 
    (void)sock;
}

std::string phpCgiModule::exec(const std::string& cmd) 
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe)
        return std::string("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void phpCgiModule::onReceive(const boost::asio::ip::tcp::socket& sock)
{
    (void)sock;
}

void phpCgiModule::onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend)
{
    (void)sock;
    (void)toSend;
}

moduleType phpCgiModule::getModuleType() const
{
    return (moduleType::PHPCGI);
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<phpCgiModule>(new phpCgiModule));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<phpCgiModule>());
    }

#endif
