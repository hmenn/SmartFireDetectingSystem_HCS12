#ifndef COMPONENTS_HEADER
#define COMPONENTS_HEADER

// LCD Stuffs
#define LCD_PORT PORTK
#define LCD_DDR DDRK
#define LCD_E 0x02
#define LCD_RS 0x01
#define CMD 0
#define DATA 1

void openlcd();
void puts2lcd(char *str);
void put2lcd(char c, char type);
void clearlcd();


// MQ-2 GAS SENSOR STUFFS
void initGasSensor();

void openBuzzer();
void closeBuzzer();

// INIT LED-7SEGMENTS
//unsigned char SEGMENTS[7]={0x0}
void initLEDs();



extern unsigned char systemActive;



#endif