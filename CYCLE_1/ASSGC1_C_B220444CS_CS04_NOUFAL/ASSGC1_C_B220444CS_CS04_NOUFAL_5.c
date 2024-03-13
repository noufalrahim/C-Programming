#include<stdio.h>
#include<stdlib.h>

void main(){
    int arrSize;
    int lengthOfWindow;
    scanf("%d", &arrSize);
    scanf("%d", &lengthOfWindow);
    int arr[arrSize];
    for(int i=0; i<arrSize; i++){
        scanf("%d", &arr[i]);
    }
    int max = -1000;
    for(int i=0; i<arrSize; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    int left = 0;
    int right = lengthOfWindow - 1;
    int count = 0;
    int *distinctNumbers = (int *)malloc(arrSize * sizeof(int));
    int m = 0;
    while (right < arrSize)
    {
        int hash[max+1];
        for (int i = 0; i <= max; i++)
        {
            hash[i] = 0;
        }
        
        for(int i=left; i<=right; i++){
            hash[arr[i]]++;
        }
       
        for(int i=0; i<=max; i++){
            if(hash[i] > 0){
                count++;
            }
        }

        distinctNumbers[m++] = count;
        count = 0;
        for(int i=0; i<=max; i++){
            hash[i] = 0;
        }
        left = left + 1;
        right = right + 1;
    }

    for(int i=0; i<m; i++){
        printf("%d ", distinctNumbers[i]);
    } 
}