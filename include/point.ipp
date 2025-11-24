#pragma once

#include <iostream>

#include<point.h>

template<class T>
Point<T>::Point() : x(0), y(0) {}

template<class T>
Point<T>::Point(T x_, T y_) : x(x_), y(y_) {}

template<class T>
std::istream& operator>>(std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    os << '(' << p.x << ' ' << p.y << ')';
    return os;
}

template<class T>
bool operator==(const Point<T>& a, const Point<T>& b) { return a.x == b.x && a.y == b.y; }

template<class T>
bool operator!=(const Point<T>& a, const Point<T>& b) { return !(a == b); }