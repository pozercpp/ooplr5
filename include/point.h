#pragma once
#include <iostream>

template<class T> class Point;

template<class T>
std::istream& operator>>(std::istream&, Point<T>&);

template<class T>
std::ostream& operator<<(std::ostream&, const Point<T>&);

template<class T>
bool operator==(const Point<T>&, const Point<T>&);

template<class T>
bool operator!=(const Point<T>&, const Point<T>&);

template<class T> 
class Point {
public:
    T x, y;

    Point();
    Point(T, T);
    
    friend std::istream& operator>> <>(std::istream&, Point<T>&);
    friend std::ostream& operator<< <>(std::ostream&, const Point<T>&);
    friend bool operator== <>(const Point<T>&, const Point<T>&);
    friend bool operator!= <>(const Point<T>&, const Point<T>&);
};

#include <point.ipp>