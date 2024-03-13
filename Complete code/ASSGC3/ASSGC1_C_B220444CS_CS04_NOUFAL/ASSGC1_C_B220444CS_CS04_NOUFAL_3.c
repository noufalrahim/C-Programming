#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#include <string.h>

struct ListNode
{
    char name[1000];
    char rollNo[1000];
    int age;
    struct ListNode *next;
};

struct ListNode *HashTable[SIZE];
int findGroup(char *name, int age)
{
    int sum = 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        int val = name[i];
        sum = sum + val;
    }

    return (sum + age)% 4;
}
void insert(char *name, int age, char *rollNo)
{
    int index = findGroup(name, age);

    struct ListNode *newnode = (struct ListNode *)malloc(sizeof(struct ListNode));
    strcpy(newnode->name, name);
    strcpy(newnode->rollNo, rollNo);
    newnode->age = age;
    newnode->next = NULL;

    if (HashTable[index] == NULL)
    {
        HashTable[index] = newnode;
    }
    else
    {
        struct ListNode *temp = HashTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newnode;
    }
}

void display(int index)
{
    struct ListNode *temp = HashTable[index];
    int count = 0;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    temp = HashTable[index];
    printf("%d ", count);
    while (temp != NULL)
    {
        printf("%s ", temp->name);
        temp = temp->next;
    }
    printf("\n");
}

void DepartmentDisplay(char *dept, int index)
{
    struct ListNode *temp = HashTable[index];
    int count = 0;

    while (temp != NULL)
    {
        char branch[3];
        branch[0] = temp->rollNo[7];
        branch[1] = temp->rollNo[8];
        branch[2] = '\0';
        if (strcmp(branch, dept) == 0)
        {
            count++;
        }
        temp = temp->next;
    }

    temp = HashTable[index];
    if (count == 0)
    {
        printf("-1\n");
        return;
    }

    while (temp != NULL)
    {
        char branch[3];
        branch[0] = temp->rollNo[7];
        branch[1] = temp->rollNo[8];
        branch[2] = '\0';
        if (strcmp(branch, dept) == 0)
        {
            printf("%s ", temp->name);
        }
        temp = temp->next;
    }
    printf("\n");
}

void convertToUpperCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 97 && str[i] <= 122)
        {
            str[i] -= 32;
        }
    }
    return;
}

void printList(int index)
{
    struct ListNode *temp = HashTable[index];
    while (temp != NULL)
    {
        printf("%s %d %s \n", temp->name, temp->age, temp->rollNo);
        temp = temp->next;
    }
}

void main()
{
    int totalLength;
    scanf("%d", &totalLength);
    for (int i = 0; i < totalLength; i++)
    {
        char name[1000];
        int age;
        char rollNo[1000];
        scanf(" %s", name);
        scanf(" %s", rollNo);
        scanf("%d", &age);
        insert(name, age, rollNo);
    }

    char choice;

    while (1)
    {
        scanf(" %c", &choice);
        if (choice == 'e')
        {
            break;
        }

        if(choice == 'c'){
            int index;
            scanf("%d", &index);
            display(index);
        }
        else if(choice == '1' || choice == '2' || choice == '3' || choice == '4'){
            char dept[2];
            int index = choice - '0';
            scanf(" %s", dept);
            convertToUpperCase(dept);
            DepartmentDisplay(dept , index);
        }
    }
}