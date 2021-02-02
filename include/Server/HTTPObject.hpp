/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** HTTPObject
*/

#ifndef HTTPOBJECT_HPP_
#define HTTPOBJECT_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <utility>

namespace HTTP {

    enum reqElem {STARTLINES, HEADERS, BODY};
    enum HTTPType {REQ, RES};
    using reqType = std::unordered_map<std::string, std::vector<std::string>>;

    class HTTPObject {
        public:
            HTTPObject(const std::string& request, const HTTP::HTTPType& type=HTTPType::REQ);
            HTTPObject()=default;
            ~HTTPObject()=default;
            HTTPObject(const HTTPObject& other)=default;
            HTTPObject& operator=(const HTTPObject& other)=default;
            HTTP::reqType& operator[](const HTTP::reqElem& elem);
        public:
            bool isElem(const reqElem& elem, const std::string& key);
            void deleteElemContent(const reqElem& elem, const std::string& key, std::size_t pos = std::string::npos);
            void modifyElemContent(const reqElem& elem, const std::string& key, const std::string& newVal, std::size_t pos = 0);
            std::string getElemConcatContent(const reqElem& elem, const std::string& key);
            std::string toString(void);
            int checkContent(void);
        private:
            void parseRequest(const std::string& request);
            void parseStartLine(const std::string& request);
            void parseHeaders(const std::string& request);
            void parseBody(const std::string& request);
        private:
            HTTP::HTTPType _type;
            HTTP::reqType _startLine;
            HTTP::reqType _headers;
            std::vector<std::string> _headersOrderList;
            HTTP::reqType _body;
    };
}

std::ostream &operator<<(std::ostream& os, HTTP::HTTPObject& obj);

#endif /* !HTTPOBJECT_HPP_ */
