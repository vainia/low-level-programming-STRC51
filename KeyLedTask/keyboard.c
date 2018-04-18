#include "keyboard.h"

#define KEY (U12 & 0xf0)

__sfr __at 0xA8 IE;
__sfr __at 0x89 TMOD;
__sfr __at 0x8D TH1;
__sfr __at 0x8b TL1;
__sfr __at 0x88 TCON;
__sfr __at 0x99 SBUF;
__sfr __at 0x98 SCON;
__sfr __at 0x87 PCON;
__sbit __at 0X98 RI;
__sbit __at 0X99 TI;

__xdata __at 0x8000 unsigned char U15;
__xdata __at 0x8000 unsigned char U12;
const unsigned char klawiszZKolumny[4] = { 0xd0, 0xe0, 0x70, 0xb0 };
const unsigned char kolumna[4] = { 0xfd, 0xfe, 0xf7, 0xfb}; 		
int key =-1;		
int t = 0;			
int key_set = 0;	


char keys[4][4] =
{
	{19,15,11,7},
	{18,14,10,6},
	{21,17,13,9},
	{20,16,12,8}
};


void get_key (void) 
{
	
    int i = 0;
	U15 = kolumna[t];
    for (i = 0; i < 16; i++) {
        if ((KEY == klawiszZKolumny[i%4])&& !key_set && t == i) 
		{
			key =keys[t][i%4];
			key_set = 1;
     	}
    }
      
   t++;
   t=t%4;
   
} 





