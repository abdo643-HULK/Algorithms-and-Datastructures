//
// Created by abous on 17/01/2022.
//

#include "main.hpp"

using namespace std;

int main() {
    Graph graph;
    MyVertex vertices1[] = {
            MyVertex("0"),
            MyVertex("1"),
            MyVertex("2"),
            MyVertex("3"),
            MyVertex("4"),
    };
    const auto vertices1Len = sizeof(vertices1) / sizeof(*vertices1);

    cout << "------------------- PART 1 -------------------" << "\n";

    for (const auto &vertex: vertices1) {
        graph.insertVertex(vertex);
    }

    cout << "Vertices in Graph: ";
    for (const auto &v: graph.getVertices()) {
        cout << v << " ";
    }
    cout << "\n" << "Number of Vertices: " << graph.getNumberOfVertices() << "\n";


    graph.insertEdge(vertices1[0], vertices1[1], 10);
    graph.insertEdge(vertices1[0], vertices1[3], 5);
    graph.insertEdge(vertices1[1], vertices1[2], 1);
    graph.insertEdge(vertices1[1], vertices1[3], 2);
    graph.insertEdge(vertices1[2], vertices1[4], 4);
    graph.insertEdge(vertices1[3], vertices1[4], 2);

    cout << "\n" << "------------------- PART 2 -------------------" << "\n";

    graph.shortestPathDijkstra(vertices1[0]);

    return 1;
}


