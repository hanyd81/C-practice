#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "type.h"
//#define DEBUG

void clear(void)
{
	while (getchar() != '\n')
		;
}
float getscore(char *str)
{
	float tempScore;
	int sr, keepInput = 1;
	while (keepInput) {
		printf("Enter Student's %s score :", str);
		sr = scanf("%f", &tempScore);
		if (sr == 0) {
			printf("Invalid input, Score must be a number \n");
			clear();
		}
		else if (tempScore > 100 || tempScore < 0) {
			printf("Invalid number, score must between 0-100 \n");
			clear();
		}
		else keepInput = 0;
	}
	return tempScore;


}
long getID()
{
	long id;
	int sr, flag = 1;

	while (flag) {
		printf("Enter Student ID:");
		sr = scanf("%ld", &id);
		if (id == 0) {
			clear();
			return 0;
		}
		if (sr == 0) {
			printf("Invalid input, student ID must be %d digit number, or enter 0 to exit \n", IDDIGIT);
			clear();
		}
		else if (id >= (long)pow(10, IDDIGIT) || id < (long)pow(10, IDDIGIT - 1)) {
			printf("Invalid number, student ID must be %d digit number or enter 0 to exit\n", IDDIGIT);
			clear();
		}
		else flag = 0;
	}
	clear();
	return id;
}

char getGender()
{
	int flag = 1;
	char g;
	while (flag) {
		printf("Enter Student's gender:");
		scanf("%c", &g);
		g = toupper(g);
		if (g == 'M' || g == 'F' || g == 'N')
			flag = 0;
		else {
			printf("Invalid input, gender must be M(male),F(female) or N(not known) \n");
			clear();
		}
	}
	clear();
	return g;
}
void getName(char *name)
{
	int i;
	char temp[NAMELEN];
	printf("Enter Student name:");
	scanf("%[^\n]%*c", temp);
	for (i = 0; i <(int) strlen(temp); i++) {
		if (i == 0)
			temp[i] = toupper(temp[i]);
		if (temp[i - 1] == ' ')
			temp[i] = toupper(temp[i]);
	}
	strcpy(name, temp);
}

int idSearch(const STU *Students, int len, long id)
{
	int i;
	for (i = 0; i < len; i++)
	{
		if (Students[i].id == id)
			return i;
	}
	return -1;
}

void nameSearch(const STU *Students, int len)
{
	int i, j, k, flag = 0, slen, count = 0;
	char sname[NAMELEN];
	STU student;
	printf("Enter Student name:");
	scanf("%s", sname);
	clear();
	sname[0] = toupper(sname[0]);
	for (i = 0; sname[i] != '\0'; i++);
	slen = i;
	infoTitle();
	//iterate each student 
	for (i = 0; i < len; i++) {
		student = Students[i];
		flag = 0;
		for (j = 0; j < NAMELEN; j++) {
			if (j == 0) {
				for (k = 0; sname[k] != '\0'&& flag == 0; k++) {
					if (student.name[j] != sname[k])
						flag = 1;
					else j++;
				}
				if (k == slen && flag == 0) {
					stuInfo(student);
					count++;
					break;
				}
			}
			else if (student.name[j - 1] == ' ') {
				flag = 0;
				for (k = 0; sname[k] != '\0'&& flag == 0; k++) {
					if (student.name[j] != sname[k])
						flag = 1;
					else  j++;
				}
				if (k == slen && flag==0) {
					stuInfo(student);
					count++;
					break;
				}
			}
		}
	}
	if (count == 0)
		printf("No match names! \n");
	else {
		printf("                                     ------------------------------\n");
		printf("                                               %d maches found \n", count);
	}
}

void del(STU *Students, int len, int j)
{
	int i;
	for (i = j; i < len - 1; i++) {
		Students[i] = Students[i + 1];
	}
	return;
}

STU addInfo(STU *Students, int len)
{
	STU student = { 0 };
	long id;
	int flag = 1, i;

	//get ID 
	do {
		id = getID();
		if (id == 0)
			return student;
		i = idSearch(Students, len, id);
		if (i == -1) {
			student.id = id;
			flag = 0;
		}
		else {
			printf("Student's ID already exist!\n");
			infoTitle();
			stuInfo(Students[i]);
			printf("\n");
		}
	} while (flag);

	getName(student.name);
	student.gender = getGender();
	student.CPR = getscore("CPR");
	student.IPC = getscore("IPC");
	student.ULI = getscore("ULI");

	//printf("student Information input is:\n");
	//infoTitle();
	//stuInfo(student);
	//printf("Do you want to add ?\n");
	return student;
}


