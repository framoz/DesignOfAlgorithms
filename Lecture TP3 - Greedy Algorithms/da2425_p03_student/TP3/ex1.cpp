#include <limits.h>

#include "MSTTestAux.h"
#include "../data_structures/Graph.h"

template <typename T>
std::vector<Vertex<T> *> prim(Graph<T> *g) {
    auto vertexSet = g->getVertexSet();

    if (vertexSet.empty()) {
        return vertexSet;
    }

    for (auto v : vertexSet) {
        v->setDist(INF);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    vertexSet[0]->setDist(0);
    MutablePriorityQueue<Vertex<T>> q;

    for (auto v : vertexSet) {
        q.insert(v);
    }

    while (!q.empty()) {
        auto u = q.extractMin();
        u->setVisited(true);

        for (auto e: u->getAdj()) {
            auto v = e->getDest();
            if (!v->isVisited() && e->getWeight() < v->getDist()) {
                    v->setDist(e->getWeight());
                    v->setPath(e);
                    q.decreaseKey(v);
            }
        }
    }

    return vertexSet;
}


/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

TEST(TP3_Ex1, test_prim) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = prim(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}

TEST(TP3_Ex1_performance, test_performance_prim) {
    //Change these const parameters as needed
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 30; //Try with 100
    const int STEP_SIZE = 10;
    const int N_REPETITIONS = 50;
    for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Graph<int> g;
        generateRandomGridGraph(n, g);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= N_REPETITIONS; i++)
            prim(&g);
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << "Processing grid (Prim) " << n << " x " << n << " average time (milliseconds)=" << (elapsed / N_REPETITIONS) << std::endl;
    }
}
