/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule
*/

#ifndef PHPCGIMODULE_HPP_
#define PHPCGIMODULE_HPP_

#include "IModule.hpp"
#include <fstream>


class phpCgiModule : public IModule {
    public:
        phpCgiModule();
        void processRequest(HTTP::HTTPObject& req);
        void onReceive(const boost::asio::ip::tcp::socket& sock);
        void onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend);
        moduleType getModuleType() const;
        phpCgiModule(const phpCgiModule& other) = default;
        phpCgiModule& operator=(const phpCgiModule& other) = default;
        ~phpCgiModule() = default;
        void init(const std::string& path, boost::asio::ip::tcp::socket& sock);
    protected:
    private:
        std::string exec(const std::string& cmd);
        std::unordered_map<std::string, void (phpCgiModule::*)(HTTP::HTTPObject& req)> _methods;
        void helloWorld(HTTP::HTTPObject& req);
        
};


#endif /* !PHPCGIMODULE_HPP_ */
