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
	//bool zero to handle the zero case
	bool zero = false;
	if(value == 0) zero = true;
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
	//convert to denormalized number
	if(deNormalized){
		ret = ret>>1;
		if(sign){
			ret &= ~(1L << ((*def).totBits-2));
			ret |= (1L << ((*def).totBits-1));
		}

		ret = ret|(1<<((*def).totBits-(*def).expBits-2));
	}
	//if the input was zero it assigns 0 to ret because +0 = -0
	if(zero){
		ret = 0;
	}

    return ret;
}

/** Return C double with value which best approximates that of floatx fx
 *  (as defined by *def).
 */
double floatxToDouble(const floatxDef *def, floatx fx) {
	union {
		double d;
		unsigned long i;
	} representations;
	representations.i = 0;
	int i;

	bool zero = false;
	if(fx == 0) zero = true;
	//section is to account for denormalized numbers, checks to see if the exponent bits are all off
	unsigned long denorm = 1;
	for(i = 0; i < (*def).totBits - (*def).expBits -1; i++){
		denorm *=2;
	}
	unsigned long tempDenorm = fx;
	//bool to check if fx is positive to add the bit back after it is shifted left
	bool denormPos = tempDenorm&(1<<((*def).totBits -1));
	tempDenorm &= ~(1<<((*def).totBits-1));
	if(tempDenorm <= denorm){
		//removes the sign bit if on so it does not make the double NAN
		if(denormPos) fx &= ~(1<<((*def).totBits-1));
		fx &= ~(1<<((*def).totBits - (*def).expBits -2));
		fx = fx<<1;
		if(denormPos) fx |=(1L<<((*def).totBits-1));
	}






	unsigned long leftBit = 1;
	//finds furthes left value of fx
	for(i = 0; i < (*def).totBits -1; i++){
		leftBit*=2;
	}
	if(fx&leftBit){
		representations.i = representations.i|0x8000000000000000;
	}


	int bitMaskExp =1;
	for(i=0; i< (*def).expBits-1; i++){
		bitMaskExp*=2;
	}
	bitMaskExp--;

	int temp = fx>>((*def).totBits-(*def).expBits-1);
	temp &= ~(1<<(*def).expBits);
	//tooBig is a bool to know if it should convert to infinity
	bool tooBig = false;
	if(temp >= bitMaskExp*2) tooBig = true;
	temp -= bitMaskExp;
	unsigned long doubleExp = 0x3FF;
	doubleExp += temp;
	representations.i = representations.i|(doubleExp<<52);

	unsigned long fracx = 1;
	for(i=0; i< (*def).totBits - (*def).expBits -1; i++){
		fracx *= 2;
	}
	fracx--;
	fracx = fracx&fx;
	representations.i = representations.i|(fracx<<(52 - ((*def).totBits-(*def).expBits -1)));


	if(tooBig) representations.i|=0x7FF0000000000000;

	if(zero) representations.d = 0.0;

	//bitMaskExp = (fx&(bitMaskExp<<((*def).totBits-(*def).expBits - 1)))>>(*def).totBits-(*def).expBits - 1);
	



	return representations.d;
}