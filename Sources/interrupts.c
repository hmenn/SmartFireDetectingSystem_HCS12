#include "components.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


void initInterrupts(){

  TIOS=0x20; // PTT5 - output compare - buzzer
  TCTL1=0x04; // PTT5 Toggle
  
  TIE=0x20; // timer interrupt enable for PTT5

  PIEH=0xFF; // porth interrupt enable
  PPSH=0x01; // risign edge for PORTH7
}

// PORTH - SWITCH INTERRUPT HANDLER
interrupt (((0x10000-Vporth)/2)-1) void PTH_ISR(void){
  
  if(PIFH & PIFH_PIFH0_MASK){
    systemActive=~systemActive;
  }

  if(systemActive)
    PPSH = 0xFE;  // falling edge int
  else
    PPSH = 0x01;    // rising edge int
  PIFH=0xFF; // clear all interrupt flagS
}


interrupt (((0x10000-Vtimch5)/2)-1) void PTT5_ISR(void){
  PORTB=0x20;
  TC5=TCNT+40000;
  TFLG1 |= TFLG1_C5F_MASK;
}