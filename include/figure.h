#pragma once

#include<iostream>
#include <sstream>
#include<initializer_list>
#include<cmath>

#include<array.h>
#include<point.h>

template<class T> class Figure;

template<class T>
bool operator==(const Figure<T>&, const Figure<T>&);

template<class T>
bool operator!=(const Figure<T>&, const Figure<T>&);

template<class T>
std::istream& operator>>(std::istream&, Figure<T>&);

template<class T>
std::ostream& operator<<(std::ostream&, Figure<T>&);

template<class T> class Figure {
public:
    long double Area();
    Point<T> Centr();

    Figure(size_t);
    Figure(const std::initializer_list<Point<T>>&);

    friend bool operator== <>(const Figure<T>&, const Figure<T>&);
    friend bool operator!= <>(const Figure<T>&, const Figure<T>&);

    friend std::istream& operator>> <>(std::istream&, Figure<T>&);
    friend std::ostream& operator<< <>(std::ostream&, Figure<T>&);

    void ReadPoints(std::istream&);
    void PrintPoints(std::ostream&);

protected:
    Array<Point<T>> v;
    long double CalcArea(const Array<Point<T>>&) const;
    Point<T> CalcCentr(const Array<Point<T>>&) const;
};

#include<figure.ipp>