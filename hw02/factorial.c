#include <stdio.h>
#include <math.h>

char fact_char(char n);
short fact_short(short n);
int fact_int(int n);
long fact_long(long n);
float fact_float(float n);
double fact_double(double n);

int main(int argc, char **argv) {

	char i_char;
	for(i_char=1; ; i_char++) {
		char r_char;
		r_char = fact_char(i_char);
		if (i_char >=2 && 0 != r_char%2 ) break;
		if (i_char >=5 && 0 != r_char%10) break;
		printf("%d! = %d\n",i_char,r_char);
	}
	printf("%d! does not fit in a char variable\n",i_char);
	
	short i_short;
	for(i_short=1; ; i_short++) {
		short r_short;
		r_short = fact_short(i_short);
		if (i_short >=2 && 0 != r_short%2 ) break;
		if (i_short >=5 && 0 != r_short%10) break;
		printf("%d! = %d\n",i_short,r_short);
	}
	printf("%d! does not fit in a short variable\n",i_char);
	
	int i_int;
	for(i_int=1; ; i_int++) {
		int r_int;
		r_int = fact_int(i_int);
		if (i_int >=2 && 0 != r_int%2 ) break;
		if (i_int >=5 && 0 != r_int%10) break;
		printf("%d! = %d\n",i_int,r_int);
	}
	printf("%d! does not fit in a int variable\n",i_int);
	
	long i_long;
	for(i_long=1; ; i_long++) {
		long r_long;
		r_long = fact_long(i_long);
		if (i_long >=2 && 0 != r_long%2 ) break;
		if (i_long >=5 && 0 != r_long%10) break;
		printf("%ld! = %ld\n",i_long,r_long);
	}
	printf("%ld! does not fit in a long variable\n",i_long);
	
	float i_float;
	for(i_float=1; ; i_float++) {
		float r_float;
		r_float = fact_float(i_float);
		if (r_float == INFINITY) break;
		printf("%f! = %g\n",i_float,r_float);//%g is for scientific notation
	}
	printf("%f! does not fit in a float variable\n",i_float);
	
	double i_double;
	for(i_double=1; ; i_double++) {
		double r_double;
		r_double = fact_double(i_double);
		if (r_double == INFINITY) break;
		printf("%f! = %g\n",i_double,r_double);//%g is for scientific notation
	}
	printf("%f! does not fit in a double variable\n",i_double);

	return 0;
}

char fact_char(char n) {
	if (n<3) return n;
	return n*fact_char(n-1);
}
short fact_short(short n) {
	if (n<3) return n;
	return n*fact_short(n-1);
}
int fact_int(int n) {
	if (n<3) return n;
	return n*fact_int(n-1);
}
long fact_long(long n) {
	if (n<3) return n;
	return n*fact_long(n-1);
}
float fact_float(float n) {
	if (n<3) return n;
	return n*fact_float(n-1);
}
double fact_double(double n) {
	if (n<3) return n;
	return n*fact_double(n-1);
}
