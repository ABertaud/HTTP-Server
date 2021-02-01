/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

class INetwork {
    public:
        virtual ~INetwork() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
    protected:
    private:
        virtual void startAccept() = 0;
};

#endif /* !INETWORK_HPP_ */
