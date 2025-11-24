#pragma once

#include <five.h>

template<class T>
Five<T>::Five() : Figure<T>(5) {}

template<class T>
Five<T>::Five(const std::initializer_list<Point<T>>& lst) : Figure<T>(lst) {
    if (lst.size() != 5) {
        throw std::invalid_argument("Five must have exactly 5 points");
    }
}

template<class T>
Five<T>::~Five() = default;