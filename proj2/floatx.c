#include "floatx.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

/*--------------------------------------------------------------------------------
	Return floatx representation (as defined by *def) which
	best approximates value
-------------------------------------------------------------------------------- */

floatx doubleToFloatx(const floatxDef *def, double value) {
    union {
		double d;
		unsigned long i;
		unsigned char c[8];
	} representations;
	printf("\n\n");
	representations.d = value;
	bool sign = (representations.i&0x8000000000000000);
	printf("Sign: %d \n",sign);
	unsigned long EXP=(representations.i & 0x7FF0000000000000)>>52;
	//EXP-1023 because thats half of the bits reserved for exp
	printf("Exponent: %lu \n", (EXP-1023));
	unsigned long FRAC=(representations.i & 0xFFFFFFFFFFFFF);
	printf("Fraction: %lu \n", FRAC);
	bool twoFrac = (representations.i & 0x8000000000000);
	printf("1/2: %d \n", twoFrac);
	bool fourFrac= (representations.i & 0x4000000000000);
	printf("1/4: %d \n", fourFrac);
    return 0;

	/* Put your code here */
}

/** Return C double with value which best approximates that of floatx fx
 *  (as defined by *def).
 */
double floatxToDouble(const floatxDef *def, floatx fx) {
	/* Put your code here */
	return NAN;
}