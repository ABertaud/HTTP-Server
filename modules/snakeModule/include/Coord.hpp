/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Coord
*/

#ifndef COORD_HPP_
#define COORD_HPP_

#define MAX_LENGTH 10

class Coord {
    public:
        Coord() = default;
        Coord(const int ab, const int ord);
        Coord(const Coord& other) = default;
        Coord& operator+(const Coord& other);
        Coord& operator+=(const Coord& other);
        bool operator==(const Coord& other) const;
        Coord& operator=(const Coord& other) = default;
        ~Coord() = default;
        int x;
        int y;
};

#endif /* !COORD_HPP_ */
