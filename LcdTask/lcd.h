#ifndef LCD_H
#define LCD_H

void msleep(int n);
void DrawIt();
void CountIt();

void LcdInit();
void LcdClrScr();
void ShowProgressLine(char idx);
void LcdPrintOCT32(unsigned int x);

void set_cursor_pos(char x, char y);
void print_LCD(unsigned char data);

#endif /* LCD_H */
