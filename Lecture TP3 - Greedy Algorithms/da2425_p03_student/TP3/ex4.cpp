// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"
#include <climits>
using namespace std;

template <class T>
bool relax(Edge<T> *edge) { // d[u] + w(u,v) < d[v]
    Vertex<T> *src = edge->getOrig();
    Vertex<T> *dest = edge->getDest();
    double new_dist = src->getDist() + edge->getWeight();

    if (new_dist < dest->getDist()) {
        dest->setDist(src->getDist() + edge->getWeight());
        return true;
    }

    return false;
}

template <class T>
void dijkstra(Graph<T> * g, const int &origin) {




    Vertex<T>* vertex = g->findVertex(origin);

    MutablePriorityQueue<Vertex<T>> pq;

    for (auto v : g->getVertexSet()) {
        v->setDist(INT_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
        pq.insert(v);
    }

    vertex->setDist(0);
    vertex->setVisited(true);
    pq.decreaseKey(vertex);


    while (!pq.empty()) {
        Vertex<T> *u = pq.extractMin();
        u->setVisited(true);

        for (auto edge: u->getAdj()) {
            if (edge->getDest()->isVisited() == false && relax(edge)) {


                edge->getDest()->setPath(edge);
                pq.decreaseKey(edge->getDest());
            }
        }
       // std::cout << u->getInfo() << " -> ";
    }
}

template <class T>
static std::vector<T> getPath(Graph<T> * g, const int &origin, const int &dest) {
    std::vector<T> res;

    Vertex<T> *cur = g->findVertex(dest);

    do {
        res.insert(res.begin(), cur->getInfo());
        cur = cur->getPath()->getOrig();
    }
    while (cur->getInfo() != origin);
    res.insert(res.begin(), cur->getInfo());
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

template <class T>
 static void checkAllPaths(Graph<T> &g, std::string expected) {
    std::stringstream ss;
    std::vector<Vertex<T> *> vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != nullptr ) {
            ss << vs[i]->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}


static void checkSinglePath(std::vector<int> path, std::string expected) {
    std::stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++) {
        ss << path[i] << " ";
    }
    EXPECT_EQ(expected, ss.str());
}

TEST(TP3_Ex4, test_dijkstra) {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    dijkstra(&myGraph, 3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    dijkstra(&myGraph, 1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(getPath(&myGraph, 1, 7), "1 2 4 5 7 ");

    dijkstra(&myGraph,5);
    checkSinglePath(getPath(&myGraph, 5, 6), "5 7 6 ");

    dijkstra(&myGraph, 7);
    checkSinglePath(getPath(&myGraph, 7, 1), "7 6 4 3 1 ");

}