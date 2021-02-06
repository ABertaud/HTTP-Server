/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testConfigHandler.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "configHandler.hpp"
#include "pathHandler.hpp"
#include "Error.hpp"
#include <iostream>
#include <sys/stat.h> 

Test(testPathSoError, configHandler)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"PHP_CGI\",\n",
        "            \"SSL_TSL\",\n",
        "            \"Snake\",\n",
        "            \"File_Server\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        configHandler ConfigHand(paths);
    }
    catch (Error &e) {
        cr_assert(std::strcmp(e.what(), "Error config file: one module doesn't exist") == 0);
    }
}

Test(TestTagErr, configHandler)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"Error\",\n",
        "            \"Error\",\n",
        "            \"Error\",\n",
        "            \"Error\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream outfile ("testErr.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "testErr.txt";
        configHandler ConfigHand(paths);
    }
    catch (Error &e) {
        cr_assert(std::strcmp(e.what(), "Error config file: the tag doesn't exist") == 0);
    }
}

/*Test(TestAllGood, configHandler)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"PHP_CGI\",\n",
        "            \"SSL_TSL\",\n",
        "            \"Snake\",\n",
        "            \"File_Server\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    mkdir("FileSo", 0777);
    std::ofstream phpSo ("FileSo/PHP_CGI.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/SSL_TSL.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/Snake.so");
    snakeSo.close();
    std::ofstream serverSo ("FileSo/File_Server.so");
    serverSo.close();
    std::ofstream outfile ("testErr.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "testErr.txt";
        paths.dirPath = "FileSo/";
        configHandler ConfigHand(paths);
    }
    catch (Error &e) {
        cr_assert(std::strcmp(e.what(), "Error config file: the tag doesn't exist") != 0);
    }
}*/