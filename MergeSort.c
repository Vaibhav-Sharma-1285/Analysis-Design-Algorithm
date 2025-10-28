#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right)
{
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  int *L = (int *)malloc(n1 * sizeof(int));
  int *R = (int *)malloc(n2 * sizeof(int));

  if (L == NULL || R == NULL)
  {
    printf("Memory allocation failed in merge\n");
    exit(1);
  }

  for (i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  i = 0;
  j = 0;
  k = left;

  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }

  while (i < n1)
    arr[k++] = L[i++];

  while (j < n2)
    arr[k++] = R[j++];

  free(L);
  free(R);
}

void mergeSort(int arr[], int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main()
{
  srand(time(NULL));

  printf("n,time\n");

  int sizes[] = {5000, 10000, 20000, 40000, 60000, 80000, 100000, 120000, 150000, 200000};
  int numTests = 10;

  for (int i = 0; i < numTests; i++)
  {
    int n = sizes[i];
    double totalTime = 0;

    // Average of 5 runs
    for (int run = 0; run < 5; run++)
    {
      int *arr = (int *)malloc(n * sizeof(int));

      // Generate random array
      for (int j = 0; j < n; j++)
        arr[j] = rand() % 100000;

      clock_t start = clock();
      mergeSort(arr, 0, n - 1);
      clock_t end = clock();

      totalTime += ((double)(end - start)) / CLOCKS_PER_SEC;
      free(arr);
    }

    printf("%d,%.6f\n", n, totalTime / 5);
  }

  printf("Best Case: O(n log n)\n");
  printf("Average Case: O(n log n)\n");
  printf("Worst Case: O(n log n)\n");

  return 0;
}
