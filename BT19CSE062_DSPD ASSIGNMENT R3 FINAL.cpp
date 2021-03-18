#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct book
{
    char name[20];
    char subject[20];
    char authors[100];
    int access;
    char date[8];//YY-MM-DD
    int available;//if available then 1 else 0
    int extra_days;
};

struct member
{
    char name[20];
    char department[20];
    char designation[20];
    char memberId[20];
    int book_hold[4];
    int no_of_books;
};

struct library
{
    struct book;
    int hall;
    int rack;
    int row;
    int avail;
    int days;
};

struct book bk[1000];
struct member staff[100];
struct member student[100];

int bookCount=0;
int fac=0;
int stud=0;

//sorting
void sort_bk(void)
{
    for(int i=0;i<bookCount-1;i++){
        for(int j=0;j<bookCount-i-1;j++){
            if(strcmp(bk[j].name,bk[j+1].name)>0){
                struct book temp=bk[j];
                bk[j]=bk[j+1];
                bk[j+1]=temp;
            }
        }
    }
}

void insert_book(void)
{
    printf("Enter name of book\n");
    gets(bk[bookCount].name);
    printf("Enter subject\n");
    gets(bk[bookCount].subject);
    printf("Enter authors\n");
    gets(bk[bookCount].authors);
    printf("Enter accession number\n");
    scanf("%d",&bk[bookCount].access);
    printf("Enter date of publish\n");
    gets(bk[bookCount].date);
    bk[bookCount].available=1;
    sort_bk();
    bookCount++;
}

void new_fac(void)
{
    printf("Enter name\n");
    gets(staff[fac].name);
    printf("Enter department\n");
    gets(staff[fac].department);
    printf("Enter designation\n");
    gets(staff[fac].designation);
    printf("Enter member ID\n");
    gets(staff[fac].memberId);
    staff[fac].no_of_books=0;
    fac++;
}

void new_stud(void)
{
    printf("Enter name\n");
    gets(student[stud].name);
    printf("Enter department\n");
    gets(student[stud].department);
    strcpy(student[stud].designation,"student");
    printf("Enter member ID\n");
    gets(student[stud].memberId);
    student[stud].no_of_books=0;
    stud++;
}

void print_max_book_people(void)
{
    int maxi=0;
    for(int i=0;i<stud;i++){
        if(student[i].no_of_books > maxi){
            maxi=student[i].no_of_books;
        }
    }
    for(int i=0;i<stud;i++){
        if(student[i].no_of_books == maxi){
            puts(student[i].name);
        }
    }
    //faculty
    maxi=0;
    for(int i=0;i<fac;i++){
        if(staff[i].no_of_books > maxi){
            maxi=staff[i].no_of_books;
        }
    }
    for(int i=0;i<stud;i++){
        if(staff[i].no_of_books == maxi){
            puts(staff[i].name);
        }
    }
}

void calc_fine(void)
{
    int maxi=0;
    for(int i=0;i<stud;i++){
            int curfine=0;
        for(int j=0;j<4;j++){
            if(student[i].book_hold[j]!=0){
                for(int k=0;k<bookCount;k++){
                    if(bk[k].access==student[i].book_hold[j]){
                        curfine+=50*bk[k].extra_days;
                    }
                }
            }
        }
        if(maxi<curfine) maxi=curfine;
    }
    for(int i=0;i<stud;i++){
        int curfine=0;
        for(int j=0;j<4;j++){
            if(student[i].book_hold[j]!=0){
                for(int k=0;k<bookCount;k++){
                    if(bk[k].access==student[i].book_hold[j]){
                        curfine+=50*bk[k].extra_days;
                    }
                }
            }
        }
        if(curfine==maxi) puts(student[i].name);
    }
    //faculty
    maxi=0;
    for(int i=0;i<fac;i++){
            int curfine=0;
        for(int j=0;j<4;j++){
            if(staff[i].book_hold[j]!=0){
                for(int k=0;k<bookCount;k++){
                    if(bk[k].access==staff[i].book_hold[j]){
                        curfine+=50*bk[k].extra_days;
                    }
                }
            }
        }
        if(maxi<curfine) maxi=curfine;
    }
    for(int i=0;i<fac;i++){
        int curfine=0;
        for(int j=0;j<4;j++){
            if(staff[i].book_hold[j]!=0){
                for(int k=0;k<bookCount;k++){
                    if(bk[k].access==staff[i].book_hold[j]){
                        curfine+=50*bk[k].extra_days;
                    }
                }
            }
        }
        if(curfine==maxi) puts(staff[i].name);
    }
}

void sort_staff(void)
{
    for(int i=0;i<fac;i++){
        for(int j=0;j<fac-1;j++){
            if(strcmp(staff[j].name,staff[j+1].name) > 0){
                struct member temp=staff[j];
                staff[j]=staff[j+1];
                staff[j+1]=temp;
            }
        }
    }
}

void sort_students(void)
{
    for(int i=0;i<stud;i++){
        for(int j=0;j<stud-1;j++){
            if(strcmp(student[j].name,student[j+1].name) > 0){
                struct member temp=student[j];
                student[j]=student[j+1];
                student[j+1]=temp;
            }
        }
    }
}

void borrows(void)
{
    sort_staff();
    sort_students();
    for(int i=4;i>=0;i++)
    {
        for(int j=0;j<fac;j++){
            if(staff[j].no_of_books==i){
                puts(staff[j].name);
            }
        }
        for(int j=0;j<stud;j++){
            if(student[j].no_of_books==i){
                puts(student[j].name);
            }
        }
    }
}

int main()
{
    while(1){
        printf("1.Insert a book\n2.New faculty\n3.New student\n4.Fine\n5.Personal Fine\n6.Borrows total\n");
        int command;
        scanf("%d",&command);
        if(command==1){
            insert_book();
        }
        if(command==2){
            new_fac();
        }
        if(command==3){
            new_stud();
        }
        if(command==4){
            print_max_book_people();
        }
        if(command==5){
            calc_fine();
        }
        if(command==6){
            borrows();
        }
    }
}
