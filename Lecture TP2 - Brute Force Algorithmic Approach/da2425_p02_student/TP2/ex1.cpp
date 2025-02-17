// By: Gonçalo Leão
// With contributions by Eduardo Almeida

#include <climits>
// Time: O(n^2), Space: O(n)
int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max = INT_MIN;
    for (int x = 0; x < n; x++) {
       int temp_sum = 0;
        for (int y = x; y < n; y++){
            temp_sum += A[y];
            if (temp_sum > max) {
                max = temp_sum;
                i = x;
                j = y;
            }
        }
    }
    return max;
}

// Alternative, slower solution
// Time: O(n^3), Space: O(n)
int maxSubsequenceBF_a(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max = INT_MIN;
    for (int x = 0; x < n; x++) {
        for (int y = x; y < n; y++) {
            int sum = 0;
            for (int z = x; z <= y; z++) {
                sum += A[z];
                if (sum > max) {
                    max = sum;
                    i = x;
                    j = y;
                }
            }
        }
    }
    return max;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex1, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}

TEST(TP2_Ex1_n3, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF_a(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}