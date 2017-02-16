#include <stdio.h>
#include <string.h>

#define MAXSTUDENTS 20
#define NAMELEN 12
#define NUMGRADES 9

char name[NAMELEN];
int getName();
int getGrade();
void printHeader();
void printSep();

/* Your main function goes here */
int main(int argc, char* argv[]){
	int i;
	int y;
	char nameArray[MAXSTUDENTS][NAMELEN];
	int gradeArray[MAXSTUDENTS][NUMGRADES];
	int numRowsUsing = 0;
	while(getName() == 1){
		for(i =0; i< NAMELEN; i++){
			nameArray[numRowsUsing][i] = name[i];
		}
		for(i = 0; i < NUMGRADES; i++){
			gradeArray[numRowsUsing][i] = getGrade();
		}
		numRowsUsing++;
		
	}
	printHeader();
	float avg;
	float minAvg = 100.0;
	float maxAvg = 0.0;
	int minSt = 0;
	int maxSt = 0;
	for(i = 0; i < numRowsUsing; i++){
		avg = 0;
		printf("%*s |",NAMELEN,nameArray[i]);
		for(y = 0; y < NUMGRADES; y++){
			avg += gradeArray[i][y];
			printf(" %3d |",gradeArray[i][y]);
		}
		avg /= NUMGRADES;
		printf(" %6.2f |\n",avg);
		if(avg > maxAvg){
			maxAvg = avg;
			maxSt = i;
		}
		else if(avg < minAvg){
			minAvg = avg;
			minSt = i;
		}
	}
	printSep();
	printf("Minimum avg=%6.2f earned by %s\n",minAvg,nameArray[minSt]);
	printSep();
	printf("Maximum avg=%6.2f earned by %s\n",maxAvg,nameArray[maxSt]);
	printSep();
	
	
	return 0;
}

int getName() {
	/* --------------------------------------------------------------------------------------------------
		Reads the next name from stdin, and saves it in the "name" global array
		Returns a 1 if name has been updated, or 0 if there was a problem.
	-----------------------------------------------------------------------------------------------------*/
	if (1==scanf("%s ",name)) return 1;
	return 0;
}

int getGrade() {
	/* --------------------------------------------------------------------------------------------------
		Reads the next grade from stdin,
		Returns the grade if succesful, or -1 if there was a problem.
	-----------------------------------------------------------------------------------------------------*/
	int grade;
	if (1==scanf("%d ",&grade)) return grade;
	return -1;
}

void printHeader() {
	printf("%*s | %3s | %3s | %3s | %3s | %3s | %3s | %3s | %3s | %3s | %6s |\n",
		NAMELEN,"Name","HW1","HW2","HW3","LB1","LB2","LB3","TS1","TS2","TS3","Avg");
	printSep();
}

void printSep() {
	/* Print a separator row */
	int i;
	for(i=0;i<NAMELEN; i++) putchar('-');
	printf("-+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------+\n");
}
