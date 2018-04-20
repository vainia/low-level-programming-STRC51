//Yakymyshyn Napolsky
#include <stdlib.h>
#include <math.h>
#include <8051.h>

xdata at 0x8000 unsigned char U15;
xdata at 0xFFFF unsigned char U10;

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


#define HEX(x,n) ((x & 0xf << (4*n)) >> (4*n))
#define MAX 0xffff

char digits[] = {LED_0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_a, LED_b, LED_c, LED_d, LED_e, LED_f};

char LED[4];
char current_LED[4] = { 0xdf, 0xef, 0x7f, 0xbf };

char t = 0;

void func_isr (void) interrupt 3
{
        if (t >= 4) t = 0;
        U10 = 0;
        U15 = current_LED[t];
        U10 = LED[t];
        ++t;
}

void initLED(void)
{
        SCON = 0x50;
        TMOD &= 0x0F;
        TMOD |= 0x20;
        TCON = 0x40;
        TH1 = 253;
        TL1 = 253;
        PCON = 0x80;
        IE = 0x88;
        ES=1;
}

void toHEX(unsigned short int n)
{
        if (n < MAX)
        {
                LED[3] = digits[HEX(n, 0)];
                LED[2] = digits[HEX(n, 1)];
                LED[1] = digits[HEX(n, 2)];
                LED[0] = digits[HEX(n, 3)];
        }
}

main (void)
{
        char c;
        char buf[5] = {0};
        char i = 0;
        initLED();
        toHEX(0);
        while (1)
        {
                if(RI)
                {
                        c = SBUF;
                        if (i >= 3)
                        {
                                buf[i] = c;
                                i = 0;
                                toHEX(atoi(buf)/4);
                        }
                        else
                        {
                                buf[i++] = c;
                        }
                        RI = 0;
                }
        }
}
