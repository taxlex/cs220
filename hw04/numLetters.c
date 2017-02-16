#include <stdio.h>
#include <stdlib.h>
int wholeNum(int);
int threeDigitConverter(int);
int twoDigitConverter(int);
int oneDigitConverter(int);
int main(int argc, char ** argv){
	if(argc<=1 || argc>2){
		printf("One number pls\n");
		exit(1);
	}
	int num;
	int numlet;
	num = atoi(argv[1]);
	if(num > 1000000000){
		printf("number larger the 1,000,000,000\n");
		exit(1);
	}
	if(num < 0){
		printf("number smaller than 0\n");
		exit(1);
	}
	numlet = wholeNum(num);
	printf("%d takes %d letters\n", num, numlet);
	return 0;
}
int wholeNum(int in){
	int letterCount = 0;
	int temp;
	if(in == 1000000000) return 10;//one billion
	if(in == 0) return 4;//zero 
	//million converter
	temp = in/1000000;
	if(temp > 0){
		letterCount += 7 +threeDigitConverter(temp);//7 for "million"
		in -= temp*1000000;
	}
	//thousand converter
	temp = in/1000;
	if(temp > 0){
		letterCount += 8 + threeDigitConverter(temp);//8 for "thousand"
		in -= temp*1000;
	}
	//hundred converter
	return letterCount + threeDigitConverter(in);
}
int threeDigitConverter(int in){
	int letterCount = 0;
	int temp = in/100;
	if(temp > 0){
		letterCount += 7 + oneDigitConverter(temp);//7 is for "hundred"
		in -= temp*100;
	}
	temp = in/10;
	//deals with the "tens"
	if(temp == 1){
		if(in == 10) return letterCount + 3;//ten
		else if(in == 11) return letterCount + 6;//eleven
		else if(in == 12) return letterCount + 6;//twelve
		else if(in == 13) return letterCount + 8;//thirteen
		else if(in == 14) return letterCount + 8;//fourteen
		else if(in == 15) return letterCount + 7;//fifteen
		else if(in == 16) return letterCount + 7;//sixteen
		else if(in == 17) return letterCount + 9;//seventeen
		else if(in == 18) return letterCount + 8;//eighteen
		else if(in == 19) return letterCount + 8;//nineteen
	}
	else if(temp > 0){
		letterCount += twoDigitConverter(temp);
		in -= temp*10;
	}
	return letterCount += oneDigitConverter(in);
	
}
int twoDigitConverter(int in){
	if(in == 2) return 6;//twenty
	else if(in == 3) return 6;//thirty
	else if(in == 4) return 5;//forty
	else if(in == 5) return 5;//fifty
	else if(in == 6) return 5;//sixty
	else if(in == 7) return 7;//seventy
	else if(in == 8) return 6;//eighty
	else if(in == 9) return 6;//ninety
	return 0;
}
int oneDigitConverter(int in){
	if(in == 0) return 0;
	else if(in == 1) return 3;//one
	else if(in == 2) return 3;//two
	else if(in == 3) return 5;//three
	else if(in == 4) return 4;//four
	else if(in == 5) return 4;//five
	else if(in == 6) return 3;//six
	else if(in == 7) return 5;//seven
	else if(in == 8) return 5;//eight
	else if(in == 9) return 4;//nine
	return 0;
}
