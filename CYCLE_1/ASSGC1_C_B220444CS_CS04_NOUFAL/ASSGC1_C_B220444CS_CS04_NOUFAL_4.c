#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int findLargestPrime(int limit) {
    for (int i = limit - 1; i >= 2; i--) {
        if (isPrime(i)) {
            return i;
        }
    }

    return -1;  
}

int hashValue(int key, int size) {
    return key % size;
}

int LProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    int i = 0;
    
    while (hashTable[(index + i) % size] != 0) {
        i++;
        (*collisions)++;
    }

    return (index + i) % size;
}

int DHProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    int i = 0;
    int primeNo = findLargestPrime(size);
    int hash2 = primeNo - (key % primeNo);

    while (hashTable[(index + i * hash2) % size] != 0) {
        i++;
        (*collisions)++;
    }

    return (index + i * hash2) % size;
}

int QProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    int i = 0;

    while (hashTable[(index + i * i) % size] != 0) {
        i++;
        (*collisions)++;
    }

    return (index + i * i) % size;
}

int LinearHashProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    if (hashTable[index] != 0) {
        index = LProbe(key, hashTable, size, collisions);
    }

    printf("%d ", index);
    hashTable[index] = key;

    return *collisions;
}

int DoubleHashingProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    if (hashTable[index] != 0) {
        index = DHProbe(key, hashTable, size, collisions);
    }

    printf("%d ", index);
    hashTable[index] = key;

    return *collisions;
}

int QuadraticHashProbe(int key, int hashTable[], int size, int* collisions) {
    int index = hashValue(key, size);
    if (hashTable[index] != 0) {
        index = QProbe(key, hashTable, size, collisions);
    }

    printf("%d ", index);
    hashTable[index] = key;

    return *collisions;
}

int main() {
    int tableSize;
    scanf("%d", &tableSize);

    int LinearhashTable[tableSize];
    int QuadratichashTable[tableSize];
    int DoublehashTable[tableSize];

    for (int i = 0; i < tableSize; i++) {
        LinearhashTable[i] = 0;
        QuadratichashTable[i] = 0;
        DoublehashTable[i] = 0;
    }

    int arr[tableSize];
    int k = 0;


    char num[1000];
    char s[10];
    s[0] = '\0';

    scanf(" %[^\n]s", num);

    for(int i=0; num[i] != '\0'; i++){
        if(num[i] != ' ' && num[i] != '\0'){
            int len = strlen(s);
            s[len] = num[i];
            s[len+1] = '\0';
        }
        else{
            arr[k++] = atoi(s);
            s[0] = '\0';
        }
    }

    if(s[0] != '0'){
        arr[k] = atoi(s);
        k++;
    }
  
    // scanf(" %[^\n]s", num);
    // for(int i=0; num[i] != '\0'; i++){
    //   if(num[i] != ' ' && num[i] != '\0'){
    //     int len = strlen(s);
    //     s[len] = num[i];
    //     s[len + 1] = '\0';
    //   }
    //   else{
    //     arr[k++] = atoi(s);
    //     s[0] = '\0';
    //   }
    // }
    
    if(s[0] != '\0'){
      arr[k] = atoi(s);
      k++;
    }

    int linearCollisions = 0;
    for (int i = 0; i < k; i++) {
        linearCollisions = LinearHashProbe(arr[i], LinearhashTable, tableSize, &linearCollisions);
    }
    printf("\n");
    printf("%d\n", linearCollisions);

    int quadraticCollisions = 0;
    for (int i = 0; i < k; i++) {
        quadraticCollisions = QuadraticHashProbe(arr[i], QuadratichashTable, tableSize, &quadraticCollisions);
    }

    printf("\n");
    printf("%d\n", quadraticCollisions);

    int doubleHashingCollisions = 0;
    for (int i = 0; i < k; i++) {
        doubleHashingCollisions = DoubleHashingProbe(arr[i], DoublehashTable, tableSize, &doubleHashingCollisions);
    }

    printf("\n");
    printf("%d\n", doubleHashingCollisions);

    return 0;
}

