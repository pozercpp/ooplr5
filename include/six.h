#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Six : public Figure<T> {
public:
    Six();
    Six(const std::initializer_list<Point<T>>&);
    ~Six();
};

#include<six.ipp>