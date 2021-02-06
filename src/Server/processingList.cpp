/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** processingList
*/

#include "processingList.hpp"

void processingList::add(const moduleType &type, const unsigned int pos)
{
    if (pos > _list.size())
        _list.push_back(type);
    else {
        auto itPos = _list.begin() + pos;
        _list.insert(itPos, type);
    }
}

void processingList::remove(const unsigned int pos)
{
    auto sizeMax = (_list.size() - 1);
    if (pos > sizeMax)
        _list.erase(_list.begin() + static_cast<long int>(sizeMax));
    else
        _list.erase(_list.begin() + pos);
}

void processingList::clear()
{
    _list.clear();
}

moduleType processingList::getCurrentType() const
{
    if (_list.size() == 0)
        return (moduleType::NONE);
    return (_list.front());
}