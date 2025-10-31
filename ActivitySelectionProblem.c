#include <stdio.h>

struct Activity {
    int start;
    int finish;
    int index;
};

void sortActivities(struct Activity act[], int n) {
    int i, j;
    struct Activity temp;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (act[j].finish > act[j + 1].finish) {
                // Swap activities
                temp = act[j];
                act[j] = act[j + 1];
                act[j + 1] = temp;
            }
        }
    }
}

void activitySelection(struct Activity act[], int n) {
    int i, count = 0;
    
    printf("\n--- Activity Selection using Greedy Method ---\n\n");
    
    sortActivities(act, n);
    
    printf("Activities sorted by finish time:\n");
    printf("Activity\tStart\tFinish\n");
    for (i = 0; i < n; i++) {
        printf("A%d\t\t%d\t%d\n", act[i].index, act[i].start, act[i].finish);
    }
    
    printf("\n--- Selected Activities ---\n");
    
    i = 0;
    printf("Activity A%d (Start: %d, Finish: %d)\n", 
           act[i].index, act[i].start, act[i].finish);
    count++;
    
    for (int j = 1; j < n; j++) {
        if (act[j].start >= act[i].finish) {
            printf("Activity A%d (Start: %d, Finish: %d)\n", 
                   act[j].index, act[j].start, act[j].finish);
            i = j;
            count++;
        }
    }
    
    printf("\nTotal activities selected: %d\n", count);
}

int main() {
    int n, i;
    
    printf("Enter number of activities: ");
    scanf("%d", &n);
    
    struct Activity act[n];
    
    printf("\nEnter start and finish time for each activity:\n");
    for (i = 0; i < n; i++) {
        printf("Activity %d - Start time: ", i + 1);
        scanf("%d", &act[i].start);
        printf("Activity %d - Finish time: ", i + 1);
        scanf("%d", &act[i].finish);
        act[i].index = i + 1;
    }
    
    activitySelection(act, n);
    
    return 0;
} 
