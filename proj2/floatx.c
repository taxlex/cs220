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
	unsigned long EXP=(representations.i & 0x7FF0000000000000)>>52;
	//EXP-1023 because thats half of the bits reserved for exp
	printf("Exponent: %lu \n", (EXP));
	unsigned long FRAC=(representations.i & 0xFFFFFFFFFFFFF);
	printf("Fraction: %lu \n", FRAC);
	bool twoFrac = (representations.i & 0x8000000000000);
	printf("1/2: %d \n", twoFrac);
	bool fourFrac= (representations.i & 0x4000000000000);
	printf("1/4: %d \n", fourFrac);

	int i;
	unsigned long leftBit = 1;
	//finds furthes left value 
	for(i = 0; i < (*def).totBits -1; i++){
		leftBit*=2;
	}

	printf("totBits: %d \n",(*def).totBits);
	printf("left bit %lu \n",leftBit);
	

	unsigned long oneBitDouble = 0x8000000000000000;
	bool sign = (representations.i&oneBitDouble);
	printf("Sign: %d \n",sign);
	//zero out ret(return value)
	floatx ret = 0;
	//assign sign bit
	if(sign)ret +=leftBit;
	//assigning exp bits
	unsigned long bitMaskExp =1;
	for(i=0; i< (*def).expBits; i++){
		bitMaskExp*=2;
	}
	bitMaskExp/=2;
	bitMaskExp--;
	unsigned long exp;
	if(EXP>=1023) exp = EXP -1023;
	else exp = 1023-EXP;
	bitMaskExp+=exp;
	ret = ret|(bitMaskExp<<((*def).totBits-(*def).expBits-1));
	//assigning fractionbits
	ret = ret|(FRAC>>(52-((*def).totBits-(*def).expBits-1)));


    return ret;

	/* Put your code here */
}

/** Return C double with value which best approximates that of floatx fx
 *  (as defined by *def).
 */
double floatxToDouble(const floatxDef *def, floatx fx) {
	/* Put your code here */
	return NAN;
}