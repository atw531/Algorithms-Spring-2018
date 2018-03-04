
#include <cstring>
#include "Graph.hh"

void Graph::addRoot(std::string name) {
    struct listNode root;
    root.name = name;
    root.cost = 0.0;
    root.dist = 0.0;
    root.next = nullptr;
    adjList.push_back(root);
}

void Graph::addEdge(int parentIndex, int childIndex, double distance, double cost) {
    struct listNode* parent = &adjList[parentIndex];
    struct listNode* child = &adjList[childIndex];

    struct listNode* tempNode = parent;
    while (tempNode->next != nullptr) {
        tempNode = tempNode->next;
    }

    struct listNode* newNode = new listNode;
    newNode->name = child->name;
    newNode->dist = distance;
    newNode->cost = cost;
    newNode->next = nullptr;
    tempNode->next = newNode;
}