#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct DL_node
{
    struct DL_node *prev;
    struct DL_node *next;
    int size;
    int tag;
};

struct DL_node* create_node(int**);
void push(struct DL_node*,int,int);

struct DL_node* create_node(int **t)
{
    struct DL_node *n;
    
    n = (struct DL_node*)malloc(sizeof(struct DL_node));
    n->size = 0;
    n->tag = **t;
    n->next = NULL;
    n->prev = NULL;
    **t = **t +1;
    return(n);
}

void push(struct DL_node **start,int s,int *count)
{
    struct DL_node *ptr;
    
    ptr = create_node(&count);
    if(ptr != NULL)
    {
        if((*start) != NULL)
        {
            (*start)->prev = ptr;
        }
        ptr->size = s;
        ptr->next = *start;
        *start = ptr;
    }
    else{
        printf("Process Failed");
    }
}

void PrintList(int c,struct DL_node *ptr)
{
    struct DL_node *temp;
    if(c == 6)
    {
        printf("\n\nBlockId  Size\n");
    }
    else
    {
        printf("\n\nTag  Size\n");
    }
    if(ptr== NULL && c == 6)
    {
        printf("\nProcess is Not Allocated (First allocate it by using choice no. 3)");
    }
    else if(ptr == NULL && c == 7)
    {
        printf("\nNo block is present");
    }
    else
    {
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        while(ptr != NULL)
        {
            printf("%d \t%d\n",ptr->tag,ptr->size);
            ptr = ptr->prev;
        }
    }
}


struct allocate
{
    struct allocate *prev;
    struct allocate *next;
    int size;
    int tag;
    int blockId;
};

struct allocate *create_allocate(int **t);
void FirstFit(struct DL_node *blockSize,struct DL_node **old_processSize,struct DL_node *new_processSize,int *a_size,struct allocate **head);
void Print_Allocate(struct allocate *head);
void delete_allocate(int t,struct allocate **head,struct DL_node **processSize,struct DL_node *blockSize);

struct allocate *create_allocate(int **t)
{
    struct allocate* ptr = (struct allocate)malloc(sizeof(struct allocate));
    
    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->tag = *(*t);
    **t = **t+1;

    return(ptr);
}

void FirstFit(struct DL_node *blockSize,struct DL_node **old_processSize,struct DL_node *new_processSize,int *a_size,struct allocate **head)
{
    struct allocate *alloc,*temp,*lptr;
    bool flag = true;
    struct DL_node *ptr,*old;
    int j=0;
    
    alloc = NULL;
    old = *old_processSize;
    
    if(old == NULL)
    {
        *old_processSize = new_processSize;
    }
    else
    {
        while(old->next != NULL)
        {
            old = old->next;
        }
        old->next = new_processSize;
    }
    
    while(new_processSize != NULL)
    {
        flag = true;
        ptr = blockSize;
        j=0;
        
        while(ptr != NULL && flag == true)
        {
            if(ptr->size >= new_processSize->size)
            {
                temp = create_allocate(&a_size);
                temp->size = new_processSize->size;
                if(alloc == NULL)
                {
                    alloc = temp;
                    lptr = temp;
                }
                else
                {
                    alloc->next = temp;
                    temp->prev = alloc;
                    alloc = temp;
                }
                alloc->blockId = j;
                ptr->size = ptr->size - new_processSize->size;
                flag = false;
            }
            j++;
            ptr = ptr->next;
        }
        
        if(flag == true)
        {
            printf("\n%d block can't be allocated memory",new_processSize->size);
        }
        new_processSize = new_processSize->next;
    }
    
    if(*head == NULL)
    {
        *head = lptr;
    }
    else
    {
        temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = lptr;
        lptr->prev = temp;
    }
}

void Print_Allocate(struct allocate *head)
{
    printf("\n\nTag  Block_Id   Size\n");
    while(head != NULL)
    {
        if(head->blockId != -1)
        {
            printf("%d \t%d \t%d\n",head->tag,head->blockId,head->size);
        }
        else
        {
            printf("Memeory is not allocated for the process %d\n",head->size);
        }
        head = head->next;
    }
}

void delete_allocate(int t,struct allocate **head,struct DL_node **processSize,struct DL_node *blockSize)
{
    struct allocate *curr;
    struct DL_node *temp;
    
    curr = *head;
    while(curr != NULL && t != curr->tag)
    {
        curr = curr->next;
    }
    printf("OUt");
    if(curr != NULL)
    {
        while(blockSize->tag != curr->blockId)
        {
            printf("1 ");
            blockSize = blockSize->next;
        }
        blockSize->size = blockSize->size + curr->size;
        printf("2 ");
        temp = *processSize;
        while(temp->size != curr->size)
        {
            temp = temp->next;
        }
        printf("3 ");
        if(temp->prev == NULL)
        {
            *processSize = temp->next;
        }
        else
        {
            temp->prev->next = temp->next;
            if(temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }
        }
        free(temp);
        printf("4 ");
        if(curr->prev == NULL)
        {
            *head = curr->next;
        }
        else
        {
            curr->prev->next = curr->next;
            if(curr->next != NULL)
            {
                curr->next->prev = curr->prev;
            }
        }
        free(curr);printf("5 ");
    }
    else
    {
        printf("\nNo Tag Id found with Id %d",t);
    }
    printf("6 ");
}


int main()
{
    struct allocate* alloc;
    struct DL_node *blockSize,*processSize,*new_proc,*temp;
    int value=0,i;
    int block_tag=0,process_tag=0,allocate_tag=0,choice;
    blockSize = NULL;
    processSize = NULL;
    alloc = NULL;
    new_proc = NULL;
    
    while(choice != 8)
    {
        printf("Choose the operation you want to perform:\n");
        printf("\n1. Creating blocks with different memory size.");
        printf("\n2. Creating processes that required memory.");
        printf("\n3. Allocate memory to the processes.");
        printf("\n4. Print the allocated memory list.");
        printf("\n5. Deleting a particular process");
        printf("\n6. Print Block Sizes list.");
        printf("\n7. Print Processes Sizes list.");
        printf("\n8. Exit");
        
        printf("\nChoice = ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter the size of blocks (enter -1 when process is done): \n");
    
                scanf("%d",&value);
                
                while(value != -1)
                {
                    push(&blockSize,value,&block_tag);
                    scanf("%d",&value);
                }
                
                break;
                
            case 2:
                printf("Enter the size of processes (enter -1 when process is done): \n");
    
                scanf("%d",&value);
                while(value != -1)
                {
                    push(&new_proc,value,&process_tag);
                    scanf("%d",&value);
                }
                break;
                
            case 3:
                FirstFit(blockSize,&processSize,new_proc,&allocate_tag,&alloc);
                new_proc = NULL;
                break;
                
            case 4:
                Print_Allocate(alloc);
                
                break;
                
            case 5:
                printf("Enter the tag of the process that you want to delete\ntag = ");
                scanf("%d",&value);
                delete_allocate(value,&alloc,&processSize,blockSize);
                
                break;
                
            case 6:
                PrintList(6,blockSize);
                break;
                
            case 7:
                PrintList(7,processSize);
                break;
                
            case 8:
                exit(0);
        }
        printf("\n---------------------------------------------------------------------\n");
    }
    
    return(0);
}