int readInfo(FILE *fp, STU *Students, int len)
{
	STU student;
	int sr = 0, i, mark;
	char c;
	mark = feof(fp);
	//read infomation from file and put into array
	for (i = 0; i < len; i++) {
		do {
			sr = fscanf(fp, "%d;%[^;];%c;%f;%f;%f\n", &student.id, student.name, &student.gender, &student.CPR, &student.IPC, &student.ULI);
			//printf("scanf read %d fileds\n", sr);
			//get rid of wrong info
			if (sr != 6)
				while ((c = fgetc(fp)) != '\n'&& c != EOF)
					;
		} while (sr != 6);
		Students[i] = student;

#ifdef DEBUG
		//printf("scanf read %d fileds\n", sr);
		stuInfo(Students[i]);
#endif
		if (feof(fp) > mark)
			break;
	}
	rewind(fp);
	return i + 1;
}

int countStu(FILE *fp)
{
	int count = 0, c;
	do {
		c = fgetc(fp);
		if (c == EOF)
			break;
		if (c == '\n')
			count++;
	} while (feof(fp) == 0);
	rewind(fp);

#ifdef DEBUG
	printf("count %d records\n", count);
	system("pause");
#endif
	return count;
}


void display(const STU *Students, int len)
{
	int i, uli = 0, ipc = 0, cpr = 0;
	float tULI = 0, tIPC = 0, tCPR = 0;

	infoTitle();
	for (i = 0; i < len; i++) {
		stuInfo(Students[i]);
		if (Students[i].CPR > 0) {
			tCPR += Students[i].CPR;
			cpr++;
		}
		if (Students[i].ULI > 0) {
			tULI += Students[i].ULI;
			uli++;
		}
		if (Students[i].IPC > 0) {
			tIPC += Students[i].IPC;
			ipc++;
		}

	}
	printf("                         -----------------------------------------\n");
	printf("                             Average:     %5.2f    %5.2f    %5.2f \n", tCPR / cpr, tIPC / ipc, tULI / uli);
	getchar();

}

int change(STU *Students, int len)
{
	long id;
	int i;
	//get id and search for student
	id = getID();
	if (id == 0)
		return 0;
	i = idSearch(Students, len, id);
	if (i == -1) {
		printf("Can not find student ID %ld \n", id);
		return 0;
	}
	infoTitle();
	stuInfo(Students[i]);

	//change info
	Students[i].id = getID();
	getName(Students[i].name);
	Students[i].gender = getGender();
	Students[i].CPR = getscore("CPR");
	Students[i].IPC = getscore("IPC");
	Students[i].ULI = getscore("ULI");

	return 1;
}

int dele(STU *Students, int len)
{
	int i;
	long id;
	char option;
	id = getID();
	if (id == 0)
		return 0;
	i = idSearch(Students, len, id);
	if (i == -1) {
		printf("Can not find student ID %ld \n", id);
		return 0;
	}
	infoTitle();
	stuInfo(Students[i]);
	printf("\nDo you want to delete this information (Y/N) ?\n");
	while (1) {
		option = getchar();
		clear();
		switch (option)
		{
		case 'y':
		case 'Y':
			del(Students, len, i);
			printf("infomation deleted successfully! \n");
			return 1;
		case 'n':
		case 'N':
			return 0;
		default:
			printf("Please enter Y or N :\n");

		}
	}
}

void infoSearch(const STU *Students, int len)
{
	char option;
	int i, id;
	while (1) {

		option = searchMenu();
		switch (option)
		{
		case '1':
			id = getID();
			i = idSearch(Students, len, id);
			if (i == -1)
				printf("Can not find student ID %ld \n", id);
			else {
				infoTitle();
				stuInfo(Students[i]);
			}
			getchar();
			break;

		case '2':
			nameSearch(Students, len); getchar();
			break;

		case '0':
			return;

		default:
			printf("Please enter a valid number\n");
			getchar();
			break;
		}
	}
}
