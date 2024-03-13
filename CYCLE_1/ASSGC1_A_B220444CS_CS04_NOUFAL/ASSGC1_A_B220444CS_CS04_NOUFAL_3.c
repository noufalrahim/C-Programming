#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient
{
    char name[100];
    int severity;
    char time[5];
    struct patient *next;
};

int checkTime(char *a, char *b)
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i] < b[i])
        {
            return 1;
        }
        else if (a[i] > b[i])
        {
            return 0;
        }
    }
    return 0;
}

struct patient *admit(struct patient *head, char *name, int severity, char *time)
{
    struct patient *newpatient = (struct patient *)malloc(sizeof(struct patient));
    strcpy(newpatient->name, name);
    newpatient->severity = severity;
    strcpy(newpatient->time, time);
    newpatient->next = NULL;

    if (head == NULL || head->severity < severity || (head->severity == severity && strcmp(head->time, time) > 0))
    {
        newpatient->next = head;
        head = newpatient;
        return head;
    }
    else
    {
        struct patient *temp = head;
        while (temp->next != NULL && (temp->next->severity > severity || (temp->next->severity == severity && strcmp(temp->next->time, time) < 0)))
        {
            temp = temp->next;
        }
        newpatient->next = temp->next;
        temp->next = newpatient;
    }

    return head;
}

void checkNextPatient(struct patient *head)
{
    if (head != NULL)
    {
        printf("%s ", head->name);
        printf("%d ", head->severity);
        printf("%s ", head->time);
        printf("\n");
    }
}

struct patient *treatNextPatient(struct patient *head)
{
    if (head != NULL)
    {
        printf("%s ", head->name);
        printf("%d ", head->severity);
        printf("%s \n", head->time);

        struct patient *temp = head;
        head = head->next;
        free(temp);
    }

    return head;
}

struct patient *dischargePatient(struct patient *head, char *name, char *time)
{
    struct patient *temp = head;
    struct patient *prev = NULL;

    while (temp != NULL && (strcmp(temp->name, name) != 0 || strcmp(temp->time, time) != 0))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        if (prev != NULL)
        {
            prev->next = temp->next;
        }
        else
        {
            head = temp->next;
        }

        free(temp);
    }

    return head;
}

struct patient *updatePriority(struct patient *head, char *name, char *time, int severity)
{
    struct patient *temp = head;
    struct patient *prev = NULL;

    while (temp != NULL && (strcmp(temp->name, name) != 0 || strcmp(temp->time, time) != 0))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        temp->severity = severity;
    }

    if (prev != NULL)
    {
        prev->next = temp->next;
    }
    else
    {
        head = temp->next;
    }

    head = admit(head, name, severity, time);

    return head;
}

void printAllPatients(struct patient *head)
{
    while (head != NULL)
    {
        printf("%s ", head->name);
        printf("%d ", head->severity);
        printf("%s \n", head->time);

        head = head->next;
    }
}

int main()
{
    char nameOfPatient[1000];
    char timeOfPatient[1000];
    char a;
    int x;
    struct patient *head = NULL;

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
            
        }
        switch (a)
        {
        case 'a':
            scanf(" %s", nameOfPatient);
            scanf(" %d", &x);
            scanf(" %s", timeOfPatient);
            head = admit(head, nameOfPatient, x, timeOfPatient);
            break;
        case 't':
            head = treatNextPatient(head);
            break;
        case 'c':
            checkNextPatient(head);
            break;
        case 'd':
            scanf(" %s %s", nameOfPatient, timeOfPatient);
            head = dischargePatient(head, nameOfPatient, timeOfPatient);
            break;
        case 'u':
            scanf(" %s %s %d", nameOfPatient, timeOfPatient, &x);
            head = updatePriority(head, nameOfPatient, timeOfPatient, x);
            break;
        case 'p':
            printAllPatients(head);
            break;
        }
    }
    struct patient *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
