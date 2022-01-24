//
// Created by abous on 17/01/2022.
//

#ifndef UE9_GRAPH_HPP
#define UE9_GRAPH_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <tuple>

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


static constexpr char const *enum_str[] = {"White", "Gray", "Black"};

class Graph {
private:
    enum Color {
        WHITE,
        GRAY,
        BLACK
    };

    struct Edge {
        MyVertex in;
        MyVertex out;
        int weight;

        Edge() = default;

        Edge(MyVertex _in, MyVertex _out, int _weight) : in(_in), out(_out), weight(_weight) {}
    };

    std::vector<Edge> edges;
    std::vector<MyVertex> vertices;

    size_t DFSVisit(size_t count, const MyVertex &v, std::vector<Color> &colors);

    bool DFSVisit(const MyVertex &v, std::vector<Color> &colors, bool isCyclic);

    std::tuple<size_t, bool>
    DFSVisit(const MyVertex &v, std::vector<Color> &colors, size_t count = 1, bool isCyclic = false);

    Color colorOfVertex(const MyVertex &v, const std::vector<Color> &colors);

    long long indexOfVertex(const MyVertex &v);

public:

    /* Erzeugt einen neuen Graphen */
    Graph();

    /* Fügt neuen Knoten v in den Graphen ein und liefert seinen Index
    im Knotenvector oder -1, wenn der Knoten bereits eingefügt ist */
    int insertVertex(MyVertex v);

    /* Fügt eine ungerichtete Kante mit dem Gewicht weight zwischen den
    Knoten in und out ein. Die Methode liefert false,
    falls die Kante bereits existiert, sonst true. */
    bool insertEdge(MyVertex in, MyVertex out, int weight);

    // Liefert true, wenn der Graph verbunden ist, sonst false.
    bool isConnected();

    // Liefert true, wenn der Graph Zyklen enthält, sonst false.
    bool isCyclic();

    /* Gibt die Anzahl der eingefügten Knoten zurück */
    int getNumberOfVertices();

    /* Gibt einen vector aller eingefügten Knoten zurück */
    std::vector<MyVertex> getVertices();

    /* Liefert das Gewicht der Kante zwischen Knoten in und out, wenn
    sie existiert, ansonsten -1. */
    int getEdgeWeight(const MyVertex &in, const MyVertex &out);

    /* Liefert eine NxN Adjazenzmatrix für diesen Graphen, wobei N =
    getNumVertices().
    Die Matrix enthält die Gewichte der Kanten (>=0). */
    std::vector<std::vector<int>> getAdjacencyMatrix();

    /* Liefert einen Vector von Knoten welche adjazent zum Knoten in
    sind. */
    std::vector<MyVertex> getAdjacentVertices(const MyVertex &in);

    // Gibt die Anzahl der Komponenten des Graphen zurück.
    int getNumberOfComponents();

    /* Gibt die Knoten aller Komponenten aus (eine Zeile pro
    Komponente). */
    void printComponents();
};


#endif //UE9_GRAPH_HPP
