#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    int minIndex = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex])
        minIndex = j;
    }
    if (minIndex != i)
    {
      int temp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = temp;
    }
  }
}

int main()
{
  srand(time(NULL));

  printf("n,time\n");

  int sizes[] = {100, 200, 400, 600, 800, 1000, 1200, 1500, 2000, 2500, 3000, 4000, 5000, 6000, 7000};
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
      selectionSort(arr, n);
      clock_t end = clock();

      totalTime += ((double)(end - start)) / CLOCKS_PER_SEC;
      free(arr);
    }

    printf("%d,%.6f\n", n, totalTime / 10);
  }

  printf("Best Case: O(n^2)\n");
  printf("Average Case: O(n^2)\n");
  printf("Worst Case: O(n^2)\n");

  return 0;
}
