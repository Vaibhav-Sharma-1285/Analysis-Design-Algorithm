#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocateMatrix(int n)
{
  int **matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
    matrix[i] = (int *)calloc(n, sizeof(int));
  return matrix;
}

void freeMatrix(int **matrix, int n)
{
  for (int i = 0; i < n; i++)
    free(matrix[i]);
  free(matrix);
}

void addMatrix(int **A, int **B, int **C, int n)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrix(int **A, int **B, int **C, int n)
{
  if (n == 1)
  {
    C[0][0] = A[0][0] * B[0][0];
    return;
  }

  int k = n / 2;

  int **A11 = allocateMatrix(k), **A12 = allocateMatrix(k);
  int **A21 = allocateMatrix(k), **A22 = allocateMatrix(k);
  int **B11 = allocateMatrix(k), **B12 = allocateMatrix(k);
  int **B21 = allocateMatrix(k), **B22 = allocateMatrix(k);
  int **C11 = allocateMatrix(k), **C12 = allocateMatrix(k);
  int **C21 = allocateMatrix(k), **C22 = allocateMatrix(k);
  int **M = allocateMatrix(k);

  for (int i = 0; i < k; i++)
  {
    for (int j = 0; j < k; j++)
    {
      A11[i][j] = A[i][j];
      A12[i][j] = A[i][j + k];
      A21[i][j] = A[i + k][j];
      A22[i][j] = A[i + k][j + k];

      B11[i][j] = B[i][j];
      B12[i][j] = B[i][j + k];
      B21[i][j] = B[i + k][j];
      B22[i][j] = B[i + k][j + k];
    }
  }

  multiplyMatrix(A11, B11, C11, k);
  multiplyMatrix(A12, B21, M, k);
  addMatrix(C11, M, C11, k);

  multiplyMatrix(A11, B12, C12, k);
  multiplyMatrix(A12, B22, M, k);
  addMatrix(C12, M, C12, k);

  multiplyMatrix(A21, B11, C21, k);
  multiplyMatrix(A22, B21, M, k);
  addMatrix(C21, M, C21, k);

  multiplyMatrix(A21, B12, C22, k);
  multiplyMatrix(A22, B22, M, k);
  addMatrix(C22, M, C22, k);

  for (int i = 0; i < k; i++)
  {
    for (int j = 0; j < k; j++)
    {
      C[i][j] = C11[i][j];
      C[i][j + k] = C12[i][j];
      C[i + k][j] = C21[i][j];
      C[i + k][j + k] = C22[i][j];
    }
  }

  freeMatrix(A11, k);
  freeMatrix(A12, k);
  freeMatrix(A21, k);
  freeMatrix(A22, k);
  freeMatrix(B11, k);
  freeMatrix(B12, k);
  freeMatrix(B21, k);
  freeMatrix(B22, k);
  freeMatrix(C11, k);
  freeMatrix(C12, k);
  freeMatrix(C21, k);
  freeMatrix(C22, k);
  freeMatrix(M, k);
}

int main()
{
  int sizes[] = {16, 32, 64, 128, 256};
  int numSizes = sizeof(sizes) / sizeof(sizes[0]);

  srand(time(NULL));

  for (int s = 0; s < numSizes; s++)
  {
    int n = sizes[s];

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        A[i][j] = rand() % 10;
        B[i][j] = rand() % 10;
      }

    clock_t start = clock();
    multiplyMatrix(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Matrix size %d x %d -> Time: %f seconds\n", n, n, time_taken);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
  }

  return 0;
}

