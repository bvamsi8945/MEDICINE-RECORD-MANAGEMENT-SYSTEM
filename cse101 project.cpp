
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
void gotoxy(int ,int );
void menu();
void add();
void view();
void search();
void modify();
void deleterec();
struct medicine
{
char name[20];
char pr[10];
char mfd[20];
char exp[20];
char ds[20];
};
int main()
{
gotoxy(15,8);
printf("<--:Medicine Record Management System:-->");
gotoxy(19,15);
printf("Press any key to continue.");
getch();
menu();
return 0;
}
void menu()
{
int choice;
system("cls");
gotoxy(10,3);
printf("<--:MENU:-->");
gotoxy(10,5);
printf("Enter appropriate number to perform following task.");
gotoxy(10,7);
printf("1 : Add New medicine.");
gotoxy(10,8);
printf("2 : View Medicine Details.");
gotoxy(10,9);
printf("3 : Search Medicine.");
gotoxy(10,10);
printf("4 : Update Medicine Details.");
gotoxy(10,11);
printf("5 : Delete Medicine.");
gotoxy(10,12);
printf("6 : Exit.");
gotoxy(10,15);
printf("Enter your choice.");
scanf("%d",&choice);
switch(choice)
{
case 1:
add();
break;
case 2:
view();
break;
case 3:
search();
break;
case 4:
modify();
break;
case 5:
deleterec();
break;
case 6:
exit(1);
break;
default:
gotoxy(10,17);
printf("Invalid Choice.");
}
}
void add()
{
FILE *fp;
struct medicine std;
char another ='y';
system("cls");
fp = fopen("record.txt","ab+");
if(fp == NULL){
gotoxy(10,5);
printf("Error opening file");
exit(1);
}
fflush(stdin);
while(another == 'y')
{
gotoxy(10,3);
printf("<--:ADD RECORD:-->");
gotoxy(10,5);
printf("Enter details of Medicine.");
gotoxy(10,7);
printf("Enter Name : ");
gets(std.name);
gotoxy(10,8);
printf("Enter Prize : ");
gets(std.pr);
gotoxy(10,9);
printf("Enter MFD : ");
gets(std.mfd);
fflush(stdin);
gotoxy(10,10);
printf("Enter EXP Date : ");
gets(std.exp);
gotoxy(10,11);
printf("Enter Quantity : ");
gets(std.ds);
fwrite(&std,sizeof(std),1,fp);
gotoxy(10,15);
printf("Want to add of another record? Then press 'y' else 'n'.");
fflush(stdin);
another = getch();
system("cls");
fflush(stdin);
}
fclose(fp);
gotoxy(10,18);
printf("Press any key to continue.");
getch();
menu();
}
void view()
{
FILE *fp;
int i=1,j;
struct medicine std;
system("cls");
gotoxy(10,3);
printf("<--:VIEW RECORD:-->");
gotoxy(10,5);
printf("S.No Name of Medicine Prize MFD EXP Date Quantity");
gotoxy(10,6);
printf("--------------------------------------------------------------------");
fp = fopen("record.txt","rb+");
if(fp == NULL){
gotoxy(10,8);
printf("Error opening file.");
exit(1);
}
j=8;
while(fread(&std,sizeof(std),1,fp) == 1){
gotoxy(10,j);
printf("%-7d%-22s%-12s%-12s%-12s%-dnf12s",i,std.name,std.pr,std.mfd,std.exp,std.ds);
i++;
j++;
}
fclose(fp);
gotoxy(10,j+3);
printf("Press any key to continue.");
getch();
menu();
}
void search()
{
FILE *fp;
struct medicine std;
char stname[20];
system("cls");
gotoxy(10,3);
printf("<--:SEARCH MEDICINE:-->");
gotoxy(10,5);
printf("Enter name of Medicine : ");
fflush(stdin);
gets(stname);
fp = fopen("record.txt","rb+");
if(fp == NULL){
gotoxy(10,6);
printf("Error opening file");
exit(1);
}
while(fread(&std,sizeof(std),1,fp ) == 1){
if(strcmp(stname,std.name) == 0){
gotoxy(10,8);
printf("Name : %s",std.name);
gotoxy(10,9);
printf("Medicine Prize : %s",std.pr);
gotoxy(10,10);
printf("MFD : %s",std.mfd);
gotoxy(10,11);
printf("EXP Date : %s",std.exp);
gotoxy(10,12);
printf("Quantity : %s",std.ds);
}
}
fclose(fp);
gotoxy(10,16);
printf("Press any key to continue.");
getch();
menu();
}
void modify()
{
char stname[20];
FILE *fp;
struct medicine std;
system("cls");
gotoxy(10,3);
printf("<--:UPDATE RECORD:-->");
gotoxy(10,5);
printf("Enter name of medicine to update: ");
fflush(stdin);
gets(stname);
fp = fopen("record.txt","rb+");
if(fp == NULL){
gotoxy(10,6);
printf("Error opening file");
exit(1);
}
rewind(fp);
fflush(stdin);
while(fread(&std,sizeof(std),1,fp) == 1)
{
if(strcmp(stname,std.name) == 0){
gotoxy(10,7);
printf("Enter name: ");
gets(std.name);
gotoxy(10,8);
printf("Enter Prize : ");
gets(std.pr);
gotoxy(10,9);
printf("Enter MFD : ");
gets(std.mfd);
gotoxy(10,10);
printf("Enter EXP Date : ");
fflush(stdin);
gets(std.exp);
gotoxy(10,11);
printf("Enter Quantity : ");
fflush(stdin);
gets(std.ds);
fseek(fp ,-sizeof(std),SEEK_CUR);
fwrite(&std,sizeof(std),1,fp);
break;
}
}
fclose(fp);
gotoxy(10,16);
printf("Press any key to continue.");
getch();
menu();
}
void deleterec()
{
char stname[20];
FILE *fp,*ft;
struct medicine std;
system("cls");
gotoxy(10,3);
printf("<--:DELETE RECORD:-->");
gotoxy(10,5);
printf("Enter name of medicine to delete record : ");
fflush(stdin);
gets(stname);
fp = fopen("record.txt","rb+");
if(fp == NULL){
gotoxy(10,6);
printf("Error opening file");
exit(1);
}
ft = fopen("temp.txt","wb+");
if(ft == NULL){
gotoxy(10,6);
printf("Error opening file");
exit(1);
}
while(fread(&std,sizeof(std),1,fp) == 1){
if(strcmp(stname,std.name)!=0)
fwrite(&std,sizeof(std),1,ft);
}
fclose(fp);
fclose(ft);
remove("record.txt");
rename("temp.txt","record.txt");
gotoxy(10,10);
printf("Press any key to continue.");
getch();
menu();
}
void gotoxy(int x,int y)
{
COORD c;
c.X=x;
c.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

