#include "../data_structures/Graph.h"
#include <vector>
#include <algorithm>


template<typename T>
void tarjanHelper(Vertex<T>* v, std::vector<Vertex<T>*>& stack, std::vector<std::vector<T>>& result, int& index) {
    v->setNum(index);
    v->setLow(index);
    index++;

    stack.push_back(v);
    v->setProcessing(true);

    for (Edge<T>* e :v->getAdj()) {
        Vertex<T>* w  = e->getDest();
        if (w->getNum() == -1) {
            tarjanHelper(w,stack,result,index);
            v->setLow(std::min(v->getLow(), w->getLow()));
        }
        else if (w->isProcessing()) {
            v->setLow(std::min(v->getLow(), w->getLow()));
        }
    }

    if (v->getNum() == v->getLow()) {
        std::vector<T> component;
        Vertex<T>* w;
        do {
            w = stack.back();
            stack.pop_back();
            w->setProcessing(false);
            component.push_back(w->getInfo());
        }while (w != v);
        result.push_back(component);
    }
}

template <typename T>
std::vector<std::vector<T>> sccTarjan(Graph<T>* g) {
    std::vector<std::vector<T>> result;
    std::vector<Vertex<T>*> stack;
    int index = 0;

    std::vector<Vertex<T>*> vertexSet = g->getVertexSet();

    for (Vertex<T>* v : vertexSet) {
        if (v->getNum() == -1) {
            tarjanHelper(v, stack, result, index);
        }
    }

    for (Vertex<T>* v : vertexSet) {
        v->setNum(-1);
        v->setLow(-1);
        v->setProcessing(false);
    }

    return result;
}