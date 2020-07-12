
#include <built_in.h>
#include "Basic_Macros.h"
#include "HAL_P18F46K22.h"


/*===================== CONFIGURAÇÃO DO LCD ====================================
Seleciona os pinos onde esta ligado o LCD. by Márcio.
==============================================================================*/
// LCD module connections
// Este modelo é o usado pela JSM 15/03/2020
sbit LCD_RS at LATB7_bit;
sbit LCD_EN at LATB6_bit;
sbit LCD_D4 at LATB5_bit;
sbit LCD_D5 at LATB4_bit;
sbit LCD_D6 at LATB3_bit;
sbit LCD_D7 at LATB2_bit;

sbit LCD_RS_Direction at TRISB7_bit;
sbit LCD_EN_Direction at TRISB6_bit;
sbit LCD_D4_Direction at TRISB5_bit;
sbit LCD_D5_Direction at TRISB4_bit;
sbit LCD_D6_Direction at TRISB3_bit;
sbit LCD_D7_Direction at TRISB2_bit;
// End LCD module connections



/*****************************************************************************
   Inicializa o LCD
*/
void Lcd_Initialize( void ) {

    Lcd_Init();                     // Initialize LCD

    Lcd_Cmd(_LCD_CLEAR);            // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF);       // Cursor off
    Display_Direction     = output;
    Display               = true;          // Liga back light

}

/*==================== AD_Init() ===========================================
 Configurando as portas de I/O
==============================================================================*/
void HAL_P18_Initialize( void ) {
  
     
     INTCON = 0;                     // disable all interrupts

     
     /* Configura pinos usados do Conversor Analogo Digital  */
     ANSELA = 0B00001111;        // Porta a como digital
     ANSELB = 0;                 // Porta B como digital
     ANSELC = 0;                 // Porta C como digital
     ANSELD = 0;                 // Porta D como digital
     PORTD  = 0;                  //Valor inicial 0, porto D inteiro como saída

     ADCON1 = 0b00000000;         // Positivo referencia AVdd (bit 2,3)
                                  // Negativo ref. AVss ( bit 1,0)
     TRISA  = 0b11111111;           // def. PORTA todo como entrada
     TRISB =  0b00000000;           // porto B fika todo como saida, Display
     TRISD  = 0b00000000;           //def. PORTA todo como saida
     TRISE  = 0b11111000;           //def. PORTE  E0, E1, E2 como saida
     
     
     /* Configura de forma discreta direção dos pinos  */
     //Display_Direction     = output;
     Conversor_Direction   = output;
     
     /* Inicializa o LCD */
     Lcd_Initialize();
     
     /* Aguarda estabilizar tensões */
     Delay_ms(100);

}//~










/*******************************************************************************
 End of File
*/