/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** processingList
*/

#ifndef PROCESSINGLIST_HPP_
#define PROCESSINGLIST_HPP_

#include "moduleType.hpp"
#include <vector>

class processingList {
    public:
    processingList() = default;
    void add(const moduleType& type, const unsigned int pos = 0);
    void remove(const unsigned int pos = 0);
    void clear();
    moduleType getCurrentType() const;
    std::vector<moduleType>& getList();
    size_t getSize()const;
    processingList(const processingList& other) = default;
    processingList& operator=(const processingList& other);
    ~processingList() = default;
private:
    std::vector<moduleType> _list;
};

#endif /* !PROCESSINGLIST_HPP_ */
