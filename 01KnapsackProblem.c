#include <stdio.h>
#include <time.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int zeroOneKnapsack(int capacity, int weights[], int values[], int n) {
    int dp[n + 1][capacity + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                int includeItem = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                int excludeItem = dp[i - 1][w];
                dp[i][w] = max(includeItem, excludeItem);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\n0/1 Knapsack (Dynamic Programming):\n");
    printf("----------------------------------------\n");
    printf("Selected items:\n");
    
    int w = capacity;
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("Item %d (Weight=%d, Value=%d)\n", 
                   i, weights[i - 1], values[i - 1]);
            w = w - weights[i - 1];
        }
    }
    
    return dp[n][capacity];
}

int main() {
    int capacity = 50;
    int n = 5;
    
    int weights[] = {10, 20, 30, 15, 25};
    int values[] = {60, 100, 120, 80, 90};
    
    printf("0/1 KNAPSACK PROBLEM\n");
    printf("============================\n");
    printf("Capacity: %d\n", capacity);
    
    clock_t start = clock();
    int result = zeroOneKnapsack(capacity, weights, values, n);
    clock_t end = clock();
    
    double timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("----------------------------------------\n");
    printf("Maximum Value: %d\n", result);
    printf("Time taken: %.6f ms\n", timeTaken);
    
    return 0;
}

// **Time Complexity:** O(n × W) - where W is capacity  
// **Space Complexity:** O(n × W) - for DP table
