#include <stdio.h>
#define DATAFILE "studentInfo.txt"
#define NAMELEN 20
#define IDDIGIT 5


//structure of student information
typedef struct Student {
	long id;
	char name[NAMELEN];
	char gender;
	float CPR;
	float IPC;
	float ULI;
}STU;

STU addInfo(STU *Students, int len);

//display function
void infoTitle();
void stuInfo(STU student);
char showMainMenu(int noStu);
char searchMenu();

//tool function
void clear(void);
int countStu(FILE *fp);
int readInfo(FILE *fp, STU *Students, int len);
int idSearch(const STU *Students, int len, long id);
void nameSearch(const STU *Students, int len);


//menu function
int change(STU *Students, int len);
void display(const STU *Students, int len);
STU addInfo(STU *Students, int len);
int dele(STU *Students, int len);
void infoSearch(const STU *Students, int len);
