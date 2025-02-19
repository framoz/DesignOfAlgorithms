// By: Gonçalo Leão


#include <algorithm>
#include <iostream>

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {

    for (int i = n-1; i >= 0; i--) {
        usedCoins[i] = 0;
        if (T==0) continue;
        unsigned int n_coins = T / C[i];
        // std::cout
        //     << "it:" <<i << "\n"
        //     << "Start T: " << T << "\n"
        //     << "Stock: " << Stock[i] << "\n"
        //     << "n_coins: " << n_coins << "\n";


        //if (n_coins == 0) continue;
        n_coins = (n_coins > Stock[i]) ? Stock[i] : n_coins;
        //std::cout <<"n_coins after: "<< n_coins << "\n";
        T -= n_coins * C[i];
        //std::cout << "Final T: " << T << "\n";
        Stock[i] -= n_coins;
        //std::cout << "Final Stock: " << Stock[i] << "\n";
        usedCoins[i] = n_coins;
        //std::cout << "Used Coins[" <<i <<"]: " << usedCoins[i] << "\n\n\n";

    }
    if (T==0) return true;
    return false;
}



// Time: O(D*S), Space: O(D), where D is the number of coin values and S is the maximum amount of stock of any value
bool changeMakingGR(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {

    for (int i = n-1; i >= 0; i--) {
        usedCoins[i] = 0;
        if (T==0) continue;
        unsigned int n_coins = T / C[i];
        // std::cout
        //     << "it:" <<i << "\n"
        //     << "Start T: " << T << "\n"
        //     << "Stock: " << Stock[i] << "\n"
        //     << "n_coins: " << n_coins << "\n";


        //if (n_coins == 0) continue;
        n_coins = (n_coins > Stock[i]) ? Stock[i] : n_coins;
        //std::cout <<"n_coins after: "<< n_coins << "\n";
        T -= n_coins * C[i];
        //std::cout << "Final T: " << T << "\n";
        Stock[i] -= n_coins;
        //std::cout << "Final Stock: " << Stock[i] << "\n";
        usedCoins[i] = n_coins;
        //std::cout << "Used Coins[" <<i <<"]: " << usedCoins[i] << "\n\n\n";

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