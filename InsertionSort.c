#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int current = arr[i];
    int j = i - 1;

    // Move elements of arr[0..i-1], that are greater than key,
    // to one position ahead of their current position
    while (j >= 0 && arr[j] > current)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = current;
  }
}

int main()
{
  srand(time(NULL));

  printf("n,time\n");

  int sizes[] = {100, 200, 400, 600, 800, 1000, 1200, 1500, 2000, 2500, 3000, 4000, 5000,6000,7000};
  int numTests = 15;

  for (int i = 0; i < numTests; i++)
  {
    int n = sizes[i];
    double totalTime = 0;

    // Average of 10 runs for better accuracy
    for (int run = 0; run < 10; run++)
    {
      int *arr = (int *)malloc(n * sizeof(int));

      // Generate random array
      for (int j = 0; j < n; j++)
        arr[j] = rand() % 100000;

      clock_t start = clock();
      insertionSort(arr, n);
      clock_t end = clock();

      totalTime += ((double)(end - start)) / CLOCKS_PER_SEC;
      free(arr);
    }

    printf("%d,%.6f\n", n, totalTime / 10);
  }

  printf("Best Case: O(n)\n");
  printf("Average Case: O(n^2)\n");
  printf("Worst Case: O(n^2)\n");

  return 0;
}
