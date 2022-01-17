//
// Created by abous on 17/01/2022.
//

#include "Graph.hpp"

using namespace std;

Graph::Graph() {

}

int Graph::getNumberOfVertices() {
    return static_cast<int>(vertices.size());
}

int Graph::insertVertex(MyVertex v) {
    if (find(vertices.begin(), vertices.end(), v) != vertices.end()) return -1;
    vertices.push_back(v);

    return static_cast<int>(vertices.size() - 1);
}

vector<MyVertex> Graph::getVertices() {
    return vertices;
}

int Graph::getEdgeWeight(MyVertex v1, MyVertex v2) {
    const auto v1Idx = find(vertices.begin(), vertices.end(), v1);
    const auto v2Idx = find(vertices.begin(), vertices.end(), v2);
    if (v1Idx == vertices.end() || v2Idx == vertices.end()) return -1;
}

bool Graph::insertEdge(MyVertex v1, MyVertex v2, int weight) {
    const Edge edge(v1, v2, weight);
    edges.push_back(edge);

    return true;
}

vector<vector<int>> Graph::getAdjacencyMatrix() {
    vector<vector<int>> matrix(vertices.size(), vector<int>(vertices.size(), -1));

    for (size_t i = 0; i < vertices.size(); ++i) {
        matrix[i][i] = 0;
    }

    return matrix;
}