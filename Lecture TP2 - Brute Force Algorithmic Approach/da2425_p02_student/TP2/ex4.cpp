// By: Gonçalo Leão

#include <algorithm>
#include <vector>
// TODO fazer uma média entre peso e valor, ordenar por esse valor e inserir itens fracionados quando o peso for excedido pelo item completo
double fractionalKnapsackGR(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {
    double maxValue = 0;


    struct Item {
        double value;
        double weight;
        unsigned int index;

        double getValue() {
            return value/weight;
        }
    };

    Item items[n];
    for (unsigned int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].index = i;
    }

    std::sort(items, items + n, [](Item a, Item b) {return a.getValue() > b.getValue(); });
    double totalWeight = 0;

    for (unsigned int i = 0; i < n || totalWeight > maxWeight; i++) {
        if (totalWeight + items[i].weight <= maxWeight) {
            totalWeight += items[i].weight;
            maxValue += items[i].value;
            usedItems[items[i].index] = 1;
        }
        else {
            double weightLeft = maxWeight - totalWeight;
            double weightPercent = weightLeft / items[i].weight;
            double valueLeft = items[i].value * weightPercent;
            maxValue += valueLeft;
            totalWeight = maxWeight;
            usedItems[items[i].index] = weightPercent;
        }
    }

    return maxValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP2_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}