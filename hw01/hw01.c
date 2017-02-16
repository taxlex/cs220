#include <stdio.h>
#include <string.h>

int fib(int n);
int diffSq(int a, int b);

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("Please invoke as %s <input-ID>\n",argv[0]);
		printf("  %s will then open a file called <input-ID>.txt,\n",argv[0]);
		printf("  perform the requested operations, and write the results to\n");
		printf("  a file called <input-ID>_results.txt\n");
		return 1;
	}

	char inFileName[100] = {'\0'};
	strcat(inFileName,argv[1]);
	strcat(inFileName,".txt");
	char outFileName[100]={'\0'};
	strcat(outFileName,argv[1]);
	strcat(outFileName,"_results.txt");

	FILE *inFile=NULL;
	inFile=fopen(inFileName,"r");
	if (inFile==NULL) {
		printf("Unable to open input file %s... quitting.\n",inFileName);
		return 1;
	}

	FILE *outFile=NULL;
	outFile=fopen(outFileName,"w");
	if (outFile==NULL) {
		printf("Unable to open output file %s... quitting.\n",outFileName);
		fclose(inFile);
		return 1;
	}

	int a;
	int b;
	int result;
	while(!feof(inFile)) {
		if (1==fscanf(inFile," fib %d ",&a)) {
			result=fib(a);
			fprintf(outFile,"fib(%d) = %d\n",a,result);
		}
		else if (2==fscanf(inFile," diffSq %d %d ",&a,&b)) {
			result = diffSq(a,b);
			fprintf(outFile,"diffSq(%d,%d) = %d\n",a,b,result);
		} else {
			char unrecognized[256];
			fscanf(inFile," %256s",unrecognized);
			printf("The following word from the input file is not recognized: %s\n",unrecognized);
		}
	}
	fclose(inFile);
	fclose(outFile);
	return 0;
}

int fib(int n) {
	/*------------------------------------------------------------------------------
	46 is the largest number who's fibonacci sequence can be held in an int
	--------------------------------------------------------------------------------*/
	if(n==0) return 0;
	if(n<47 && n>0){
		int higher = 1;
		int lower = 0;
		for(n=n; n > 1; n--){
			int temp = lower;
			lower = higher;
			higher += temp;
		}
		return higher;
	}
	else{
		printf("Too large or small of a number to be held in an int: fib()");
		return -1;
	}
}

int diffSq(int a, int b) {
	/* -------------------------------------------------------------------------------
	46341 is the largest number whose square can be held in an int
	----------------------------------------------------------------------------------*/
	if(a > -46341 && a < 46341 && b > -46341 && b < 46341){
		return a*a - b*b;
	}
	else{
		printf("Too large or small of a number to be held in an int: diffSq()");
		return -1;
	}
	
}
