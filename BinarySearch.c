#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int binarySearch(int arr[], int n, int target){
  int left=0, right=n-1;
  while(left<=right)
  {
    int mid=left+(right - left)/2;
    if(arr[mid]==target){
      return mid;
    }
    if(arr[mid]<target){
      left=mid+1;
    }
    else{
      right=mid-1;
    }
  }
  return -1;
}

int main(){
  int sizes[]={1000, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000, 2000000};
  int TotalSizes=10;

  for(int i=0; i<TotalSizes; i++){
    int n = sizes[i];
    int *arr = malloc(n * sizeof(int));

    for (int j=0; j<n; j++){
      arr[j]=j;
    }

    int target=n; 

    for (int k=0; k<1000; k++){
      binarySearch(arr, n, target);
    }

    clock_t total=0;
    int noOfiterations=1000000;

    for (int k=0; k<noOfiterations; k++){
      clock_t start=clock();
      binarySearch(arr, n, target);
      clock_t end=clock();

      total+=(end-start);
    }

    double avgTime=((double)total/noOfiterations/CLOCKS_PER_SEC)*1000000;
    printf("Size,Time\n");
    printf("%d,%.2f\n", n, avgTime);

    free(arr);
  }

  return 0;
}
