#include "../data_structures/Graph.h"
#include "stack"
using namespace std;

#include <queue>



template <typename T>
void tarjanHelper(Vertex<T>* v, std::vector<std::vector<T>>& result, std::vector<Vertex<T>*>& stk, int& index) {
    v->setNum(index);
    v->setLow(index);
    index++;
    stk.push_back(v);
    v->setProcessing(true);

    for (Edge<T>* edge : v->getAdj()) {
        Vertex<T>* w = edge->getDest();
        if (w->getNum() == -1) {
            tarjanHelper(w, result, stk, index);
            v->setLow(std::min(v->getLow(), w->getLow()));
        } else if (w->isProcessing()) {
            v->setLow(std::min(v->getLow(), w->getNum()));
        }
    }

    if (v->getLow() == v->getNum()) {
        std::vector<T> component;
        Vertex<T>* w;
        do {
            w = stk.back();
            stk.pop_back();
            w->setProcessing(false);
            component.push_back(w->getInfo());
        } while (w != v);
        result.push_back(component);
    }
}

template <typename T>
std::vector<std::vector<T>> sccTarjan(Graph<T>* g) {
    std::vector<std::vector<T>> result;
    std::vector<Vertex<T>*> stk;
    int index = 0;

    auto vertexSet = g->getVertexSet();
    for (Vertex<T>* v : vertexSet) {
        if (v->getNum() == -1) {
            tarjanHelper(v, result, stk, index);
        }
    }

    // Reset the vertex attributes to default values
    for (Vertex<T>* v : vertexSet) {
        v->setNum(-1);
        v->setLow(-1);
        v->setProcessing(false);
    }

    return result;
}