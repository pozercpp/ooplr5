#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Five : public Figure<T> {
public:
    Five();
    Five(const std::initializer_list<Point<T>>&);
    ~Five();
};

#include<five.ipp>