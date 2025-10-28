#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int function_calls = 0;

int fibonacci_recursive(int n)
{
  function_calls++;

  if (n <= 1)
  {
    return n;
  }

  return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n)
{
  if (n <= 1)
  {
    return n;
  }

  int first = 0;
  int second = 1;
  int result;

  for (int i = 2; i <= n; i++)
  {
    result = first + second;
    first = second;
    second = result;
  }

  return result;
}

int fibonacci_memo_helper(int n, int memo[])
{
  function_calls++;

  if (n <= 1)
  {
    return n;
  }

  if (memo[n] != -1)
  {
    return memo[n];
  }

  memo[n] = fibonacci_memo_helper(n - 1, memo) + fibonacci_memo_helper(n - 2, memo);

  return memo[n];
}

int fibonacci_top_down(int n)
{

  int *memo = (int *)malloc((n + 1) * sizeof(int));

  for (int i = 0; i <= n; i++)
  {
    memo[i] = -1;
  }

  int result = fibonacci_memo_helper(n, memo);
  free(memo);

  return result;
}

int fibonacci_bottom_up(int n)
{
  if (n <= 1)
  {
    return n;
  }

  int *table = (int *)malloc((n + 1) * sizeof(int));

  table[0] = 0;
  table[1] = 1;

  for (int i = 2; i <= n; i++)
  {
    table[i] = table[i - 1] + table[i - 2];
  }

  int result = table[n];
  free(table);

  return result;
}

void test_approach(const char *name, int (*func)(int), int n)
{
  function_calls = 0;

  int repetitions = 1000000;
  clock_t start = clock();
  int result;
  for (int i = 0; i < repetitions; i++)
  {
    result = func(n);
  }
  clock_t end = clock();

  double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / repetitions;

  printf("%s:\n", name);
  printf("  F(%d) = %d\n", n, result);
  printf("  Avg Time: %.9f seconds\n", time_taken);

  if (function_calls > 0)
  {
    printf("  Function calls: %d\n", function_calls);
  }
  printf("\n");
}

int main()
{
  printf("FIBONACCI NUMBER GENERATION\n\n");

  int n;
  printf("Enter the value of n: ");
  scanf("%d", &n);

  printf("\nResults for F(%d)\n\n", n);

  if (n <= 35)
  {
    test_approach("1. Recursive Approach", fibonacci_recursive, n);
  }
  else
  {
    printf("1. Recursive Approach: Skipped (too slow)\n\n");
  }

  test_approach("2. Iterative Approach", fibonacci_iterative, n);
  test_approach("3. Top-Down DP (Memoization)", fibonacci_top_down, n);
  test_approach("4. Bottom-Up DP (Tabulation)", fibonacci_bottom_up, n);

  printf("COMPLEXITY ANALYSIS\n");
  printf("Approach               | Time      | Space\n");
  printf("----------------------|-----------|--------\n");
  printf("Recursive             | O(2^n)    | O(n)\n");
  printf("Iterative             | O(n)      | O(1)\n");
  printf("Top-Down DP           | O(n)      | O(n)\n");
  printf("Bottom-Up DP          | O(n)      | O(n)\n");
  printf("\n");

  if (n <= 20)
  {
    printf("RECURSIVE CALLS GROWTH\n");
    for (int i = 1; i <= n && i <= 15; i++)
    {
      function_calls = 0;
      fibonacci_recursive(i);
      printf("F(%2d): %5d function calls\n", i, function_calls);
    }
  }

  return 0;
}
