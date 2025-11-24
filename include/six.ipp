#pragma once

#include <six.h>

template<class T>
Six<T>::Six() : Figure<T>(6) {}

template<class T>
Six<T>::Six(const std::initializer_list<Point<T>>& lst) : Figure<T>(lst) {
    if (lst.size() != 6) {
        throw std::invalid_argument("Five must have exactly 6 points");
    }
}

template<class T>
Six<T>::~Six() = default;