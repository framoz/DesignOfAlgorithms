#include <iostream>
#include <unordered_set>

#include "../data_structures/Graph.h"

using namespace std;

/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
template <class T>
vector<T> dfs(Graph<T> *g, const T & source) {
    vector<int> res;
    Vertex<T> *v = g->findVertex(source);
    if (v != nullptr) dfsVisit(v, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void dfsVisit(Vertex<T> *v, vector<T> & res) {
    vector<Edge<T> *> e = v->getAdj();
    res.push_back(v->getInfo());
    for (auto edge : e) {
        if (std::find(res.begin(), res.end(), edge->getDest()->getInfo()) == res.end())
            dfsVisit(edge->getDest(), res);
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph, starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <typename T>
vector<T> bfs(Graph<T> *g, const T & source) {
    vector<T> res;
    unordered_set<T> visited;

    Vertex<T> *v = g->findVertex(source);
    if (!v) return res;

    queue<Vertex<T> *> q;
    q.push(v);
    visited.insert(v->getInfo());

    while (!q.empty()) {
        Vertex<T> *u = q.front();
        q.pop();
        res.push_back(u->getInfo());
        for (auto edge : u->getAdj()) {
            Vertex<T> *neighbor = edge->getDest();
            if (visited.find(neighbor->getInfo()) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor->getInfo());
            }
        }
    }
    return res;
}