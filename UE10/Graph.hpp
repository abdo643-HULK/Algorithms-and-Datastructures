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
#include <queue>
#include <set>

#include "PQElement.hpp"

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
    im Knotenvektor oder -1, wenn der Knoten bereits eingefügt ist */
    int insertVertex(MyVertex v);

    /* Gibt die Anzahl der eingefügten Knoten zurück */
    int getNumberOfVertices();

    /* Gibt einen vector aller eingefügten Knoten zurück */
    std::vector<MyVertex> getVertices();

    /* Liefert das Gewicht der Kante zwischen Knoten in und out, wenn
    sie existiert, ansonsten -1. */
    int getEdgeWeight(const MyVertex &in, const MyVertex &out);

    /* Fügt eine ungerichtete Kante mit dem Gewicht weight zwischen den
    Knoten in und out ein. Die Methode liefert false,
    falls die Kante bereits existiert, sonst true. */
    bool insertEdge(MyVertex in, MyVertex out, int weight);

    /* Liefert eine NxN Adjazenzmatrix für diesen Graphen, wobei N =
    getNumVertices().
    Die Matrix enthält die Gewichte der Kanten (>=0). */
    std::vector<std::vector<int>> getAdjacencyMatrix();

    /* Liefert einen Vector von Knoten welche adjazent zum Knoten in
    sind. */
    std::vector<MyVertex> getAdjacentVertices(const MyVertex &in);

    /**
     * Berechnet die kürzesten Wege ausgehend von Knoten source und
     * gibt sowohl die Länge des kürzesten Pfades und die Knoten dieses
     *
     * Weges aus, z.B.:
     * Vertex[0]: Laenge=0, Weg= Vertex[0],
     * Vertex[1]: Laenge=7, Weg= Vertex[1], Vertex[3], Vertex[0],
     * Vertex[2]: Laenge=8, Weg= Vertex[2], Vertex[1], Vertex[3], Vertex[0],
     * Vertex[3]: Laenge=5, Weg= Vertex[3], Vertex[0],
     * Vertex[4]: Laenge=7, Weg= Vertex[4], Vertex[3], Vertex[0],
    */
    void shortestPathDijkstra(MyVertex source);
};


#endif //UE9_GRAPH_HPP
