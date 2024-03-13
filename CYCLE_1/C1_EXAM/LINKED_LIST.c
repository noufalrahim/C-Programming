#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *createNode(int val)
{
    struct ListNode *newnode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newnode->next = NULL;
    newnode->val = val;
    return newnode;
}

struct ListNode *insertNode(struct ListNode *head, int val)
{
    struct ListNode *newnode = createNode(val);
    if (head == NULL)
    {
        return newnode;
    }

    struct ListNode *temp = head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newnode;
    return head;
}

struct ListNode *deleteNode(struct ListNode *head, int index)
{
    int count = 1;
    struct ListNode *temp = head;
    struct ListNode *prev = NULL;
    if(index == 1){
        head = head -> next;
        return head;
    }
    while (count < index && temp != NULL)
    {
        count++;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL || count > index)
    {
        printf("-1\n");
        return head;
    }

    prev->next = temp->next;
    free(temp);
    return head;
}

void printList(struct ListNode *head)
{
    if (head == NULL)
    {
        printf("-1\n");
        return;
    }
    while (head != NULL)
    {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

struct ListNode* removeDuplicates(struct ListNode* head){
    struct ListNode* temp = head;
    struct ListNode* headPtr = head;
    struct ListNode* prev = NULL;
    if(head == NULL){
        return NULL;
    }
    while (headPtr != NULL)
    {
        prev = temp;
        temp = headPtr -> next;
        while (temp != NULL)
        {
            if(temp -> val == headPtr -> val){
                prev -> next = temp -> next;
                free(temp);
                temp = prev -> next;
            }
            else{
                prev = temp;
                temp = temp -> next;
            }
            
        }

        headPtr = headPtr -> next;
    }

    return head;
}

void main()
{
    char choice;
    struct ListNode *head = NULL;
    int num;
    while (1)
    {
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'a':
            scanf("%d", &num);
            head = insertNode(head, num);
            break;
        case 'r':
            scanf("%d", &num);
            head = deleteNode(head, num);
            break;
        case 'p':
            printList(head);
            break;
        case 'd':
            head = removeDuplicates(head);
            printList(head);
            break;
        default:
            break;
        }
    }
}