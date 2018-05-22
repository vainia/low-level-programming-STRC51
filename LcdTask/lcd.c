#include <8051.h>
#include "lcd.h"

static const char E = 0x08;
static const char RS = 0x04;
static volatile int mcounter = 0;

void msleep(int n) {
    mcounter = 0;
    while(mcounter < n) __asm__("nop");
}

unsigned int DEC_TO_HEX(unsigned int n)
{
    unsigned int res = 0;
    unsigned int pos = 1;
    while (n)
    {
        res += (n%8)*pos;
        n /= 8;
        pos *= 10;
    }
    return res;
}

unsigned int DIGIT_LEN(unsigned int n) {
    if (n < 10) return 1;
    return 1 + DIGIT_LEN(n / 10);
}

static char GET_OCTET(unsigned int x, char n)
{
    if (DIGIT_LEN(DEC_TO_HEX(x)) < n) return 0;
    return ((x & 07 << (3*n)) >> (3*n));
}

static void send_cmd_8(unsigned char cmd)
{
    P1=cmd;
    P1=cmd | E;
    P1=cmd & !E;
}

static void send_cmd(unsigned char cmd)
{
    P1=cmd & 0xf0;
    P1=(cmd & 0xf0) | E;
    P1=(cmd & 0xf0) & !E;
    P1=(cmd << 4) & 0xf0;
    P1=((cmd << 4) & 0xf0) | E;
    P1=((cmd << 4) & 0xf0) & !E;
}

void print_LCD(unsigned char data)
{
    P1=(data & 0xf0) | RS;
    P1=((data & 0xf0) | E) | RS;
    P1=((data & 0xf0) & !E) | RS;
    P1=((data << 4) & 0xf0) | RS;
    P1=(((data << 4) & 0xf0) | E) | RS;
    P1=(((data << 4) & 0xf0) & !E) | RS;
}

void set_cursor_pos(char x, char y) {
    char i = y == 0 ? 0x80 : 0xC0;
    i |= x;
    send_cmd(i);
    msleep(2);
}

static void print_LCD_at(char c, char x, char y) {
    set_cursor_pos(x,y);
    print_LCD(c);
}

void LcdClrScr() {
    send_cmd(0x01);
    msleep(3);
}

void ShowProgressLine(char idx) {
    print_LCD_at(idx%8, idx, idx < 8 ? 1 : 0);
    msleep(500);
}

void DrawIt() {
    char i=0;
    for(i=0; i<16; ++i) {
      ShowProgressLine(i);
      msleep(1);
    }
}

static char octet_to_char(char x) {
    return '0' + x;
}

void LcdPrintOCT32(unsigned int x) {
    char i = 0;
    print_LCD('8');
    msleep(1);
    print_LCD(':');
    msleep(1);
    for(i = 0; i < 11; ++i)
    {
        print_LCD(octet_to_char(GET_OCTET(x,i)));
        msleep(1);
    }
}

void CountIt(){
    int i = 0;
    for(i = 0; i < 32767; ++i)
    {
       LcdPrintOCT32(i);
    }
}

static void init_line() {
    char i = 0;
    char j = 0;

    for (j = 0; j < 8; ++j) {
        send_cmd(0x40 | (j*8));
        msleep(5);
        for (i = 0; i < 8; ++i) {
            print_LCD(j == 7-i ? 0x1F : 0x00);
            msleep(5);
        }
    }
}

void LcdInit()
{
    SCON = 0x50;
    TMOD &= 0x0F;
    TMOD |= 0x20;
    TH1 = TL1 = 253;
    TCON = 0x40;
    PCON = 0x80;
    IE =    0x88;

    msleep(15);
    send_cmd_8(0x30);
    msleep(5);
    send_cmd_8(0x30);
    msleep(1);
    send_cmd_8(0x30);
    msleep(5);
    send_cmd_8(0x20);
    msleep(1);
    send_cmd(0x2C);
    msleep(1);
    send_cmd(0x08);
    msleep(1);
    send_cmd(0x0C);
    msleep(1);
    send_cmd(0x06);
    msleep(1);
    send_cmd(0x14);
    msleep(1);

    init_line();
}
