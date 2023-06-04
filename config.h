#pragma config FEXTOSC=XT
#pragma config WDTE=OFF
#pragma config LVP=OFF

#define _XTAL_FREQ     4000000
#define LED1 PORTAbits.RA1

#define LCD_DATA PORTD
#define LCD_RS PORTEbits.RE1
#define LCD_E PORTEbits.RE0