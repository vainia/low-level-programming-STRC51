// Ivan Napolskykh, Ilona Basowska

#include <ctype.h>

xdata at 0x8000 unsigned char U15;
xdata at 0x8000 unsigned char U12;
xdata at 0xFFFF unsigned char U10;

sfr at 0xA8 IE;

sfr at 0x89 TMOD;
sfr at 0x8D TH1;
sfr at 0x8b TL1;
sfr at 0x88 TCON;


sfr at 0x99 SBUF;
sfr at 0x98 SCON;
sfr at 0x87 PCON;

sbit at 0X98 RI;
sbit at 0X99 TI;

#define SEG_A 0x02
#define SEG_B 0x04
#define SEG_C 0x40
#define SEG_D 0x10
#define SEG_E 0x08
#define SEG_F 0x01
#define SEG_G 0x20
#define SEG_H 0x80

#define LED_0 SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F
#define LED_1 SEG_B | SEG_C
#define LED_2 SEG_A | SEG_B | SEG_D | SEG_E | SEG_G
#define LED_3 SEG_A | SEG_B | SEG_C | SEG_D | SEG_G
#define LED_4 SEG_B | SEG_C | SEG_F | SEG_G
#define LED_5 SEG_A | SEG_C | SEG_D | SEG_F | SEG_G
#define LED_6 SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define LED_7 SEG_A | SEG_B | SEG_C
#define LED_8 SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define LED_9 SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G
#define LED_a SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
#define LED_b SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
#define LED_c SEG_A | SEG_D | SEG_E | SEG_F
#define LED_d SEG_B | SEG_C | SEG_D | SEG_E | SEG_G
#define LED_e SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
#define LED_f SEG_A | SEG_E | SEG_F | SEG_G
#define LED_E SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
#define LED_r SEG_E | SEG_G
#define LED_o SEG_C | SEG_D | SEG_E | SEG_G


#define OCT_DIGIT(x,n) ((x & 07 << (3*n)) >> (3*n))

char digits[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

char content_LED[4];
const char current_LED[4] = { 0xdf, 0xef, 0x7f, 0xbf };

char t = 0;

const unsigned char klawiszZKolumny[4] = { 0xd0, 0xe0, 0x70, 0xb0 };
const unsigned char kolumna[4] = { 0xfd, 0xfe, 0xf7, 0xfb};
int key = -1;

int key_set = 0;

void led_update (void) {
    U10 = 0;
    U15 = current_LED[t];
    U10 = content_LED[t];
}

void printOCT(unsigned short int n) {
	content_LED[3] = digits[OCT_DIGIT(n, 0)];
	content_LED[2] = digits[OCT_DIGIT(n, 1)];
	content_LED[1] = digits[OCT_DIGIT(n, 2)];
	content_LED[0] = digits[OCT_DIGIT(n, 3)];
}

void sleep()
{
	int i;

	for (i=0; i< 10; i++);
}

void func_isr (void) interrupt 3
{
	U15 = kolumna[t];
	 	
	if (((U12 & 0x0f) == 0x0e) && key_set == 0) 
		{
			key = 2;
			key_set = 1;
     	}
	if (((U12 & 0x0f) == 0x0d) && key_set == 0) 
		{
			key = 3;
			key_set = 1;
     	}
	if (((U12 & 0x0f) == 0x0b) && key_set == 0) 
		{
			key = 4;
			key_set = 1;
     	}
	if (((U12 & 0x0f) == 0x07) && key_set == 0) 
		{
			key = 5;
			key_set = 1;
     	} 
    if (((U12 & 0xf0) == klawiszZKolumny[0]) && key_set == 0 && t == 0) 
		{
			key = 11;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[0]) && key_set == 0 && t == 1) 
      	{
      		key = 10;
      		key_set = 1;
    	}    
    if (((U12 & 0xf0) == klawiszZKolumny[0]) && key_set == 0 && t == 2) 
		{
			key = 13;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[0]) && key_set == 0 && t == 3) 
      	{
      		key = 12;
      		key_set = 1;
    	}  
    if (((U12 & 0xf0) == klawiszZKolumny[1]) && key_set == 0 && t == 0) 
		{
			key = 7;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[1]) && key_set == 0 && t == 1) 
      	{
      		key = 6;
      		key_set = 1;
    	}    
    if (((U12 & 0xf0) == klawiszZKolumny[1]) && key_set == 0 && t == 2) 
		{
			key = 9;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[1]) && key_set == 0 && t == 3) 
      	{
      		key = 8;
      		key_set = 1;
    	}    
    if (((U12 & 0xf0) == klawiszZKolumny[2]) && key_set == 0 && t == 0) 
		{
			key = 19;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[2]) && key_set == 0 && t == 1) 
      	{
      		key = 18;
      		key_set = 1;
    	}   
    if (((U12 & 0xf0) == klawiszZKolumny[2]) && key_set == 0 && t == 2) 
		{
			key = 21;
			key_set = 1;
     	}
    if (((U12 & 0xf0) == klawiszZKolumny[2]) && key_set == 0 && t == 3) 
      	{
      		key = 20;
      		key_set = 1;
    	}    
    if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 0) 
     	{
     		key = 15;
    	 	key_set = 1;
     	}	 
    if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 1)  
     	{
      		key = 14;
      		key_set = 1;
      	}
    if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 2) 
     	{
     		key = 17;
    	 	key_set = 1;
     	}	  
    if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 3)  
     	{
      		key = 16;
      		key_set = 1;
      	}
		led_update();
		
   t++;
   
   if(t==4) t=0;
} 

void init(void)
{
	SCON = 0x50;		//konfiguracja rs232 (L1, 8-bit, samoprzeladowalny)
	TMOD &=	0x0F;		//konfiguracja licznika
    TMOD |=	0x20;		//czy uzywamy licznika 0 czy 1 tryb z samo przeladowaniem czy bez
	TH1 = TL1 = 253;	//wartosc startowa
  	TCON = 0x40;
  	PCON = 0x80;
	IE = 0x88;
}

void putchar(char znak)
{
    SBUF = znak;
    while(TI==0);
    TI=0;
}

main (void){
	init();
	
	for (;;)
	{
		switch(key){
		
			case 2 :
				putchar('2');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 3 :
				putchar('3');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
			
			case 4 :
				putchar('4');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 5 :
				putchar('5');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
		
			case 6 :
				putchar('6');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
			
			case 7 :
				putchar('7');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;

			case 8 :
				putchar('8');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;

			case 9 :
				putchar('9');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 10 :
				putchar('1');
				putchar('0');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
			
			case 11 :
				putchar('1');
				putchar('1');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 12 :
				putchar('1');
				putchar('2');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 13 :
				putchar('1');
				putchar('3');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 14 :
				putchar('1');
				putchar('4');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;

			case 15 :
				putchar('1');
				putchar('5');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 16 :
				putchar('1');
				putchar('6');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 17 :
				putchar('1');
				putchar('7');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 18 :
				putchar('1');
				putchar('8');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 19 :
				putchar('1');
				putchar('9');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 20 :
				putchar('2');
				putchar('0');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
				
			case 21 :
				putchar('2');
				putchar('1');
				putchar(' ');
				printOCT(key+1);
				key = -1;
				key_set = 0;
				sleep();
				break;
			
			default :
				break;
		}
	}
}