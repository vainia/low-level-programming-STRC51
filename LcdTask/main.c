/*
 * Napolskykh Ivan, Basovska Ilona
 * sdcc 3.6.0
 */

#include <stdlib.h>
#include <8051.h>
#include "lcd.h"

void main (void) {
   LcdInit();
   LcdClrScr();
   DrawIt();
   LcdClrScr();
   set_cursor_pos(0,0);
   CountIt();
}
