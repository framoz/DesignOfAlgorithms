// By: Gonçalo Leão


// Bruteforce o algoritmo será (2^n) temporal, n espacial

#include <algorithm>

bool subsetSumBFHelper(unsigned int A[], unsigned int n, unsigned int T, unsigned int index,unsigned int subset[], unsigned int &subsetSize, unsigned int curSum) {
    if (curSum == T) {
        return true;
    }
    if (index == n || curSum > T) {
        return false;
    }

    subset[subsetSize] = A[index];
    subsetSize++;

    if (subsetSumBFHelper(A, n, T, index+1, subset, subsetSize, curSum + A[index])) {
        return true;
    }

    subsetSize--;

    if (subsetSumBFHelper(A, n, T, index+1, subset, subsetSize, curSum)) {
        return true;
    }

    return false;
}

bool subsetSumBF(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    std::sort(A, A+n); //dando sort antes para corrigir o backtrack
    subsetSize = 0;
    return subsetSumBFHelper(A,n,T,0, subset, subsetSize, 0 );
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), false);
}