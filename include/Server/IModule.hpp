/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include "moduleType.hpp"
#include "HTTPObject.hpp"

class IModule {
    public:
    virtual ~IModule() = default;
    virtual void processRequest(HTTP::HTTPObject& req) = 0;
    virtual moduleType getModuleType()= 0;
    private:
};

#endif /* !IMODULE_HPP_ */
