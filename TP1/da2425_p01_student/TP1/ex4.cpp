#include "../data_structures/Graph.h"
#include "stack"


template<typename T>
void kosarajuDFS(Vertex<T>* v, std::vector<Vertex<T>*>& stack) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            kosarajuDFS(w, stack);
        }
    }
    stack.push_back(v);
}

template<typename T>
void kosarajuDFSSecondPass(Vertex<T>* v, std::vector<T>& component) {
    v->setVisited(true);
    component.push_back(v->getInfo());
    for (auto e : v->getIncoming()) {
        auto w = e->getOrig();
        if (!w->isVisited()) {
            kosarajuDFSSecondPass(w, component);
        }
    }
}

// Kosaraju-Sharir algorithm
template <typename T>
std::vector<std::vector<T>> SCCkosaraju(Graph<T>* g)  {
    std::vector<std::vector<T>> sccs;

    auto vertexSet = g->getVertexSet();

    //Set visited to false in all nodes
    for (auto v : vertexSet) {
        v->setVisited(false);
    }

    std::vector<Vertex<T>* > stack;
    //Do a normal DFS just to mark the node order
    for (auto v : vertexSet) {
        if (!v->isVisited())
        kosarajuDFS(v,stack);
    }

    //Prepare for second DFS pass
    for (Vertex<T>* v : g->getVertexSet()) {
        v->setVisited(false);
    }

    while (!stack.empty()) {
        Vertex<T>* v = stack.back();
        stack.pop_back();

        if (!v->isVisited()) {
            std::vector<T> component;
            kosarajuDFSSecondPass(v,component);
            sccs.push_back(component);
        }
    }

    return sccs;
}



