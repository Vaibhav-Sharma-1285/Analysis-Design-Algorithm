#include <stdio.h>
#include <time.h>

struct Item {
    int weight;
    int value;
    float ratio;
};

void sortItems(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (items[j].ratio < items[j + 1].ratio) {
                struct Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

float fractionalKnapsack(int capacity, struct Item items[], int n) {
    for (int i = 0; i < n; i++) {
        items[i].ratio = (float)items[i].value / items[i].weight;
    }

    sortItems(items, n);
    
    float totalValue = 0.0;
    int currentWeight = 0;
    
    printf("\nFractional Knapsack (Greedy Approach):\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            // Take whole item
            currentWeight += items[i].weight;
            totalValue += items[i].value;
            printf("Item %d: Take 100%% (Weight=%d, Value=%d)\n", 
                   i+1, items[i].weight, items[i].value);
        } else {
            int remaining = capacity - currentWeight;
            if (remaining > 0) {
                float fraction = (float)remaining / items[i].weight;
                totalValue += items[i].value * fraction;
                printf("Item %d: Take %.1f%% (Weight=%d, Value=%d)\n", 
                       i+1, fraction*100, items[i].weight, items[i].value);
            }
            break;
        }
    }
    
    return totalValue;
}

int main() {
    int capacity = 50;
    int n = 5;
    
    struct Item items[] = {
        {10, 60, 0},
        {20, 100, 0},
        {30, 120, 0},
        {15, 80, 0},
        {25, 90, 0}
    };
    
    printf("FRACTIONAL KNAPSACK PROBLEM\n");
    printf("============================\n");
    printf("Capacity: %d\n", capacity);
    
    clock_t start = clock();
    float result = fractionalKnapsack(capacity, items, n);
    clock_t end = clock();
    
    double timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("----------------------------------------\n");
    printf("Maximum Value: %.2f\n", result);
    printf("Time taken: %.6f ms\n", timeTaken);
    
    return 0;
}

// **Time Complexity:** O(n log n) - because of sorting  
// **Space Complexity:** O(n) - to store items
