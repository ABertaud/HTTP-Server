/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** jsonReader.hpp
*/


#ifndef JSONREADER_HPP_
#define JSONREADER_HPP_

#include <nlohmann/json.hpp>
#include <string>

class jsonReader {
    public:
        jsonReader(const std::string& configPath);
        nlohmann::json getJsonFile() const;
        void loadConfigFile();
        jsonReader(const jsonReader& other) = default;
        jsonReader& operator=(const jsonReader& other) = default;
        ~jsonReader() = default;
    private:
        std::string _configPath;
        nlohmann::json _jsonFile;
};

#endif /* !JSONREADER_HPP_ */
