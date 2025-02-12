#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph, to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls.
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool isDAG(Graph<T> *g) {
    vector<int> res;
    vector<Vertex<T> *> vSet = g->getVertexSet();

    for (auto v : vSet)
        v->setIndegree(0);

    for (auto v : vSet) {
        for (auto edge: v->getAdj()) {
            unsigned int indegree = edge->getDest()->getIndegree();
            edge->getDest()->setIndegree(indegree+1);
        }
    }

    queue<Vertex<T> *> q;
    for (auto vertex: vSet) {
        if (vertex->getIndegree() == 0) {
            q.push(vertex);
        }
    }


    while (!q.empty()) {
        Vertex<T> *u = q.front();
        q.pop();
        res.push_back(u->getInfo());
        for (auto edge : u->getAdj()) {
            Vertex<T> *neighbor = edge->getDest();

            neighbor->setIndegree(neighbor->getIndegree() - 1);

            if (neighbor->getIndegree() == 0) {
                q.push(neighbor);
            }
        }
    }

    if (res.size() != vSet.size()) {
        return false;
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool dfsIsDAG(Vertex<T> *v) {
    // TODO
    return true;
}

