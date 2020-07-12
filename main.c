/*  Programa para controle do nobrek usando pelo modulo EGS002
    Microprocessador PIC 18F46K22  16Mhz (c) JSM
    EGS002_2
    07/05/2020
*/

#include <built_in.h>
#include <stdint.h>
#include "HAL_P18F46K22.h"

/******************************************************************************/

/* Numero do AD de cada leitura */
#define AD_Rede      0
#define AD_Fonte     1
#define AD_Bateria   2
#define AD_Saida     3

/******************************************************************************
  Faz aleitura da Tensãod a Bateria e converte em um valor em ponto flutuante
  que pode ser exibido no LCD.
  Ex: " Bat.: 11.8V "
  
    sprintf(txt, "Bat.:%2.1fV", tlong/100. );
    Lcd_Out(2,1, txt);
    
*/
long AD_Read_Tensao( uint8_t numAD ) {

    int  tensaoAD =0;
    long tlong;
    char txt[22];
    
    /**********************************************************************/
    /* Tensão da Bateria */
    tensaoAD  = ADC_Read(numAD);                 // get ADC value from 0nd channel
    tlong = (long)tensaoAD * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                    // 0..1023 -> 0-5000mV
    // Retorna um valor lido
    return tlong;
}






/*=============================================================================
      ************** INICIO DO PROGRAMA ********************
            ||||||||     |||||||     ||            ||
               ||       ||     ||    || ||      || ||
               ||        |||         ||   ||  ||   ||
               ||           |||      ||     ||     ||
          ||   ||       ||    |||    ||            ||
            ||||         |||||||     ||            ||
==============================================================================*/
void main( void ) {


    int Trede =0, Tfonte =0, Tbateria =0, Tsaida =0, Cconversor =0;
    long tlong; long ch;
    char txt[20];


    HAL_P18_Initialize();                // Configura portos para Digital



    Lcd_Out(1,2, "JSM Engenharia");         // Write text in first row
    Lcd_Out(2,5, "NB-400W");
    Delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);

    /* Em 0 desliga */
    Conversor  = 1;                         // Liga conversor

    /* WHILE PRINCIPAL */
    while (1) {




//      Trede  = ADC_Read(0);                 // get ADC value from 0nd channel
//      tlong = (long)Trede * 3000;           // covert adc reading to milivolts
//      tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV (*5000)
//  //                                         // ** exelente rotina muito precisa
//  //
//      Lcd_Out(1,1, "Rede:");
//      ch     = tlong / 1000;                 // extract volts digit
//      Lcd_Chr_CP(48+ch);                    // write ASCII digit at 2nd row, 9th column
//
//      ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
//      Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//
//      ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
//      Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//
//     // ch    = tlong % 10;                    // extract 0.001 volts digit
//     // LCD_Chr_CP('.');
//     // LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//      Lcd_Chr_CP('V');
//      Delay_ms(300);
//
//      // Tensão Elo Teste da  Fonte
//      Tfonte  = ADC_Read(1);                   // get ADC value from 0nd channel
//      tlong = (long)Tfonte * 3000;           // covert adc reading to milivolts
//      tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV
//
//      ch     = tlong / 1000;                 // extract volts digit
//      Lcd_Chr(1,12,48+ch);                    // write ASCII digit at 2nd row, 9th column
//
//      ch    = (tlong / 100) % 10;            // extract 0.1 volts digit
//      Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//      Lcd_Chr_CP('.');
//
//      ch    = (tlong / 10) % 10;             // extract 0.01 volts digit
//      Lcd_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//    //  ch    = tlong % 10;                    // extract 0.001 volts digit
//    //  LCD_Chr_CP(48+ch);                     // write ASCII digit at cursor point
//      Lcd_Chr_CP('V');
//      Delay_ms(300);










      // Rede
      sprinti(txt, "Rede:%uV", (uint16_t)AD_Read_Tensao(AD_Rede)/10 );
      Lcd_Out(1,1, txt);
      Delay_ms(300);
      
      // Fonte
      sprinti(txt, "%uV", (uint16_t)AD_Read_Tensao(AD_Fonte)/10 );
      Lcd_Out(1,12, txt);
      Delay_ms(300);



//      /**********************************************************************/
//      /* Tensão da Bateria */
//      Tbateria  = ADC_Read(2);                 // get ADC value from 0nd channel
//      tlong = (long)Tbateria * 3000;           // covert adc reading to milivolts
//      tlong = tlong / 1023;                    // 0..1023 -> 0-5000mV
//      /* Bat.: 11.8V */
//      sprintf(txt, "Bat.:%2.1fV", tlong/100. );
//      Lcd_Out(2,1, txt);
//
//      Delay_ms(300);



        
        /* Bat.: 11.8V */
        sprintf(txt, "Bat.:%2.1fV", AD_Read_Tensao( AD_Bateria )/100. );
        Lcd_Out(2,1, txt);

        Delay_ms(300);


      /**********************************************************************/
      /* Tensão de Saída do NoBreak */
//      Tsaida  = ADC_Read(3);                   // get ADC value from 0nd channel
//      tlong = (long)Tsaida * 3000;           // covert adc reading to milivolts
//      tlong = tlong / 1023;                  // 0..1023 -> 0-5000mV
      /* 122V */
      sprinti(txt, "%uV", (uint16_t)AD_Read_Tensao(AD_Saida)/10 );
      Lcd_Out(2,13, txt);

      Delay_ms(300);
    }
}






/*******************************************************************************
 End of File
*/