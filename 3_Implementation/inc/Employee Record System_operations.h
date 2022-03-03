/**
 * @file Employee Record System_operations.h
 * @author Karthikeyan
 * @brief Header file for Employee Record System application with Arithmetic operations
 *
 */

#ifndef __Employee Record System_OPERATIONS_H__
#define __Employee Record System_OPERATIONS_H__

#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>  

COORD coord = {0,0}; 
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// main function

int main()
{
    FILE *fp, *ft; 
    char another, choice;
    struct emp
    {
        char name[40]; 
        int age; 
        float bs; 
    };

    struct emp e; 

    char empname[40]; 

    long int recsize; 
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    recsize = sizeof(e);
	
    while(1)
    {
        system("cls"); 
        gotoxy(30,10); 
        printf("1. Add Record"); 
        gotoxy(30,12);
        printf("2. List Records"); 
        gotoxy(30,14);
        printf("3. Modify Records"); 
        gotoxy(30,16);
        printf("4. Delete Records"); 
        gotoxy(30,18);
        printf("5. Exit"); 
        gotoxy(30,20);
        printf("Your Choice: "); 
        fflush(stdin); 
        choice  = getche(); 
	 
	    //switch function
	    
        switch(choice)
        {
	     // add the record
			
         case '1':  
            system("cls");
            fseek(fp,0,SEEK_END); 
              another = 'y';
            while(another == 'y')  
            {
                printf("\nEnter name: ");
                scanf("%s",e.name);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                printf("\nEnter basic salary: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); 
                printf("\nAdd another record(yes/no) ");
                fflush(stdin);
                another = getche();
            }
            break;
			
 case '2':
	      //list the record 
			
             system("cls");
            rewind(fp); 
            while(fread(&e,recsize,1,fp)==1)  
            {
                printf("\n%s %d %.2f",e.name,e.age,e.bs); 
            }
            getch();
            break;

  case '3':  
		//modify the record
			
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the employee name to modify: ");
                scanf("%s", empname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1) 
                {
                    if(strcmp(e.name,empname) == 0)  
                    {
                        printf("\nEnter new name,age and bs: ");
                        scanf("%s%d%f",e.name,&e.age,&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); 
                        fwrite(&e,recsize,1,fp); 
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
			
 case '4':
			//delete the record
			
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of employee to delete: ");
                scanf("%s",empname);
                ft = fopen("Temp.dat","wb");  
                rewind(fp); 
                while(fread(&e,recsize,1,fp) == 1)  
                {
                    if(strcmp(e.name,empname) != 0)  
                    {
                       fwrite(&e,recsize,1,ft); 
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); 
                rename("Temp.dat","EMP.DAT"); 
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                another = getche();
            }
            break;
			
 case '5':
            fclose(fp);  
            exit(0); 
        }
    }
    return 0;
}



#endif  /* #define __Employee Record System_OPERATIONS_H__ */