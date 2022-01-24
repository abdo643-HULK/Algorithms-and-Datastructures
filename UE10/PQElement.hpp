//
// Created by abous on 24/01/2022.
//

#ifndef UE10_PQELEMENT_H
#define UE10_PQELEMENT_H

#include "MyVertex.hpp"

class PQElement {
public:
    MyVertex vertex;
    int priority;

    PQElement(MyVertex v, int p) : vertex(v), priority(p) {}

    inline bool operator<(const PQElement &rhs) const { return priority < rhs.priority; }

    inline bool operator>=(const PQElement &rhs) const { return !(*this < rhs); }

    inline bool operator>(const PQElement &rhs) const { return priority > rhs.priority; }

    inline bool operator<=(const PQElement &rhs) const { return !(*this > rhs); }
};

#endif //UE10_PQELEMENT_H
