//#include <8051.h>
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
//sbit at 0x8C TR0;


//char zawart_wysw[4];
const unsigned char klawiszZKolumny[4] = { 0xd0, 0xe0, 0x70, 0xb0 };
const unsigned char kolumna[4] = { 0xfd, 0xfe, 0xf7, 0xfb};
int key =-1;



int t = 0;
int key_set = 0;

void sleep()
{
int i;

for (i=0; i< 10; i++);
}


void func_isr (void) interrupt 3
{
	
	//U15=0x00;

	U15 = kolumna[t];
	 	
        if (((U12 & 0xf0) == klawiszZKolumny[0])&& key_set == 0 && t == 0) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[0])&& key_set == 0 && t == 1) 
      	{
      		key =2;
      		key_set = 1;
    	}    
     	
       if (((U12 & 0xf0) == klawiszZKolumny[0])&& key_set == 0 && t == 2) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[0])&& key_set == 0 && t == 3) 
      	{
      		key =2;
      		key_set = 1;
    	}    
     
    
    
     if (((U12 & 0xf0) == klawiszZKolumny[1])&& key_set == 0 && t == 0) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[1])&& key_set == 0 && t == 1) 
      	{
      		key =2;
      		key_set = 1;
    	}    
     	
       if (((U12 & 0xf0) == klawiszZKolumny[1])&& key_set == 0 && t == 2) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[1])&& key_set == 0 && t == 3) 
      	{
      		key =2;
      		key_set = 1;
    	}    
    
    
       if (((U12 & 0xf0) == klawiszZKolumny[2])&& key_set == 0 && t == 0) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[2])&& key_set == 0 && t == 1) 
      	{
      		key =2;
      		key_set = 1;
    	}   
    
     if (((U12 & 0xf0) == klawiszZKolumny[2])&& key_set == 0 && t == 2) 
  	{
  		key =3;
  		key_set = 1;
     	}
     	
     	  if (((U12 & 0xf0) == klawiszZKolumny[2])&& key_set == 0 && t == 3) 
      	{
      		key =2;
      		key_set = 1;
    	}    
    	
    	    	    	
    	   	
     if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 0) 
     	{
     		key =1;
    	 	key_set = 1;
     	}	
     	         
      if (((U12 & 0xf0) == klawiszZKolumny[3])&& key_set == 0 && t == 1)  
     	{
      		key =0;
      		key_set = 1;
      	}
   
      	
    	     	
     if (((U12 & 0xf0) == klawiszZKolumny[3]) && key_set == 0 && t == 2) 
     	{
     		key =1;
    	 	key_set = 1;
     	}	
     	         
      if (((U12 & 0xf0) == klawiszZKolumny[3])&& key_set == 0 && t == 3)  
     	{
      		key =0;
      		key_set = 1;
      	}
   
   
   t++;
   //key = -1;
   if(t==4) t=0;
   
} 




void init(void)
{

	SCON = 0x50;	//konfiguracja rs232 (L1, 8-bit, samoprzeladowalny)
	
	TMOD &=	0x0F;	//konfiguracja licznika
    	TMOD |=	0x20;	//czy uzywamy licznika 0 czy 1 tryb z samo przeladowaniem czy bez
	
	
	TH1 = TL1 =253;     //Wartosc startowa
  	TCON = 0x40;
  	PCON = 0x80;
	
	
	IE =	0x88;
        //TMOD =	0x20;  	    //tryb, nr licznika, czy z samoprzeladowaniem
  	
  	//TH1 = TL1 = 0;     //Wartosc startowa

	
}

void putchar(char znak)
{
    SBUF = znak;
    while(TI==0);
    TI=0;
}

main (void){
init();



	//zawart_wysw[3] = cyfra_5;
	//zawart_wysw[2] = cyfra_6;
	//zawart_wysw[1] = cyfra_4;
	//zawart_wysw[0] = cyfra_9;
	
for (;;)
{
	switch(key){
	
	case 0 :
	putchar('A');
	putchar(' ');
	key = -1;
	key_set = 0;
	sleep();
	break;
	

	case 1 :
	putchar('B');
	putchar(' ');
	key = -1;
	key_set = 0;
	sleep();
	break;

	case 2 :
	putchar('C');
	putchar(' ');
	key = -1;
	key_set = 0;
	sleep();
	break;

	case 3 :
	putchar('D');
	putchar(' ');
	key = -1;
	key_set = 0;
	sleep();
	break;
	
	default :
	break;
	}

}

}
