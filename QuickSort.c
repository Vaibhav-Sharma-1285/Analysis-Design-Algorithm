#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high)
{
  int pivot = arr[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] < pivot)
    {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;
  return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int main()
{
  srand(time(NULL));
  
  printf("n,time\n");

  int sizes[] = {1000, 2000, 5000, 10000, 20000, 30000, 50000, 75000, 100000, 150000, 200000, 250000};
  int numTests = 12;

  for (int i = 0; i < numTests; i++)
  {
    int n = sizes[i];
    double totalTime = 0;

    // Average of 10 runs for better accuracy
    for(int run = 0; run < 10; run++)
    {
      int *arr = (int *)malloc(n * sizeof(int));
      
      // Generate random array
      for (int j = 0; j < n; j++)
        arr[j] = rand() % 100000;

      clock_t start = clock();
      quickSort(arr, 0, n - 1);
      clock_t end = clock();

      totalTime += ((double)(end - start)) / CLOCKS_PER_SEC;
      free(arr);
    }
    
    printf("%d,%.6f\n", n, totalTime / 10);
  }

  printf("Best Case: O(n log n)\n");
  printf("Average Case: O(n log n)\n");
  printf("Worst Case: O(n^2)\n");

  return 0;
}
