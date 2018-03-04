#include <iostream>
#include "Graph.hh"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph g(3);
    g.addRoot("City1");
    g.addRoot("City2");
    g.addRoot("City3");

    g.addEdge(0, 1, 1, 10);
    g.addEdge(0, 2, 2, 20);
    g.addEdge(1, 2, 12, 12);
    g.addEdge(2, 1, 21, 21);

    return 0;
}