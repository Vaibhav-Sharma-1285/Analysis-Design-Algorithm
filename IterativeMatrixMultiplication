#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocateMatrix(int n)
{
  int **mat = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
  {
    mat[i] = (int *)malloc(n * sizeof(int));
  }
  return mat;
}

void freeMatrix(int **mat, int n)
{
  for (int i = 0; i < n; i++)
  {
    free(mat[i]);
  }
  free(mat);
}

void multiplyMatrices(int **A, int **B, int **C, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      C[i][j] = 0;
      for (int k = 0; k < n; k++)
      {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main()
{
  int sizes[] = {100, 200, 500, 800};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);

  for (int s = 0; s < numSizes; s++)
  {
    int n = sizes[s];
    printf("\nMatrix size: %d x %d\n", n, n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        A[i][j] = rand() % 10;
        B[i][j] = rand() % 10;
      }
    }

    clock_t start = clock();
    multiplyMatrices(A, B, C, n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", time_taken);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
  }
  
  return 0;
}
