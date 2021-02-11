/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule
*/

#ifndef PHPCGIMODULE_HPP_
#define PHPCGIMODULE_HPP_

#include "IModule.hpp"

class phpCgiModule : public IModule {
    public:
        phpCgiModule();
        void processRequest(HTTP::HTTPObject& req);
        moduleType getModuleType() const;
        phpCgiModule(const phpCgiModule& other) = default;
        phpCgiModule& operator=(const phpCgiModule& other) = default;
        ~phpCgiModule() = default;
    protected:
    private:
};


#endif /* !PHPCGIMODULE_HPP_ */
