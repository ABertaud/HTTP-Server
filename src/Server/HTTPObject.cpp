/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** HTTPObject
*/

#include "HTTPObject.hpp"
#include "Error.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>

HTTP::HTTPObject::HTTPObject(const std::string& request, const HTTP::HTTPType& type)
try : _type(type)
{
    parseRequest(request);
    checkContent();

} catch(const ErrorHTTPObject& e)
{
    throw e;
}

HTTP::reqType& HTTP::HTTPObject::operator[](const HTTP::reqElem& elem)
{
    if (elem == HTTP::STARTLINES)
        return (_startLine);
    else if (elem == HTTP::HEADERS)
        return (_headers);
    else
        return (_body);
}

bool HTTP::HTTPObject::isElem(const reqElem& elem, const std::string& key)
{
    if (this->operator[](elem).count(key) == 0)
        return (false);
    return (true);
}

std::string HTTP::HTTPObject::getElemConcatContent(const reqElem& elem, const std::string& key)
{
    std::string toReturn;

    if (!isElem(elem, key))
        return (toReturn);
    for (std::size_t i = 0; i != this->operator[](elem)[key].size(); i++) {
        toReturn += this->operator[](elem)[key][i];
    }
    return (toReturn);
}

void HTTP::HTTPObject::deleteElemContent(const reqElem& elem, const std::string& key, std::size_t pos)
{
    std::size_t size = 0;

    if (!isElem(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") != 0)))
        return;
    size = this->operator[](elem)[key].size();
    if (size > 0) {
        if (pos == std::string::npos) {
            for (std::size_t i = 0; i != size; i++)
                this->operator[](elem)[key][i].clear();
        }
        else if (pos <= size)
            this->operator[](elem)[key][pos].clear();
    }
}

void HTTP::HTTPObject::modifyElemContent(const reqElem& elem, const std::string& key, const std::string& newVal, std::size_t pos)
{
    std::size_t size = 0;

    if (!isElem(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") != 0)))
        return;
    size = this->operator[](elem)[key].size();
    for (std::size_t i = 0; i != size; i++) {
        this->operator[](elem)[key][i] = newVal;
    }
}

void HTTP::HTTPObject::parseRequest(const std::string& request)
{
    if (request.empty())
        throw (ErrorBadRequest("Error: Request is empty."));
    parseStartLine(request);
    parseHeaders(request);
    parseBody(request);
}

void HTTP::HTTPObject::parseStartLine(const std::string& request)
{
    std::string strRaw = request.substr(0, request.find_first_of('\n'));
    std::string strMethod = strRaw.substr(0, strRaw.find_first_of(' '));
    std::string strTarget = strRaw.substr(strRaw.find_first_of(' ')+1, (strRaw.find_last_of(' ')-strMethod.size()-1));
    std::string strVersion = strRaw.substr(strRaw.find_last_of(' ')+1, strRaw.size());

    if (strMethod.compare("GET") == 0 || strMethod.compare("POST") == 0 ||\
    strMethod.compare("DELETE") == 0 || strMethod.compare("PUT") == 0) {
        _startLine["Raw"].push_back(strRaw);
        _startLine["Method"].push_back(strMethod);
        _startLine["Target"].push_back(strTarget);
        _startLine["Version"].push_back(strVersion);
    }
    else
        throw (ErrorBadRequest("Error: Unknown HTTP Method"));
}

void HTTP::HTTPObject::parseHeaders(const std::string& request)
{
    std::size_t first = request.find_first_of('\n')+1;
    std::size_t last = request.find_last_of('\n');
    std::string header = request.substr(first, last - first + 1);
    std::string headerCpy = header;
    std::vector<std::string> strs;
    std::string elem;
    std::string key;

    if (header.empty())
        throw ErrorNoHost();
    header[header.find_last_of('\n')] = '\0';
    boost::replace_all(headerCpy, "\n", "\\n");
    _headers["Raw"].push_back(headerCpy);
    boost::split(strs, header, boost::is_any_of("\n"), boost::token_compress_on);
    for (std::size_t i = 0; i < strs.size(); i++) {
        if (!strs[i].empty()) {
            elem = strs[i].substr(0, strs[i].find_first_of(':'));
            key = strs[i].substr(strs[i].find_first_of(':')+2, strs[i].size());
            if (!elem.empty() && !key.empty()) {
                _headers[elem].push_back(key);
                _headersOrderList.push_back(elem);
            }
        }
    }
}

void HTTP::HTTPObject::parseBody(const std::string& request)
{
    std::string body = request.substr(request.find_last_of('\n')+1, request.size());
    _body["Body"].push_back(body);
}

std::string HTTP::HTTPObject::toString(void)
{
    std::string result;
    std::string s;

    result += getElemConcatContent(HTTP::STARTLINES, "Raw")+"\n";
    for (std::size_t i = 0; i < _headersOrderList.size(); ++i) {
        s = _headersOrderList[i];
        result += s+": "+getElemConcatContent(HTTP::HEADERS, s)+"\n";
    }
    if (!getElemConcatContent(HTTP::BODY, "Body").empty()) {
        for (auto& it: this->operator[](HTTP::BODY))
            result += "\n"+getElemConcatContent(HTTP::BODY, it.first);
    }
    return (result);
}

int HTTP::HTTPObject::checkContent(void)
{
    int contentLength = 0;
    int bodySize = 0;

    if (getElemConcatContent(HTTP::BODY, "Body").empty())
        return (0);
    if (getElemConcatContent(HTTP::HEADERS, "Host").empty())
        throw ErrorNoHost();
    contentLength = std::stoi(this->operator[](HTTP::HEADERS)["Content-Length"][0]);
    bodySize = getElemConcatContent(HTTP::BODY, "Body").size();
    if (contentLength < 0 || contentLength != bodySize)
        throw ErrorContentSize();
    return (0);
}

std::ostream& operator<<(std::ostream& os, HTTP::HTTPObject& obj)
{
    os << "[HTTPObject Display]" << std::endl;
    os << "-- START LINE --" << std::endl;

    for (auto &it: obj.operator[](HTTP::STARTLINES))
        os << it.first+": " << "'"+it.second[0]+"'" << std::endl;
    os << "-- HEADER-- " << std::endl;
    for (auto& it: obj.operator[](HTTP::HEADERS))
        os << it.first+": " << "'"+it.second[0]+"'" << std::endl;
    os << "-- BODY-- " << std::endl;
    for (auto& it: obj.operator[](HTTP::BODY))
        os << it.first+": " << "'"+it.second[0]+"'" << std::endl;
    return (os);
}