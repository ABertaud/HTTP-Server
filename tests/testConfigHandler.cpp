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
#include <cstdlib>
#include <filesystem>

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
        configHandler configHand(paths);
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
        configHandler configHand(paths);
    }
    catch (Error &e) {
        cr_assert(std::strcmp(e.what(), "Error config file: the tag doesn't exist") == 0);
    }
}

Test(TestAllGood, configHandler)
{
    std::filesystem::create_directories("FileSo");
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
    std::ofstream phpSo ("FileSo/PHP_CGI.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/SSL_TSL.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/Snake.so");
    snakeSo.close();
    std::ofstream serverSo ("FileSo/File_Server.so");
    serverSo.close();
    std::ofstream outfile ("test.txt");
    std::unordered_map<moduleType, std::string> modulePaths;
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        modulePaths = configHand.getListModules();
    }
    catch (Error &e) {
    }
    cr_assert_eq(modulePaths[moduleType::PHPCGI], "FileSo/PHP_CGI.so");
}

Test(TestgetModule, configHandler)
{
    int size = 0;
    std::filesystem::create_directories("FileSo");
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
    std::ofstream phpSo ("FileSo/PHP_CGI.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/SSL_TSL.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/Snake.so");
    snakeSo.close();
    std::ofstream serverSo ("FileSo/File_Server.so");
    serverSo.close();
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        auto& modulePaths = configHand.getListModules();
        modulePaths.clear();
        modulePaths = configHand.getListModules();
        size = modulePaths.size();
        cr_assert_eq(size, 0);
    }
    catch (Error &e) {
    }
}

Test(TestgetProcess, configHandler)
{
    int size = 0;
    std::filesystem::create_directories("FileSo");
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
    std::ofstream phpSo ("FileSo/PHP_CGI.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/SSL_TSL.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/Snake.so");
    snakeSo.close();
    std::ofstream serverSo ("FileSo/File_Server.so");
    serverSo.close();
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        processingList processList = configHand.getCopyProcessList();
        size = processList.getSize();
        cr_assert_eq(size, 4);
    }
    catch (Error &e) {
    }
}