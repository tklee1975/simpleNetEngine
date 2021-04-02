//
//  Vector.h
//  SimpleNet
//
//  Created by kenlee on 31/3/2021.
//
#pragma once
#include <vector>

namespace simpleNet {

//    template<class T>
//    using SNVector = std::vector<T>;     // Reference: https://en.cppreference.com/w/cpp/language/type_alias

    template < class T >
    class SNVector : public std::vector<T>
    {
    };

}
