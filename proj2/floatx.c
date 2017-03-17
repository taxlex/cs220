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
	int exp;
	int temp = EXP -1023;
	if(EXP>=1023){
		if(temp > bitMaskExp){
			exp = 0;
			bitMaskExp*=2;
		} 
		else exp = EXP -1023;
	}
	else{
		if(-1*temp > bitMaskExp){
			exp = 0;
			bitMaskExp = 0;
		} 
		exp = temp;
	} 
	bitMaskExp+=exp;
	ret = ret|(bitMaskExp<<((*def).totBits-(*def).expBits-1));
	//assigning fractionbits
	ret = ret|(FRAC>>(52-((*def).totBits-(*def).expBits-1)));
	if(1&FRAC>>(52-((*def).totBits-(*def).expBits))) ret++;
	printf("Ret is %x , Frac is %x Exp is %x \n",ret,(FRAC>>(52-((*def).totBits-(*def).expBits-1))),bitMaskExp );

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