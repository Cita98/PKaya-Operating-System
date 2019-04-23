#include "interrupt.h"

int getINT_LINE()
{
	unsigned int int_line = getCAUSE(); 
	int_line = int_line >> 2; 
	int_line = (int_line&(0x0000001F));
	return int_line;
}


