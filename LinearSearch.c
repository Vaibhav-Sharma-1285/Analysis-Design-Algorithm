#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int linearSearch(int arr[], int n, int target){
  for(int i=0; i<n; i++){
    if(arr[i]==target)
    {
      return i;
    }
  }
  return -1;
}

int main(){
  int Arraysizes[]={1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000, 2000000};
  int TotalSizes=10;

  for(int i=0; i<TotalSizes; i++){
    int n=Arraysizes[i];
    int *arr=malloc(n*sizeof(int));

    for(int j=0; j<n; j++){
      arr[j]=j;
    }

    for(int k=0; k<1000; k++){
      linearSearch(arr, n, n/2);
    }

    clock_t total=0;
    int noOfIterations=50000;

    for(int l=0; l<noOfIterations; l++){
      int target=arr[n/2];  //average case

      clock_t start=clock();
      linearSearch(arr, n, target);
      clock_t end=clock();

      total+=(end-start);
    }

    double avgTime=((double)total/noOfIterations/CLOCKS_PER_SEC)*1000;
    printf("Size,Time\n");
    printf("%d,%.3f\n", n, avgTime);

    free(arr);
  }

  return 0;
}
