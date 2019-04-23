#include "interrupt.h"

int getINT_LINE()
{
	unsigned int int_line = getCAUSE(); // Leggo il contenuto del registro cause
	int_line = int_line >> 2; //shift a destra di 2 bit
	int_line = (int_line&(0x0000001F)); // And bit a bit per avere un intero che identifichi la linea 
	return int_line;
}


