#ifndef _FUNCTIONS_MATRIXSONGS_
#define _FUNCTIONS_MATRIXSONGS_

typedef struct {
	char name[30];
	int size;
	bool notes[900][3];
}MUSIC;

void copy(char a[], char b[]);
void copyVector(int size, bool a[size][3], bool b[size][3]);
void printVector(int size, bool a[size][3]);
int countNotes(int size, bool musica[size][3]);
int sizeString(char texto[]);
void breakString(char texto[], char string1[], char string2[]);
MUSIC GetMusic(int number);


#endif //_FUNCTIONS_MATRIXSONGS_