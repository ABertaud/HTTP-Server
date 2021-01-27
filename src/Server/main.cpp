/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** main.cpp
*/

#include <nlohmann/json.hpp>
#include <iostream>
#include "Error.hpp"
#include "serverCore.hpp"
#include "pathHandler.hpp"

int main(int ac, char **av)
{

    // std::unordered_map<std::string, std::vector<std::string>> lines;

    // lines["koko"].push_back("hey");
    // for (auto& line: lines["koko"])
    //     std::cout << line << std::endl;

    try
    {
        pathHandler hdl(pathType::REGULAR_FILE);
        if (ac > 2)
            throw ErrorNbArgs();
        else if (ac == 2)
            hdl.setPath(av[1]);
        if (hdl.isFileValid() == false)
            throw ErrorConfigPath();
        boost::asio::io_context ioContext;
        serverCore server(ioContext, hdl.getPath());
        server.start();
    } catch (Error& e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (nlohmann::json::exception const &jsonErr) {
        std::cout << jsonErr.what();
        return (84);
    } catch(boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }

    // std::string filename = "../jsonFiles/config.json";
    // try {
    //     jsonReader reader(filename);
    //     std::cout << reader.getJsonFile();
    // } catch (Error const &err) {
    //     std::cout << err.what();
    //     return (84);
    return (0);
}