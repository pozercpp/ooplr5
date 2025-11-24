#pragma once

#include <eight.h>

template<class T>
Eight<T>::Eight() : Figure<T>(8) {}

template<class T>
Eight<T>::Eight(const std::initializer_list<Point<T>>& lst) : Figure<T>(lst) {
    if (lst.size() != 8) {
        throw std::invalid_argument("Five must have exactly 8 points");
    }
}

template<class T>
Eight<T>::~Eight() = default;