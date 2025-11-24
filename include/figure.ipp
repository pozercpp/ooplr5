#pragma once

#include <figure.h>

template<class T>
Figure<T>::Figure(size_t n) : v(n) {}

template<class T>
Figure<T>::Figure(const std::initializer_list<Point<T>>& lst) : v(lst) {}

template<class T>
long double Figure<T>::CalcArea(const Array<Point<T>>& t) const {
    long double res{0.0};
    for (int i = 0; i + 1 < t.size(); ++i) {
        res += t[i].x * static_cast<long double>(t[i + 1].y);
        res -= t[i + 1].x * static_cast<long double>(t[i].y);
    }
    res += static_cast<long double>(t[t.size() - 1].x) * static_cast<long double>(t[0].y);
    res -= static_cast<long double>(t[0].x) * static_cast<long double>(t[t.size() - 1].y);
    return std::abs(res / 2.0);
}

template<class T>
long double Figure<T>::Area() { 
    return CalcArea(v); 
}

template<class T>
Point<T> Figure<T>::CalcCentr(const Array<Point<T>>& t) const {
    T x{0}, y{0};
    for (int i = 0; i < t.size(); ++i) {
        x += t[i].x;
        y += t[i].y;
    }
    return Point<T>(x / static_cast<T>(t.size()), y / static_cast<T>(t.size()));
}

template<class T>
Point<T> Figure<T>::Centr() { 
    return CalcCentr(v); 
}

template<class T>
void Figure<T>::PrintPoints(std::ostream& os) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << "( " << v[i].x << ", " << v[i].y << ")";
        if (i + 1 < v.size()) {
            os << " ";
        }
    }
}

template<class T>
void Figure<T>::ReadPoints(std::istream& is) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i].x >> v[i].y;
    }
}

template<class T>
bool operator==(const Figure<T>& a, const Figure<T>& b) {
    if (a.v.size() != b.v.size()) { return false; }
    for (int i = 0; i < a.v.size(); ++i) {
        if (a.v[i] != b.v[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
bool operator!=(const Figure<T>& a, const Figure<T>& b) { 
    return !(a == b); 
}

template<class T>
std::istream& operator>>(std::istream& is, Figure<T>& f) {
    f.ReadPoints(is);
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, Figure<T>& f) {
    f.PrintPoints(os);
    return os;
}