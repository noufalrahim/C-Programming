#include <stdio.h>
#include<stdlib.h>
int hashValue(int key, int size)
{
    return key % size;
}

int LProbe(int key, int hashTable[], int size)
{
    int index = hashValue(key, size);
    int i = 0;

    while (hashTable[(index + i) % size] != 0)
    {
        i++;
    }

    return (index + i) % size;
}

void LinearHashProbe(int key, int hashTable[], int size)
{
    int index = hashValue(key, size);
    if (hashTable[index] != 0)
    {
        index = LProbe(key, hashTable, size);
    }

    printf("%d ", key);
    hashTable[index] = key;
}

int isPresent(int key, int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == key)
        {
            return 1;
        }
    }
    return 0;
}

void unionOfSets(int A[], int sizeofA, int B[], int sizeofB, int hashTable[], int SIZE)
{
    for (int i = 0; i < sizeofA; i++)
    {
        LinearHashProbe(A[i], hashTable, SIZE);
    }

    for (int i = 0; i < sizeofB; i++)
    {
        if (!isPresent(B[i], A, sizeofA))
        {
            LinearHashProbe(B[i], hashTable, SIZE);
        }
    }
}

void intersectionOfSets(int A[], int sizeofA, int B[], int sizeofB, int hashTable[], int SIZE)
{
    for (int i = 0; i < sizeofA; i++)
    {
        if (isPresent(A[i], B, sizeofB))
        {
            LinearHashProbe(A[i], hashTable, SIZE);
        }
    }
    printf("\n");
}

void setDifference(int A[], int sizeofA, int B[], int sizeofB, int hashTable[], int SIZE)
{
    for (int i = 0; i < sizeofA; i++)
    {
        if (!isPresent(A[i], B, sizeofB))
        {
            LinearHashProbe(A[i], hashTable, SIZE);
        }
    }
    printf("\n");
}

int main()
{
    int sizeofA;
    int sizeofB;

    scanf("%d %d", &sizeofA, &sizeofB);

    int *A = (int *)malloc(sizeofA * sizeof(int));
    int *B = (int *)malloc(sizeofB * sizeof(int));

    for (int i = 0; i < sizeofA; i++)
    {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < sizeofB; i++)
    {
        scanf("%d", &B[i]);
    }

    int SIZE = sizeofA > sizeofB ? 2 * sizeofA : 2 * sizeofB;
    int hashTable[SIZE];

    char choice;

    while (choice != 'e')
    {
        scanf(" %c", &choice);
        for (int i = 0; i < SIZE; i++)
        {
            hashTable[i] = 0;
        }

        if (choice == 'u')
        {
            char choice1;
            scanf(" %c", &choice1);
            char choice2;
            scanf(" %c", &choice2);
            if (choice1 == 'A' && choice2 == 'B')
            {
                unionOfSets(A, sizeofA, B, sizeofB, hashTable, SIZE);
            }
            else if (choice1 == 'B' && choice2 == 'A')
            {
                unionOfSets(B, sizeofB, A, sizeofA, hashTable, SIZE);
            }
            printf("\n");
        }
        else if (choice == 'i')
        {
            char choice1;
            scanf(" %c", &choice1);
            char choice2;
            scanf(" %c", &choice2);
            if (choice1 == 'A' && choice2 == 'B')
            {
                intersectionOfSets(A, sizeofA, B, sizeofB, hashTable, SIZE);
            }
            else if (choice1 == 'B' && choice2 == 'A')
            {
                intersectionOfSets(B, sizeofB, A, sizeofA, hashTable, SIZE);
            }
        }
        else if (choice == 's')
        {
            char choice1;
            scanf(" %c", &choice1);
            char choice2;
            scanf(" %c", &choice2);
            if (choice1 == 'A' && choice2 == 'B')
            {
                setDifference(A, sizeofA, B, sizeofB, hashTable, SIZE);
            }
            else if (choice1 == 'B' && choice2 == 'A')
            {
                setDifference(B, sizeofB, A, sizeofA, hashTable, SIZE);
            }
        }
    }

    

    return 0;
}
