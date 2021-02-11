/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** HTTPObject
*/

#include "HTTPObject.hpp"
#include "Error.hpp"
// #include <boost/algorithm/string.hpp>
// #include <boost/algorithm/string/replace.hpp>

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

bool HTTP::HTTPObject::isKey(const reqElem& elem, const std::string& key)
{
    if (this->operator[](elem).count(key) == 0)
        return (false);
    return (true);
}

std::string HTTP::HTTPObject::getElemConcatContent(const reqElem& elem, const std::string& key, bool displayMode)
{
    std::string toReturn;

    if (!isKey(elem, key))
        return (toReturn);
    for (std::size_t i = 0; i != this->operator[](elem)[key].size(); i++) {
        if (!this->operator[](elem)[key][i].empty())
            toReturn += this->operator[](elem)[key][i];
        if (displayMode)
            toReturn += '\n';
    }
    return (toReturn);
}

void HTTP::HTTPObject::deleteElemContent(const reqElem& elem, const std::string& key, std::size_t pos)
{
    std::size_t size = 0;

    if (!isKey(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") == 0)))
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

void HTTP::HTTPObject::modifyElemContent(const reqElem& elem, const std::string& key, const std::string& newVal, [[maybe_unused]]std::size_t pos)
{
    std::size_t size = 0;

    if (!isKey(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") != 0)))
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

void HTTP::HTTPObject::createParamsMap(const std::string& strParams)
{
    std::vector<std::string> vec;
    std::string p1;
    std::string p2;
    std::size_t pos = 0;

    vec = strToStringVector(strParams, "&");
    // check if / after the arguments
    // like this -> param=2&super=cool/roblox

    for (size_t i = 0; i != vec.size(); i++) {
        if (!vec.at(i).empty() && (vec.at(i).find("=") != std::string::npos)) {
            pos = vec.at(i).find("=");
            p1 = vec.at(i).substr(0, pos);
            p2 = vec.at(i).substr(pos+1, vec.at(i).size()+pos);
            _params[p1] = p2;
        }
    }
}

std::string& HTTP::HTTPObject::getParams(const std::string& param)
{
    if (_params.count(param) != 0)
        return (_params[param]);
    else
        throw ErrorRequestParams("Error: Param was not found");
}

void HTTP::HTTPObject::parseTarget(std::string& target)
{
    std::vector<std::string> vec;
    bool isParams = false;

    // maybe decode the target as it may be encoded and or check

    if ((target.find('?') != std::string::npos)) {
        isParams = true;
        vec = strToStringVector(target, "?");
        _startLine["Target"].push_back(vec.at(1));
        target = vec.at(0);
    }
    vec = strToStringVector(target, "/");
    for (size_t i = 0; i != vec.size(); i++) {
        if (!vec.at(i).empty())
            _startLine["Target"].push_back(vec.at(i));
    }
    if (isParams) {
        createParamsMap(_startLine["Target"][1]);
        _startLine["Target"].erase((_startLine["Target"].begin() + 1));
    }
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
        parseTarget(strTarget);
        _startLine["Version"].push_back(strVersion);
    }
    else
        throw (ErrorBadRequest("Error: Unknown HTTP Method"));
}

std::vector<std::string> HTTP::HTTPObject::strToStringVector(const std::string& str, const std::string& delim)
{
    std::vector<std::string> toReturn;
    std::string word = "";

    if (str.find(delim) == std::string::npos) {
        toReturn.push_back(str);
        return (toReturn);
    }

    for (auto x : str)
    {
        if (x == delim.c_str()[0]) {
            if (word.compare(delim) != 0)
                toReturn.push_back(word);
            word = "";
        }
        else
            word = word + x;
    }
    if (word.compare(delim) != 0)
        toReturn.push_back(word);
    return (toReturn);
}

void HTTP::HTTPObject::parseHeaders(const std::string& request)
{
    std::size_t first = request.find_first_of('\n')+1;
    std::size_t last = request.find_last_of('\n');
    std::string header = request.substr(first, last - first + 1);
    std::vector<std::string> strs;
    std::string elem;
    std::string key;

    if (header.empty())
        throw ErrorNoHost();
    header[header.find_last_of('\n')] = '\0';
    _headers["Raw"].push_back(header);
    // boost::split(strs, header, boost::is_any_of("\n"), boost::token_compress_on);
    strs = strToStringVector(header, "\n");
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

HTTP::HTTPObject& HTTP::HTTPObject::createResponse([[maybe_unused]]const std::string& httpCode, const std::string& body)
{
    std::string strRes;

    clear();
    strRes = "HTTP/1.1 200 OK";
    _startLine["Raw"].push_back(strRes);
    _startLine["Version"].push_back("HTTP/1.1");
    _startLine["Code"].push_back("200");
    _startLine["Description"].push_back("OK");

    if (!body.empty()) {
        _headers["Content-Length"].push_back(std::to_string(body.size()));
        _headersOrderList.push_back("Content-Length");
        _body["Body"].push_back(body);
    }
    _type = HTTP::RES;
    return (*this);
}

void HTTP::HTTPObject::clear(void)
{
    _startLine.clear();
    _headers.clear();
    _headersOrderList.clear();
    _body.clear();
}

void HTTP::HTTPObject::parseBody(const std::string& request)
{
    std::string body = request.substr(request.find_last_of('\n')+1, request.size());
    if (!body.empty())
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
    if (getElemConcatContent(HTTP::HEADERS, "Content-Length").empty())
        throw ErrorBadRequest("Error: No 'Content-Length' field but with a body");
    contentLength = std::stoi(this->operator[](HTTP::HEADERS)["Content-Length"][0]);
    bodySize = getElemConcatContent(HTTP::BODY, "Body").size();
    if (contentLength < 0 || contentLength != bodySize)
        throw ErrorContentSize();
    return (0);
}