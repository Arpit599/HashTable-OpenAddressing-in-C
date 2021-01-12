#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 10

int size = 0;

struct node *search(int);
void delete (int);
void display();
void initArray();
int hashFun(int);
void insert(int, int);

struct node
{
    int key;
    int data;
    struct node* next;
};

struct hashTable
{
    struct node* head;
    struct node* tail;
};

struct hashTable hashArray[SIZE];

void initArray()
{
    for (int i = 0; i < SIZE; i++)
    {
        hashArray[i].head = NULL;
        hashArray[i].tail = NULL;
    }
}

int hashFun(int key)
{
    return key % SIZE;
}

void insert(int key, int data)
{
    if (size == SIZE)
    {
        printf("Hash table is already full\n");
        return;
    }

    int hashCode = hashFun(key);

    struct node* temp = hashArray[hashCode].head;

    while (temp != NULL)
    {
        if (temp->key == key)
        {
            printf("Key already present, therefore updating the key\n");
            temp->data = data;
            return;
        }
        temp = temp->next;
    }

    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->data = data;
    new->key = key;
    new->next = NULL;

    struct node* listHead = hashArray[hashCode].head;

    if (listHead == NULL)
    {
        hashArray[hashCode].head = new;
        // hashArray[hashCode].tail = new;
    }
    else
    {
        while(listHead->next != NULL)
        listHead = listHead->next;
        listHead->next = new;
    }
    //free(listHead);
    size++;
}

struct node *search(int key)
{
    if (size == 0)
    {
        printf("Hash table is empty");
        return NULL;
    }
    int hashIndex = hashFun(key);
    struct node *listHead = hashArray[hashIndex].head;

    while (listHead != NULL)
    {
        if (listHead->key == key)
            return listHead;
        listHead = listHead->next;
    }
    free(listHead);
    return NULL;
}

void delete (int key)
{
    struct node *item = search(key);
    int hashCode = hashFun(key);

    if (item == NULL)
    {
        printf("Element not present for deletion\n");
        return;
    }
    else if (item == hashArray[hashCode].head)
    {
        struct node *temp = hashArray[hashCode].head;
        hashArray[hashCode].head = hashArray[hashCode].head->next;
        free(temp);
    }
    else
    {
        struct node *temp = hashArray[hashCode].head;
        struct node *prev = NULL;

        while(temp != NULL && temp->key != key)
        {
            //printf("Inside while loop\n");
            prev = temp;
            temp = temp->next;
        }

        if(temp == NULL)
        {
            //printf("Element not present for deletion from temp == null condition\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
    }
    
    size--;
    printf("Element deleted successfully\n");
}

void display()
{
    if(size == 0)
    {
        printf("Empty hash table therefore no elements for display\n");
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        struct node *listHead = hashArray[i].head;
        printf("Index = %d ", i);
        while(listHead != NULL)
        {
            printf("(key = %d, value = %d) ", listHead->key, listHead->data);
            listHead = listHead->next;
        }
        printf("\n");
    }
}

int main(void)
{
    initArray();

    while (true)
    {
        printf("Search an element : 1\n");
        printf("Delete an element : 2\n");
        printf("Insert an element : 3\n");
        printf("Display the table : 4\n");
        printf("Enter your choice : ");
        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (size == 0)
            {
                printf("Hash table is already empty\n");
                break;
            }
            printf("Enter the key to be searched : ");
            int searchKey;
            scanf("%d", &searchKey);
            struct node *item = search(searchKey);
            if (item == NULL)
                printf("Element not found\n");
            else
                printf("Element is present in the hash table\n");
            break;

        case 2:
            if (size == 0)
            {
                printf("Hash table is already empty\n");
                break;
            }
            printf("Enter the key to be deleted : ");
            int deleteKey;
            scanf("%d", &deleteKey);
            delete (deleteKey);
            break;

        case 3:
            printf("Enter the key, value to be inserted : ");
            int key, value;
            scanf("%d %d", &key, &value);
            insert(key, value);
            break;

        case 4:
            display();
            break;

        default:
            break;
        }
    }
    return 0;
}