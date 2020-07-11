/*  Programa para controle do nobrek usando pelo modulo EGS002
    Microprocessador PIC 18F46K22  16Mhz (c) JSM
    EGS002_2
    07/05/2020
*/
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

unsigned int uart_rd[10];
unsigned int index=0;
char sair=0;
int Trede =0, Tfonte =0, Tbateria =0, Tsaida =0, Cconversor =0;
char txt[20];
long tlong; long ch;

 /*===================== Definições =========================================
Seleciona os pinos de entrada e saida by Márcio.
==============================================================================*/
#define Conversor      PORTD.F0    //Variável liga desliga conversor, 1 = liga
#define Display        PORTD.F1    //liga desliga back light display, 1 = liga

/*==================== AD_Init() ===========================================
 Configurando as portas de I/O
==============================================================================*/
void AD_Init()
{
  ANSELA = 0B00001111;        // Porta a como digital
  ANSELB = 0;               // Porta B como digital
  ANSELC = 0;               // Porta C como digital
  ANSELD = 0;               // Porta D como digital
  PORTD = 0;                //Valor inicial 0
  
   ADCON1 = 0b00000000;         // Positivo referencia AVdd (bit 2,3)
                                // Negativo ref. AVss ( bit 1,0)
   TRISA  = 0b11111111;           // def. PORTA todo como entrada
   TRISB =  0b00000000;           // porto B fika todo como saida, Display
   TRISD  = 0b00000000;           //def. PORTA todo como saida
   TRISE  = 0b11111000;           //def. PORTE  E0, E1, E2 como saida
}
//===========================================================================

void main(){

  char txt[20];

  INTCON = 0;                     // disable all interrupts
  Delay_ms(100);                  // Wait for UART module to estabilize
  UART1_Init(2400);               // Initialize UART module 2400 bps
  AD_Init();                      // Configura portos para Digital
  Lcd_Init();                     // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);            // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);       // Cursor off
  Display = 1;                            // Liga back light
  Lcd_Out(1,2, "JSM Engenharia");         // Write text in first row
  Lcd_Out(2,5, "NB-400W");
  Delay_ms(2000);
  Lcd_Cmd(_LCD_CLEAR);
  
  /* Em 0 desliga */
  Conversor  = 1;                         // Liga conversor

  while (1) {
    

    
    
    Trede  = ADC_read(0);                 // get ADC value from 0nd channel
    tlong = (long)Trede * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV (*5000)
//                                         // ** exelente rotina muito precisa
//
    Lcd_Out(1,1, "Rede:");
    ch     = tlong / 1000;                 // extract volts digit
    LCD_Chr_cp(48+ch);                    // write ASCII digit at 2nd row, 9th column

    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point

    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point

   // ch    = tlong % 10;                    // extract 0.001 volts digit
   // LCD_Chr_CP('.');
   // LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('V');
    Delay_ms(300);

    // Tensão Elo Teste da  Fonte
    Tfonte  = ADC_read(1);                   // get ADC value from 0nd channel
    tlong = (long)Tfonte * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV

    ch     = tlong / 1000;                 // extract volts digit
    LCD_Chr(1,12,48+ch);                    // write ASCII digit at 2nd row, 9th column

    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('.');
    
    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
  //  ch    = tlong % 10;                    // extract 0.001 volts digit
  //  LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('V');
    Delay_ms(300);

    Tbateria  = ADC_read(2);                 // get ADC value from 0nd channel
    tlong = (long)Tbateria * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                    // 0..1023 -> 0-5000mV

    Lcd_Out(2,1, "Bat.:");
    ch     = tlong / 1000;                 // extract volts digit
    LCD_Chr_Cp(48+ch);                    // write ASCII digit at 2nd row, 9th column

    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('.');
    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point

   // ch    = tlong % 10;                    // extract 0.001 volts digit
   // LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
    LCD_Chr_CP('V');
    Delay_ms(300);

    Tsaida  = ADC_read(3);                   // get ADC value from 0nd channel
    tlong = (long)Tsaida * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV

    sprintf(txt, "%f", tlong/10. );
    Lcd_Out(2,12, txt);

//    ch     = tlong / 1000;                 // extract volts digit
//    LCD_Chr(2,13,48+ch);                    // write ASCII digit at 2nd row, 9th column
//    //LCD_Chr_CP('.');
//
//    ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
//    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//
//    ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
//    LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//
//
//    //ch    = tlong % 10;                    // extract 0.001 volts digit
//    //LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//    LCD_Chr_CP('V');


    Delay_ms(300);
  }
}