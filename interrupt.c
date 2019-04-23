#include "interrupt.h"

int getBit (int shift, unsigned int reg){
        if (shift < 0 || shift >31) return -1;
        unsigned int tmp = 1;
        tmp = tmp << shift;
        return (tmp & reg) >> shift;
}

int getINT_LINE()
{
	/*unsigned int int_line = getCAUSE();
	int_line = int_line >> 2; 
	int_line = (int_line&(0X0000001F));
	return int_line;*/
	int i;
	unsigned int tmp = getCAUSE();
	for (i=0; i<16; i++)
		if (getBit(i,tmp)) return i;
	return -1;
}


