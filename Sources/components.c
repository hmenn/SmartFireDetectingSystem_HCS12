#include <hidef.h>      /* common defines and macros */
#include "derivative.h"
#include "components.h"

void delay_ms(unsigned int itime){
    unsigned int i; unsigned int j;
    for(i=0;i<itime;i++)
      for(j=0;j<4000;j++);    //1 msec. tested using Scope
}


/*

  LCD DISPLAY OPERATIONS

*/
void openlcd(void){
  LCD_DDR = 0xFF;
  delay_ms(100);
  put2lcd(0x28,CMD); // 4bit data 2line, 5*7
  put2lcd(0x0F,CMD); // turn on display, cursor, blinking
  put2lcd(0x06,CMD); // move cursor right
  put2lcd(0x01,CMD); // clear screen, move cursor to home
  delay_ms(2);  // wait until clear display
}

void clearlcd(){
  put2lcd(0x06,CMD); // move cursor right
  put2lcd(0x01,CMD); // clear screen, move cursor to home
  delay_ms(2);  // wait until clear display
}

void puts2lcd(char *str){
  while(*str){
    put2lcd(*str,DATA);
    delay_ms(1);
    str++; 
  }
}

void put2lcd(char ch, char type){
  char c_lo,c_hi;
  c_hi = (ch & 0xF0) >>2;
  c_lo = (ch & 0x0F) <<2;
  
  if(type == DATA)
    LCD_PORT = c_hi | 0x01;
  else
    LCD_PORT = c_hi & (~0x01);
  
  LCD_PORT |= 0x02;
  __asm(nop);
  __asm(nop);
  __asm(nop);
  LCD_PORT &= (~0x02);
  
  if(type ==DATA)
    LCD_PORT = c_lo | 0x01;
  else
    LCD_PORT = c_lo & 0xFE;
  
  LCD_PORT |= LCD_E;
  __asm(nop);
  __asm(nop);
  __asm(nop);
  LCD_PORT &= (~LCD_E);
  delay_ms(2);
}




/*
  MQ-2 Gas Sensor
*/


void initGasSensor(){
  ATD0CTL2 = 0x80;     //Turn on ADC,..No Interrupt
  delay_ms(5);
  ATD0CTL3 = 0x08;  //one conversion, no FIFO
  ATD0CTL4 = 0xEB;  //8-bit resolu, 16-clock for 2nd phase,
                    //prescaler of 24 for Conversion Freq=1MHz  
}






/*
  INIT LED-7SEGMENTS
*/





/*
  BUZZZER SETTINGS

*/

void openBuzzer(){
  TCTL1=0x04;
  DDRT=0xFF;
  TIE |= 0x20;
  DDRT=0xFF;
}
void closeBuzzer(){
  TIE &= (~0x20);
  PTT=0x00;
  DDRT=0x00;
  PORTB=0x10;
  TCTL1=0x00;
}
