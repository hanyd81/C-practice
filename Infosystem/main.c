#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include "type.h"
//#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG
//#define DATAFILE "studentInfo.txt"


char showMainMenu(int noStu);
char searchMenu();

void main()
{
	STU student;

	//open student information file
	FILE *fp = NULL;
	fp = fopen(DATAFILE, "a+");
	if (fp == NULL) {
		printf("Failed to open data file\n");
		system("pause");
		exit(1);
	}
	// set an array of STU to hold data
	int re, noStu, infoRead;
	noStu = countStu(fp);
	STU *Students = malloc(noStu * sizeof(STU));
	infoRead = readInfo(fp, Students, noStu);
	noStu = infoRead; //update student No.

	// mainmenu choice
	char choice;
	int i;
	while (1) {
		re = 0;
		choice = showMainMenu(noStu);
		switch (choice)
		{
		case '1':
			infoSearch(Students, noStu);
			break;

		case '2':
			printf("Add student information:\n");
			student = addInfo(Students, noStu);
			if (student.id == 0)
				break;
			//add infomation to STU array
			STU *TempStu = realloc(Students, (noStu + 1) * sizeof(STU));
			if (TempStu != NULL) {
				TempStu[noStu] = student;
				Students = TempStu;
				noStu++; //update student No.
				printf("Student information added succesfully\n");
				clear();
			}
			else
				printf("Failed to add information\n");
			getchar();
			break;

		case '3':
			re=dele(Students, noStu);
			noStu -= re;
			getchar();
			break;

		case '4':
			re = change(Students, noStu);
			if (re == 1)
				printf("Student Information changed successfully! \n"); 
			getchar();
			break;

		case '5':
			display(Students, noStu);
			break;

		case '0':
			fclose(fp);
			//rewrite file with updated data
			fp = fopen(DATAFILE, "w");
			if (fp == NULL) {
				printf("Failed to write data file\n");
				getchar();
				exit(1);
			}
			for (i = 0; i < noStu; i++) {
				fprintf(fp, "%d;%s;%c;%f;%f;%f\n", Students[i].id, Students[i].name, Students[i].gender, Students[i].CPR, Students[i].IPC, Students[i].ULI);
			}
			fclose(fp);
			free(Students);
			return;
			//exit(0);
		default:
			printf("Please enter a valid number\n");
			getchar();
			break;
		}
		//clear();
	}


}

char showMainMenu(int noStu)
{
	char choice;
	system("clear");
	printf("*--------------Welcome to Student Information System---------------*\n");
	printf("*                    Total %4d students                           *\n", noStu);
	printf("*          --------------------------------------                  *\n");
	printf("*              1. Check student information                        *\n");
	printf("*              2. Add student information                          *\n");
	printf("*              3. Delete student information                       *\n");
	printf("*              4. Change student information                       *\n");
	printf("*              5. Show all student information                     *\n");
	printf("*              0. Exit                                             *\n");
	printf("*------------------------------------------------------------------*\n");
	//choice = _getche();
	scanf("%c", &choice);
	clear();
#ifdef DEBUG
	printf("choice=%c\n", choice);
	getchar();
#endif
	return choice;
}
char searchMenu()
{
	char option;
	system("clear");
	printf("*-----------------check student information------------------------*\n");
	printf("*                        1. Search ID                              *\n");
	printf("*                        2. Search name                            *\n");
	printf("*                        0. Exit                                   *\n");
	printf("*------------------------------------------------------------------*\n");
	option = getchar();
	clear();
	return option;
}

void infoTitle()
{
	printf("  ID       Name                 Gender     CPR      IPC      ULI   \n");

}
void stuInfo(STU student)
{
	printf("%-8d   %-20s %2c %12.2f %8.2f %8.2f\n", student.id, student.name, student.gender, student.CPR, student.IPC, student.ULI);
}
