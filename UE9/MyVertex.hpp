//
// Created by abous on 24/01/2022.
//

#ifndef UE9_MYVERTEX_HPP
#define UE9_MYVERTEX_HPP

#include <iostream>
#include <string>

struct MyVertex {
    // gets automatically initialized with an empty string
    const std::string name;

    MyVertex() = default;

    explicit MyVertex(std::string _name) : name(std::move(_name)) {}

    inline bool operator==(const MyVertex &rhs) const {
        return name == rhs.name;
    }

    inline bool operator!=(const MyVertex &rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const MyVertex &p) {
        os << "Vertex[" << p.name << "]";
        return os;
    }
};

#endif //UE9_MYVERTEX_HPP
