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
	representations.d = value;
	unsigned long EXP=(representations.i & 0x7FF0000000000000)>>52;
	//EXP-1023 because thats half of the bits reserved for exp
	unsigned long FRAC=(representations.i & 0xFFFFFFFFFFFFF);

	int i;
	unsigned long leftBit = 1;
	//finds furthes left value 
	for(i = 0; i < (*def).totBits -1; i++){
		leftBit*=2;
	}
	

	unsigned long oneBitDouble = 0x8000000000000000;
	bool sign = (representations.i&oneBitDouble);
	//zero out ret(return value)
	floatx ret = 0;
	//assign sign bit
	if(sign)ret +=leftBit;
	//assigning exp bits
	unsigned long bitMaskExp =1;
	//Since the math library requires changing the makefile, I used a for loop instead of pow()
	for(i=0; i< (*def).expBits; i++){
		bitMaskExp*=2;
	}
	bitMaskExp/=2;
	bitMaskExp--;
	int exp;
	int temp = EXP -1023;
	bool tooBig = false;
	bool deNormalized = false;
	if(EXP>=1023){
		if(temp > bitMaskExp){
			exp = 0;
			bitMaskExp*=2;
			bitMaskExp++;
			tooBig = true;
		} 
		else exp = EXP -1023;
	}
	else{
		if(-1*temp >= bitMaskExp){
			exp = 0;
			bitMaskExp = 0;
			deNormalized = true;
		} 
	} 
	bitMaskExp+=exp;
	ret = ret|(bitMaskExp<<((*def).totBits-(*def).expBits-1));
	//if the number was too large to hold in the exponent it does not assign the fraction part
	if(tooBig) return ret;
	//assigns fraction bits
	ret = ret|(FRAC>>(52-((*def).totBits-(*def).expBits-1)));
	//adds one if needs to be rounded
	if(1&FRAC>>(52-((*def).totBits-(*def).expBits))) ret++;
	//convert from denormalized number
	if(deNormalized){
		ret = ret>>1;
		if((ret >> ((*def).totBits-2) & 1)){
			ret &= ~(1 << ((*def).totBits-2));
			ret |= (1 << ((*def).totBits-1));
		}

		ret = ret|(1<<((*def).totBits-(*def).expBits-2));
	}

    return ret;
}

/** Return C double with value which best approximates that of floatx fx
 *  (as defined by *def).
 */
double floatxToDouble(const floatxDef *def, floatx fx) {
	/* Put your code here */
	return NAN;
}