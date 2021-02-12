/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Snake
*/

#include "Snake.hpp"
#include <boost/algorithm/string.hpp>
#include <memory>
#include <iostream>

Snake::Snake(): _snakeCoord(Coord(0, 0)), _eatenApples(0)
{
    _movements.insert(std::make_pair("UP", Coord(0, -1)));
    _movements.insert(std::make_pair("DOWN", Coord(0, 1)));
    _movements.insert(std::make_pair("RIGHT", Coord(1, 0)));
    _movements.insert(std::make_pair("LEFT", Coord(-1, 0)));
    _methods.insert(std::make_pair("GET", &Snake::get));
    _methods.insert(std::make_pair("PUT", &Snake::put));
    _methods.insert(std::make_pair("DELETE", &Snake::remove));
    _methods.insert(std::make_pair("POST", &Snake::post));
    spawnApple();
}

void Snake::processRequest(HTTP::HTTPObject& req)
{
    if (req[HTTP::STARTLINES]["Target"][1] == "snake") {
        std::string method = req[HTTP::STARTLINES]["Method"][0];
        boost::to_upper(method);
        for (auto& met : _methods)
            if (met.first == method)
                (this->*(met.second))(req);
    }
}

void Snake::onReceive(const boost::asio::ip::tcp::socket& sock)
{
    (void)sock;
}

void Snake::onSend(const boost::asio::ip::tcp::socket& sock, const std::string& toSend)
{
    (void)sock;
    (void)toSend;
}

moduleType Snake::getModuleType() const
{
    return (moduleType::SNAKE);
}

void Snake::spawnApple()
{
    _appleCoord.x = rand() % MAX_LENGTH;
    _appleCoord.y = rand() % MAX_LENGTH;
}

void Snake::post(HTTP::HTTPObject& req)
{
    (void)req;
}

void Snake::remove(HTTP::HTTPObject& req)
{
    (void)req;
}

void Snake::put(HTTP::HTTPObject& req)
{
    (void)req;
}

void Snake::get(HTTP::HTTPObject& req)
{
    std::string param = req.getParams("arrow");
    boost::to_upper(param);
    for (auto& move : _movements)
        if (move.first == param)
            _snakeCoord += move.second;
    if (_snakeCoord == _appleCoord) {
        _eatenApples += 1;
        spawnApple();
    }
    std::cout << "x: " + std::to_string(_snakeCoord.x) + ", y: " + std::to_string(_snakeCoord.y) + ", apple_x: " + std::to_string(_appleCoord.x) + ", apple_y: " + std::to_string(_appleCoord.y) << std::endl;
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<Snake>(new Snake));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<Snake>());
    }

#endif