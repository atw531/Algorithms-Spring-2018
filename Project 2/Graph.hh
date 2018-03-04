
#pragma once

#include <string>
#include <vector>

struct listNode {
    std::string name;
    double dist;
    double cost;

    struct listNode* next;
};

class Graph {
public:
    Graph(int size)
    : nodeCount(size) {

    };

    void addRoot(std::string name);

    void addEdge(int parentIndex, int childIndex, double distance, double cost);

private:
    int nodeCount;
    std::vector<listNode> adjList;
};
