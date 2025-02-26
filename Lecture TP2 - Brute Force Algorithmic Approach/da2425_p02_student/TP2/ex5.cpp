// By: Gonçalo Leão


#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

struct CoinInfo {
    unsigned int value;
    unsigned int stock;
    unsigned int originalIndex;
    CoinInfo(unsigned int v, unsigned int s, unsigned int idx) : value(v), stock(s), originalIndex(idx) {}
};

void backtrack(unsigned int index, unsigned int remaining, vector<unsigned int>& currentCounts, unsigned int currentTotal, const vector<CoinInfo>& sortedCoins, vector<unsigned int>& bestCounts, unsigned int& bestTotal) {
    if (index == sortedCoins.size()) {
        if (remaining == 0 && currentTotal < bestTotal) {
            bestTotal = currentTotal;
            bestCounts = currentCounts;
        }
        return;
    }

    const CoinInfo& coin = sortedCoins[index];
    unsigned int maxPossible = min(coin.stock, remaining / coin.value);

    for (unsigned int count = maxPossible; ; --count) {
        unsigned int newRemaining = remaining - count * coin.value;
        unsigned int newTotal = currentTotal + count;

        if (newTotal >= bestTotal) {
            if (count == 0) break;
            continue;
        }

        vector<unsigned int> newCounts = currentCounts;
        newCounts[index] = count;

        backtrack(index + 1, newRemaining, newCounts, newTotal, sortedCoins, bestCounts, bestTotal);

        if (count == 0) {
            break;
        }
    }
}

bool changeMakingBF(unsigned int Coin_V[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    vector<CoinInfo> sortedCoins;
    for (unsigned int i = 0; i < n; ++i) {
        sortedCoins.emplace_back(Coin_V[i], Stock[i], i);
    }
    sort(sortedCoins.begin(), sortedCoins.end(), [](const CoinInfo& a, const CoinInfo& b) {
        return a.value > b.value;
    });

    vector<unsigned int> bestCounts(n);
    unsigned int bestTotal = UINT_MAX;

    vector<unsigned int> currentCounts(n);
    backtrack(0, T, currentCounts, 0, sortedCoins, bestCounts, bestTotal);

    if (bestTotal != UINT_MAX) {
        memset(usedCoins, 0, n * sizeof(unsigned int));
        for (unsigned int i = 0; i < sortedCoins.size(); ++i) {
            unsigned int originalIndex = sortedCoins[i].originalIndex;
            usedCoins[originalIndex] = bestCounts[i];
        }
        return true;
    }

    return false;

}

// Time: O(D*S), Space: O(D), where D is the number of coin values and S is the maximum amount of stock of any value
bool changeMakingGR(unsigned int Coin_V[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {

    for (int i = n-1; i >= 0; i--) {
        usedCoins[i] = 0;
        if (T==0) continue;
        unsigned int n_coins = T / Coin_V[i];
        n_coins = (n_coins > Stock[i]) ? Stock[i] : n_coins;

        T -= n_coins * Coin_V[i];

        Stock[i] -= n_coins;

        usedCoins[i] = n_coins;

    }
    if (T==0) return true;
    return false;
}










/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex5, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];
    //10x1, 5x0, 2x1, 1x1
    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex5, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex5, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}


TEST(TP2_Ex5, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP2_Ex5, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}