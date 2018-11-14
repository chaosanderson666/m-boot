#include "S3C2440addr.h"

void disable_watch_dog();

void disable_watch_dog()
{
	rWTCON = 0;
}

void clear_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;
	int *q = &__bss_end;
	
	for (; p < q; p++)
		*p = 0;
}