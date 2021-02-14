/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "IModule.hpp"
#include "Coord.hpp"

class Snake : public IModule {
    public:
        Snake();
        void processRequest(HTTP::HTTPObject& req);
        void onReceive(const boost::asio::ip::tcp::socket& sock);
        void onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend);
        Coord getSnakePos() const;
        Coord getApplePos() const;
        unsigned int getEatenApples() const;
        moduleType getModuleType() const;
        Snake(const Snake& other) = default;
        Snake& operator=(const Snake& other) = default;
        ~Snake() = default;
    protected:
    private:
        void spawnApple();
        void post(HTTP::HTTPObject& req);
        void remove(HTTP::HTTPObject& req);
        void put(HTTP::HTTPObject& req);
        void get(HTTP::HTTPObject& req);
        Coord _snakeCoord;
        Coord _appleCoord;
        unsigned int _eatenApples;
        std::unordered_map<std::string, Coord> _movements;
        std::unordered_map<std::string, void (Snake::*)(HTTP::HTTPObject& req)> _methods;
};

#endif /* !SNAKE_HPP_ */
