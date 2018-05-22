/*
 * Napolskykh Ivan, Elon Musk(Basovska Ilona)
 * sdcc 3.6.0
 */

#include <stdlib.h>
#include <8051.h>
#include "lcd.h"

void func_isr(void) __interrupt 3 {
    counter_timer();
}

void main (void) {
	int i=0;
	
	LcdInit();
	init_time();
	LcdClrScr();

	for(i=0; i<16; ++i) {
	  ShowProgressLine(i);
	  msleep(50);
	}
	for(i=16; i>0; --i) {
	  ClearProgressLine(i-1);
	  msleep(25);
	}

	LcdClrScr();
	
	while(1) {
		set_cursor_pos(0,0);
	   LcdPrintOCT32(i);
	   ++i;
	}
}
