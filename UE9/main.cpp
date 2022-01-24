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
            MyVertex("9"),
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
    cout << "\n" << "Number of Vertices: " << graph.getNumberOfVertices() << "\n\n";


    graph.insertEdge(vertices1[0], vertices1[1], 1);
    graph.insertEdge(vertices1[0], vertices1[3], 2);
    graph.insertEdge(vertices1[1], vertices1[2], 3);
    graph.insertEdge(vertices1[1], vertices1[3], 4);
    graph.insertEdge(vertices1[2], vertices1[4], 5);
    graph.insertEdge(vertices1[3], vertices1[4], 6);

    cout << "Vertices in Graph after insertEdge: ";
    for (const auto &v: graph.getVertices()) {
        cout << v << " ";
    }
    cout << "\n" << "Number of Vertices after insertEdge: " << graph.getNumberOfVertices() << "\n";


    cout << "\n" << "=========== Matrix ===========" << "\n";

    const auto matrix = graph.getAdjacencyMatrix();
    cout << "    ";
    for (int i = 0; i < vertices1Len - 1; ++i) {
        cout << vertices1[i].name << "--";
    }
    cout << vertices1[vertices1Len - 1].name << "\n";

    int i = 0;
    for (const auto &m: matrix) {
        cout << vertices1[i++].name << ": ";

        for (const auto &n: m) {
            cout << (n < 0 ? "" : " ") << n << " ";
        }

        cout << "\n";
    }

    const MyVertex vertices2[] = {
            MyVertex("5"),
            MyVertex("6"),
            MyVertex("7"),
    };

    for (const auto &vertex: vertices2) {
        graph.insertVertex(vertex);
    }

    graph.insertEdge(vertices2[0], vertices2[1], 1);
    graph.insertEdge(vertices2[0], vertices2[2], 2);

    cout << "\n" << "=========== List ===========" << "\n";

    for (const auto &searchVertex: vertices1) {
        cout << searchVertex << ": ";
        for (const auto &v: graph.getAdjacentVertices(searchVertex)) {
            cout << v.name << " ";
        }
        cout << "\n";
    }


    cout << "\n" << "------------------- PART 2 -------------------" << "\n";

    cout << "isCyclic: " << boolalpha << graph.isCyclic() << "\n";
    cout << "isConnected: " << boolalpha << graph.isConnected() << "\n";
    cout << "Connected Components: " << graph.getNumberOfComponents() << "\n";

    graph.printComponents();

    cout << "\n" << "------------------- EXTERNAL VALUES -------------------" << "\n";
    externalTest();

    return 1;
}


void externalTest() {
    Graph graph;
    graph.insertEdge(MyVertex("5"), MyVertex("7"), 1);
    graph.insertEdge(MyVertex("1"), MyVertex("0"), 2);
    graph.insertEdge(MyVertex("3"), MyVertex("0"), 3);
    graph.insertEdge(MyVertex("3"), MyVertex("4"), 4);
    graph.insertEdge(MyVertex("2"), MyVertex("4"), 5);
    graph.insertEdge(MyVertex("1"), MyVertex("4"), 6);
    graph.insertEdge(MyVertex("1"), MyVertex("2"), 6);
    graph.insertEdge(MyVertex("1"), MyVertex("3"), 6);

    cout << "isCyclic: " << boolalpha << graph.isCyclic() << "\n"; // matches

    Graph graph2;
    graph2.insertEdge(MyVertex("5"), MyVertex("8"), 1);
    graph2.insertEdge(MyVertex("1"), MyVertex("0"), 2);
    graph2.insertEdge(MyVertex("3"), MyVertex("1"), 3);
    graph2.insertEdge(MyVertex("3"), MyVertex("0"), 4);
    graph2.insertEdge(MyVertex("3"), MyVertex("4"), 5);
    graph2.insertEdge(MyVertex("2"), MyVertex("4"), 6);
    graph2.insertEdge(MyVertex("1"), MyVertex("4"), 6);
    graph2.insertEdge(MyVertex("1"), MyVertex("2"), 6);
    graph2.insertEdge(MyVertex("1"), MyVertex("3"), 6);

    cout << "isCyclic: " << boolalpha << graph2.isCyclic() << "\n"; // matches

    Graph g;
    g.insertEdge(MyVertex("0"), MyVertex("1"), 1);
    g.insertEdge(MyVertex("0"), MyVertex("2"), 1);
    g.insertEdge(MyVertex("1"), MyVertex("2"), 1);
    g.insertEdge(MyVertex("2"), MyVertex("0"), 1);
    g.insertEdge(MyVertex("2"), MyVertex("3"), 1);
    g.insertEdge(MyVertex("3"), MyVertex("3"), 1);

    cout << "isCyclic: " << boolalpha << g.isCyclic() << "\n"; // matches
}