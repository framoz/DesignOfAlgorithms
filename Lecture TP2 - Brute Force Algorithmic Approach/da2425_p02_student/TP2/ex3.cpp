// By: Gonçalo Leão

//

#include <vector>
#include <algorithm> // for sort
#include <bitset>
#include <cmath>

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int totalCombinations = std::pow(2, n);

    bool foundSol = false;
    unsigned int maxValue = 0;

    for (unsigned int i = 0; i < totalCombinations; i++) {
        std::bitset<20> binarySubset(i);

        int sum = 0;
        int weight = 0;
        for (unsigned int j = 0; j < n; j++) {
            sum += values[j] * binarySubset[j];
            weight += weights[j] * binarySubset[j];

        }
        if (weight <= maxWeight) {
            if (!foundSol || sum > maxValue) {
                foundSol = true;
                maxValue = sum;

                for (unsigned int j = 0; j < n; j++) {
                    usedItems[j] = binarySubset[j];
                }
            }
        }
    }

    return maxValue;
}

// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyValue(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    int maxValue = 0;


    struct Item {
        unsigned int value;
        unsigned int weight;
        unsigned int index;
    };

    Item items[n];
    for (unsigned int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].index = i;
    }

    std::sort(items, items + n, [](Item a, Item b) {return a.value > b.value; });
    int totalWeight = 0;

    int i = 0;
    do {
        if (items[i].weight > maxWeight) { continue;}
        if (totalWeight + items[i].weight > maxWeight) {continue;}

        totalWeight += items[i].weight;
        maxValue += items[i].value;
        usedItems[items[i].index] = true;
        i++;
    }while (totalWeight < maxWeight && i < n);

    return maxValue;
}


// does not guarantee the optimal solution in the current form
unsigned int knapsackGreedyWeight(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    int maxValue = 0;


    struct Item {
        unsigned int value;
        unsigned int weight;
        unsigned int index;
    };

    Item items[n];
    for (unsigned int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
        items[i].index = i;
    }

    std::sort(items, items + n, [](Item a, Item b) {return a.weight < b.weight; });
    int totalWeight = 0;

    int i = 0;
    do {
        if (items[i].weight > maxWeight) {continue;}
        if (totalWeight + items[i].weight > maxWeight) {break;}
        totalWeight += items[i].weight;
        maxValue += items[i].value;
        usedItems[items[i].index] = true;
        i++;
    }while (totalWeight < maxWeight && i < n);

    return maxValue;
}




/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);



    }



    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

// this test is expected to fail
TEST(TP2_Ex3, testKnapsack_4items_greedy_fail) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 5};
        bool usedItems[n];

        //correct value is 28
        //expected for greedy is 15, because it only puts the first element there
        EXPECT_EQ(knapsackGreedyValue(values, weights, n, 5, usedItems), 15);
        weights[0]=1;
        weights[1]=1;
        weights[3]=3;
        //correct value is 36
        //expected value is 28, because you end up filling it with light objects that aren't valuable
        EXPECT_EQ(knapsackGreedyWeight(values, weights, n, 5, usedItems), 28);

    }
}



TEST(TP2_Ex3, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}


TEST(TP2_Ex3, testKnapsack_40items) {
    const unsigned int n = 20;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4, 1,  2, 3, 8, 4,12, 20,
                                  1, 4, 4 ,3, 3, 6, 6, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 4,3, 2, 1, 4, 6,10, 10, 3, 1, 6,2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 24);



    }
}