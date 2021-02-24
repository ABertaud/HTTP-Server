/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** ASocketHandler
*/

#ifndef ASOCKETHANDLER_HPP_
#define ASOCKETHANDLER_HPP_

#define BUFFER_SIZE (4096)

#include "requestManager.hpp"
#include "ISocketHandler.hpp"

class ASocketHandler : public ISocketHandler {
    public:
        ASocketHandler();
        void reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList);
        ASocketHandler(const ASocketHandler& other) = default;
        ASocketHandler& operator=(const ASocketHandler& other) = default;
        virtual ~ASocketHandler() = default;
    protected:
        std::string _message;
        requestManager _reqManager;
        char _data[BUFFER_SIZE];
    private:
        virtual void handleRead(const boost::system::error_code& err, size_t bytesTransferred) = 0;

};


#endif /* !ASOCKETHANDLER_HPP_ */
