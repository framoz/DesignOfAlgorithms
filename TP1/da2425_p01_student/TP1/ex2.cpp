#include <iostream>
#include "../data_structures/Graph.h"

using namespace std;
#include <queue>

/*
 * Ex2 a. 1, 2, 5, 4, 3, 7, 6
 *        1, 2, 5, 4, 7, 3, 6
 */

/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
*/
template <typename T>
vector<T> topsort(Graph<T> *g) {
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
        return {};
    }
    return res;
}



