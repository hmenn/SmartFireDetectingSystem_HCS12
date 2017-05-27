#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "components.h"
#include <string.h>
#include <stdlib.h>

unsigned char systemActive=0;
                                        
void main(void) {
  
  TSCR1=0x80;
  TSCR2=0x00;

  openlcd();
  initGasSensor();
  initInterrupts();
  
  DDRT=0x00;
  DDRH=0x00;
  DDRB=0xFF;
  //initLEDs();
  
  TC5=TCNT+1000;
  __asm(CLI);
  for(;;){
    if(systemActive){
      openBuzzer();
      clearlcd();
      puts2lcd("ACTIVE");
    }else{
      closeBuzzer();
      clearlcd();
      puts2lcd("DEACTIVE");
      
    }
    delay_ms(50);
  
  }
  
  /*
    
    for(;;)
    {
    ATD0CTL5 = 0x85;  //Channel 5 (right justified, unsigned,single-conver,one chan only) 
    PORTB=0;
    while(!(ATD0STAT0 & 0x80));
    PORTB=ATD0DR0L;
    if(PORTB > 128){
      clearlcd();
      puts2lcd("Alert");
    }else{
      clearlcd();
      puts2lcd("Safe");
    }
    
    
    
    
    MSDelay(100);   //optional
    }
    
     */
  }

 