#include<stdio.h>
#include<stdlib.h>
struct ListNode{
    int val;
    struct ListNode* next;
};



int hashValue(int key, int SIZE){
    return key % SIZE;
}

struct ListNode* createNode(int key){
    struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newnode -> val = key;
    newnode -> next = NULL;
    return newnode;
}

void insert(int key, int SIZE, struct ListNode* hashTable[]) {
    int index = hashValue(key, SIZE);
    struct ListNode* newnode = createNode(key);

    if (hashTable[index] == NULL || hashTable[index]->val > key) {
        newnode->next = hashTable[index];
        hashTable[index] = newnode;
        return;
    }

    struct ListNode* temp = hashTable[index];
    struct ListNode* prev = NULL;

    while (temp != NULL && temp->val < key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL && temp->val == key) {
        temp->val = key;
        free(newnode);  
    } else {
        prev->next = newnode;
        newnode->next = temp;
    }
}

void search(int key, int SIZE, struct ListNode* hashTable[]){
    int index = hashValue(key, SIZE);
    struct ListNode* temp = hashTable[index];
    int count = 0;

    
    while (temp != NULL)
    {
        count++;
        if(temp -> val == key){
            printf("%d %d \n",index, count);
            return;
        }
        
        temp = temp -> next;
    }
    printf("-1 \n");
    return;
}

void delete(int key, int SIZE, struct ListNode* hashTable[]){
    int index = hashValue(key, SIZE);
    struct ListNode* head = hashTable[index];
    struct ListNode* temp = hashTable[index];
    struct ListNode* prev = NULL;

    int count = 0;
    
    while (temp -> next != NULL && temp -> val != key)
    {
        count++;
        prev = temp;
        temp = temp -> next;
    }

    if(temp == NULL){
        printf("-1\n");
        return;
    }

    if(temp -> val != key){
        printf("-1\n");
        return;
    }

    if (prev == NULL) {
        hashTable[index] = temp->next;
    } else {
        prev->next = temp->next;
    }
    printf("%d %d", index, count+1);
    printf("\n");
    return;
}


void printHashTable(int SIZE, struct ListNode* hashTable[], int index) {
    struct ListNode* temp = hashTable[index];
    if(temp == NULL){
        printf("-1\n");
        return;
    }
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void update(int oldKey, int newKey, int SIZE, struct ListNode* hashTable[]) {
    delete(oldKey, SIZE, hashTable);
    insert(newKey, SIZE, hashTable);
}

int main() {
    int SIZE;
    scanf("%d", &SIZE);
    struct ListNode* hashTable[SIZE];

    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    char choice;

    while (1) {
        scanf(" %c", &choice);
        if (choice == 'i') {
            int key;
            scanf("%d", &key);
            insert(key, SIZE, hashTable);
        } else if (choice == 's') {
            int key;
            scanf("%d", &key);
            search(key, SIZE, hashTable);
        } else if (choice == 'd') {
            int key;
            scanf("%d", &key);
            delete(key, SIZE, hashTable);
        } else if (choice == 'p') {
            int index;
            scanf("%d", &index);
            printHashTable(SIZE, hashTable, index);
        } else if (choice == 'u') {
            int oldKey, newKey;
            scanf("%d %d", &oldKey, &newKey);
            update(oldKey, newKey, SIZE, hashTable);
        } else if (choice == 'e') {
            break;
        }
    }
    

    return 0;
}

