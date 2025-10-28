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

void subMatrix(int **A, int **B, int **C, int n)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] - B[i][j];
}

void strassenMultiply(int **A, int **B, int **C, int n)
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

  int **M1 = allocateMatrix(k), **M2 = allocateMatrix(k);
  int **M3 = allocateMatrix(k), **M4 = allocateMatrix(k);
  int **M5 = allocateMatrix(k), **M6 = allocateMatrix(k);
  int **M7 = allocateMatrix(k);

  int **T1 = allocateMatrix(k), **T2 = allocateMatrix(k);

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

  addMatrix(A11, A22, T1, k);
  addMatrix(B11, B22, T2, k);
  strassenMultiply(T1, T2, M1, k);

  addMatrix(A21, A22, T1, k);
  strassenMultiply(T1, B11, M2, k);

  subMatrix(B12, B22, T2, k);
  strassenMultiply(A11, T2, M3, k);

  subMatrix(B21, B11, T2, k);
  strassenMultiply(A22, T2, M4, k);

  addMatrix(A11, A12, T1, k);
  strassenMultiply(T1, B22, M5, k);

  subMatrix(A21, A11, T1, k);
  addMatrix(B11, B12, T2, k);
  strassenMultiply(T1, T2, M6, k);

  subMatrix(A12, A22, T1, k);
  addMatrix(B21, B22, T2, k);
  strassenMultiply(T1, T2, M7, k);

  int **C11 = allocateMatrix(k), **C12 = allocateMatrix(k);
  int **C21 = allocateMatrix(k), **C22 = allocateMatrix(k);

  addMatrix(M1, M4, T1, k);
  subMatrix(T1, M5, T2, k);
  addMatrix(T2, M7, C11, k);

  addMatrix(M3, M5, C12, k);

  addMatrix(M2, M4, C21, k);

  subMatrix(M1, M2, T1, k);
  addMatrix(T1, M3, T2, k);
  addMatrix(T2, M6, C22, k);

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

  freeMatrix(M1, k);
  freeMatrix(M2, k);
  freeMatrix(M3, k);
  freeMatrix(M4, k);
  freeMatrix(M5, k);
  freeMatrix(M6, k);
  freeMatrix(M7, k);

  freeMatrix(C11, k);
  freeMatrix(C12, k);
  freeMatrix(C21, k);
  freeMatrix(C22, k);

  freeMatrix(T1, k);
  freeMatrix(T2, k);
}

int main()
{
  int sizes[] = {16, 32, 64, 128, 256, 512};
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
    strassenMultiply(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Strassen: Matrix size %d x %d -> Time: %f seconds\n", n, n, time_taken);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
  }

  return 0;
}
