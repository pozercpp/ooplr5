#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Eight : public Figure<T> {
public:
    Eight();
    Eight(const std::initializer_list<Point<T>>&);
    ~Eight();
};

#include<eight.ipp>