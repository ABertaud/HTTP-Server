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

// HTTP CODES -> https://developer.mozilla.org/fr/docs/Web/HTTP/Status

/** Success Resonses **/
// 200 OK
// 201 Created
// 202 Accepted
// 203 Non-Authoritative Information
// 204 No Content
// 205 Reset Content
// 206 Partial Content
// 207 Multi-Status
// 208 Multi-Status
// 226 IM Used

/** Redirect Messages **/
// 300 Multiple Choice
// 301 Moved Permanently
// 302 Found
// 303 See Other
// 304 Not Modified
// 305 Use Proxy
// 306 unused
// 307 Temporary Redirect
// 308 Permanent Redirect

/** Error Responses Client-Side **/
// 400 Bad Request
// 401 Unauthorized
// 402 Payment Required
// 403 Forbidden
// 404 Not Found
// 405 Method Not Allowed
// 406 Not Acceptable
// 407 Proxy Authentification Required
// 408 Request Timeout
// 409 Conflict
// 410 Gone
// 411 Length Required
// 412 Precondition Failed
// 413 Payload Too Large
// 414 URI Too Long
// 415 Unsupported Media Type
// 416 Request Range Not Satisfiable
// 417 Expectation Failed
// 418 I'm a teapot
// 421 Misdirected REquest
// 422 Unprocessable Entity
// 423 Locked
// 424 Failed Dependency
// 426 Upgrade Required
// 428 Precondition Required
// 429 Too Many Requests
// 431 Request Header Fields Too Large
// 451 Unavailable For Legal Reasons

/** Error Responses Server-Side **/
// 500 Internal Server Error
// 501 Not Implemented
// 502 Bad Gateway
// 503 Service Unavailable
// 504 Gateway Timeout
// 505 HTTP Version Not Supported
// 506 Variant Also Negotiates
// 507 Insufficient Storage
// 508 Loop Detected
// 510 Not Extended
// 511 Network Authentication Required


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
            std::vector<std::string> strToStringVector(const std::string& str, const std::string& delim);
            void createResponse(const std::string& httpCode, const std::string& body="");
            void clear(void);
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
