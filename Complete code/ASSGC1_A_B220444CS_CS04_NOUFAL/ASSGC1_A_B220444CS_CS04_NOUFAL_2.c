#include <stdio.h>
#include<stdlib.h>
struct node{
    int val;
    struct node* next;
};

void Display(struct node* head){
    while(head != NULL){
        printf("%d ",head -> val);
        head = head -> next;
    }    
}


struct node* createNode(int val){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode -> val = val;
    newnode -> next = NULL;
    return newnode;
}

struct node* insert(struct node* head, int val){
    struct node* newnode = createNode(val);
    if(head == NULL){
        head = newnode;
        return head;
    }
    struct node* temp = head;
    while(temp -> next != NULL){
        temp = temp -> next;
    }
    temp -> next = newnode;
    return head;
}

struct node* delete(struct node* head, int i) {
    int count = 1;
    struct node* temp = head;
    struct node* prevNode = NULL;

    if (head == NULL) {
        printf("-1\n");
        return NULL;
    }

    while (count < i && temp != NULL) {
        prevNode = temp;
        temp = temp->next;
        count++;
    }

    if (temp != NULL) {
        if (prevNode != NULL) {
            printf("%d\n", temp->val);
            prevNode->next = temp->next;
        } else {
            printf("%d\n", temp->val); 
            head = temp->next;
        }
        free(temp);
    }

    return head;
}

struct node* Rduplicate(struct node* head){
    struct node* temp = head;
    struct node* prevNode = NULL;
    if(temp == NULL){
        return NULL;
    }
    while(temp != NULL){
        struct node* temp1 = temp -> next;
        prevNode = temp;
        while(temp1 != NULL){
            if(temp -> val == temp1 -> val){
                prevNode -> next = temp1 -> next;
            }
            else{
                 prevNode = temp1;
            }
            temp1 = temp1 -> next;
         
        }
        temp = temp -> next;
    }
    Display(head);
    printf("\n");
    return head;
   
}

int palindrome(struct node* head){
    int count = 0;
    struct node* temp = head;
    while(temp != NULL){
        temp = temp -> next;
        count++;
    }
    int *arr = (int *)malloc(sizeof(int) * count);
    temp = head;
    int i = 0;
    while(temp != NULL){
        arr[i] = temp -> val;
        temp = temp -> next;
        i++;
    }
    int j = count - 1;
    for(i = 0; i < count/2; i++){
        if(arr[i] != arr[j]){
            return 0;
        }
        j--;
    }
    return 1;
}

int main() {
    char a;
    int x;
    struct node *head = NULL;
    int dup;
    while (1)
    {
        scanf(" %c", &a);

        if (a == 'e')
        {
            break;
        }

        switch (a)
        {
        case 'a':
            scanf("%d", &x);
            head = insert(head, x);
            break;
        case 'r':
            scanf("%d", &x);
            head = delete(head, x);
            break;
        case 'd':
            head = Rduplicate(head);
            break;
        case 'p':
            dup = palindrome(head);
            if (dup)
            {
                printf("Y\n");
            }
            else{
                printf("N\n");
            }
            break;
        case 's':
            Display(head);
            break;
        }
    }
    return 0;
}