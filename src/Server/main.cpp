/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** main.cpp
*/

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "jsonReader.hpp"

int main(void)
{
    std::string filename = "./jsonFiles/config.json";
    try {
        jsonReader reader(filename);
    } catch (std::exception const &err) {
        std::cout << err.what();
        return (84);
    }
    return (0);
}