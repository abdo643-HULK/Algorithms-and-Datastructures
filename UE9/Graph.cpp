//
// Created by abous on 17/01/2022.
//

#include "Graph.hpp"

using namespace std;

Graph::Graph() = default;

// instead of returning a tuple I could just take a reference to count and isCyclic and make it void
tuple<size_t, bool> Graph::DFSVisit(const MyVertex &v, vector<Color> &colors, size_t count, bool isCyclic) {
    colors[indexOfVertex(v)] = GRAY;

    for (const auto &adjVertex: getAdjacentVertices(v)) {
        const auto color = colorOfVertex(adjVertex, colors);
        if (color == WHITE) {
            tie(count, isCyclic) = DFSVisit(adjVertex, colors, ++count, isCyclic);
        }
        if (color == GRAY) isCyclic = true;
    }

    colors[indexOfVertex(v)] = BLACK;
    return make_tuple(count, isCyclic);
}


bool Graph::DFSVisit(const MyVertex &v, vector<Color> &colors, bool isCyclic) {
    colors[indexOfVertex(v)] = GRAY;

    for (const auto &adj_vertex: getAdjacentVertices(v)) {
        const auto color = colorOfVertex(adj_vertex, colors);
        if (color == GRAY) return isCyclic = true;
        else if (color == WHITE) return isCyclic = DFSVisit(adj_vertex, colors, isCyclic);
    }

    colors[indexOfVertex(v)] = BLACK;

    return false;
}


size_t Graph::DFSVisit(size_t count, const MyVertex &v, vector<Color> &colors) {
    colors[indexOfVertex(v)] = GRAY;

    for (const auto &adj_vertex: getAdjacentVertices(v)) {
        if (colorOfVertex(adj_vertex, colors) != WHITE) continue;
        count = DFSVisit(++count, adj_vertex, colors);
    }

    colors[indexOfVertex(v)] = BLACK;

    return count;
}

Graph::Color Graph::colorOfVertex(const MyVertex &v, const vector<Color> &colors) {
    const auto it = find(vertices.begin(), vertices.end(), v);
    return it != vertices.end() ? colors[it - vertices.begin()] : WHITE;
}

long long Graph::indexOfVertex(const MyVertex &v) {
    const auto it = find(vertices.begin(), vertices.end(), v);
    return it - vertices.begin();
}

int Graph::insertVertex(const MyVertex v) {
    if (find(vertices.begin(), vertices.end(), v) != vertices.end()) return -1;
    vertices.push_back(v);

    return static_cast<int>(vertices.size() - 1);
}

bool Graph::insertEdge(MyVertex in, MyVertex out, int weight) {
    insertVertex(in);
    insertVertex(out);

    const auto it = find_if(edges.begin(), edges.end(), [&](const Edge &edge) {
        return edge.in == in && edge.out == out;
    });

    if (it != edges.end()) return false;

    const Edge edge(in, out, weight);
    edges.push_back(edge);

    return true;
}

int Graph::getNumberOfVertices() {
    return static_cast<int>(vertices.size());
}

vector<MyVertex> Graph::getVertices() {
    return {vertices};
}

int Graph::getEdgeWeight(const MyVertex &in, const MyVertex &out) {
    const auto it = find_if(edges.begin(), edges.end(), [&](const Edge &edge) {
        return edge.in == in && edge.out == out;
    });

    return it != edges.end() ? it->weight : -1;
}

vector<vector<int>> Graph::getAdjacencyMatrix() {
    vector<vector<int>> matrix(vertices.size(), vector<int>(vertices.size(), -1));

    int i = 0, j = -1;
    for (const auto &v1: vertices) {
        for (const auto &v2: vertices) {
            matrix[i][++j] = getEdgeWeight(v1, v2);
        }
        j = -1;
        ++i;
    }

    return matrix;
}

vector<MyVertex> Graph::getAdjacentVertices(const MyVertex &in) {
    vector<MyVertex> list;
    list.reserve(static_cast<unsigned long long>(vertices.size() * 0.3));

    if (find(vertices.begin(), vertices.end(), in) == vertices.end()) return list;

    for (const auto &out: vertices) {
        if (getEdgeWeight(in, out) == -1) continue;
        list.push_back(out);
    }

    return list;
}

bool Graph::isConnected() {
    vector<Color> colors(vertices.size(), WHITE);

    size_t idx = 0;
    for (const auto &v: vertices) {
        if (colorOfVertex(v, colors) != WHITE) continue;
//        const auto count = get<0>(DFSVisit(v, colors, idx));
        const auto count = DFSVisit(idx, v, colors);
        if (vertices.size() < count) return false;
    }

    return true;
}

bool Graph::isCyclic() {
    vector<Color> colors(vertices.size(), WHITE);

    for (const auto &v: vertices) {
        if (colorOfVertex(v, colors) != WHITE) continue;
        if (DFSVisit(v, colors, false)) return true;
    }

//    bool isCyc = false;
//    for (const auto &v: vertices) {
//        isCyc = get<1>(DFSVisit(v, colors, 0, isCyc));
//        if (isCyc) return true;
//    }

    return false;
}

int Graph::getNumberOfComponents() {
    // Color every vertex white (unvisited)
    vector<Color> colors(vertices.size(), WHITE);

    int connectedComponents = 0;
    for (const auto &v: vertices) {
        if (colorOfVertex(v, colors) != WHITE) continue;

        DFSVisit(0, v, colors);
        ++connectedComponents;
    }

    return connectedComponents;
}

void Graph::printComponents() {
    vector<Color> colors(vertices.size(), WHITE);

    size_t idx = 0;
    for (const auto &v: vertices) {
        if (colorOfVertex(v, colors) != WHITE) continue;

//        const auto count = get<0>(DFSVisit(v, colors, idx));
        const auto count = DFSVisit(idx, v, colors);

//        cout << "Component (" << idx << "-" << count << "): ";
        cout << "Component: ";
        for (auto i = idx; i <= count; ++i) {
            cout << vertices[i] << " ";
        }
        cout << "\n";

        idx = count + 1;
    }
    cout << flush;
}