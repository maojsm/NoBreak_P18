/*  Programa para controle do nobrek usando pelo modulo EGS002
    Microprocessador PIC 18F46K22  16Mhz (c) JSM
    EGS002_2
    07/05/2020
*/

#include <built_in.h>
#include <stdint.h>
#include "Basic_Macros.h"
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

    /* Leitura da tensão no ADC */
    tensaoAD  = ADC_Read(numAD);              // get ADC value from 0nd channel
    tlong = (long)tensaoAD * 3000;           // covert adc reading to milivolts
    tlong = tlong / 1023;                    // 0..1023 -> 0-5000mV
    // Retorna um valor lido
    return tlong;
    
}//~


void MostraTensoes_LCD(long  Trede, long Tfonte, long Tbateria, long Tsaida ){

    char  txt[20];
    
    /* Mostra Rede no LCD*/
    sprinti(txt, "Rede:%uV", (uint16_t)Trede/10 );
    Lcd_Out(1,1, txt);

    /* Mostra Fonte no LCD */
    sprintf(txt, "%2.1fV", Tfonte/100. );
    Lcd_Out(1,13, txt);

    /* Mostra Bateria no LCD */
    sprintf(txt, "Bat.:%2.1fV", Tbateria/100. );
    Lcd_Out(2,1, txt);

    /* Mostra Tensão de Saída do NoBreak no LCD */
    sprinti(txt, "%uV", (uint16_t)Tsaida/10 );
    Lcd_Out(2,13, txt);

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


    long  Trede=0, Tfonte =0, Tbateria =0, Tsaida =0;
    char  txt[20];
    char  i=0;

    /* Copnfigurações do Hardware - PIC, ADC, LCD, etc */
    HAL_P18_Initialize();

    /* Inicia com Conversor Desligado (Não Produz Energia) */
    Conversor  = false;

    Lcd_Out(1,2, "JSM Engenharia");         // Write text in first row
    Lcd_Out(2,5, "NB-400W");
    Delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);

    /* Liga o Conversor */
    Conversor  = true;
    
    /* Aguarda o Conversor partir e atingir 112V */
    for (i=0; i < 10 ; i++) {
    
        /* Faz a leitura das Tensões */
        Trede     = AD_Read_Tensao( AD_Rede );
        Tfonte    = AD_Read_Tensao( AD_Fonte );
        Tbateria  = AD_Read_Tensao( AD_Bateria );
        Tsaida    = AD_Read_Tensao( AD_Saida );
    
        
        sprinti(txt, "Partindo: %u", (int)i );
        Lcd_Out(1,1, txt);
        
        /* Mostra Bateria no LCD */
        sprintf(txt, "Bat.:%2.1fV", Tbateria/100. );
        Lcd_Out(2,1, txt);
        /* Mostra Tensão de Saída do NoBreak no LCD */
        sprinti(txt, "%uV", (uint16_t)Tsaida/10 );
        Lcd_Out(2,13, txt);
        
        
        Delay_ms(1000);
    
    
    }
    
    
    

    /* WHILE PRINCIPAL */
    while (1) {

        /* Faz a leitura das Tensões */
        Trede     = AD_Read_Tensao( AD_Rede );
        Tfonte    = AD_Read_Tensao( AD_Fonte );
        Tbateria  = AD_Read_Tensao( AD_Bateria );
        Tsaida    = AD_Read_Tensao( AD_Saida );
        
        /* Limpa LCD */
        Lcd_Cmd(_LCD_CLEAR);
        
        /* Fonte ligada? */
        if ( (Tfonte/100) > 4  ) {
        
             /* Liga o conversor */
             Conversor  = true;
             /* Mostra tela normal com as tensões */
             MostraTensoes_LCD( Trede, Tfonte, Tbateria, Tsaida );
        

        } else {
        
           /* Tensão na Saída normal, ou seja, maior que 108 volts */
            if ( (Tsaida/10) >= 112 ) {

               /* Liga o conversor */
               Conversor  = true;
               /* Mostra tela normal com as tensões */
               MostraTensoes_LCD( Trede, Tfonte, Tbateria, Tsaida );

            /* Tensão  */
            } else if ( (Tsaida/10) <= 108 ) {


                /* Desliga o conversor */
                Conversor  = false;
               
               
                Lcd_Out( 1, 1, "Conv. Desligado" );
                /* Mostra Bateria no LCD */
                sprintf(txt, "Bat.:%2.1fV", Tbateria/100. );
                Lcd_Out(2,1, txt);
                /* Mostra Tensão de Saída do NoBreak no LCD */
                sprinti(txt, "%uV", (uint16_t)Tsaida/10 );
                Lcd_Out(2,13, txt);

            } else {
            
               Lcd_Out( 1, 1, "Entre 108 e 112V" );
            
            }
            
        
        }


        

        /* Tempo entre atualizações da Tela do LCD */
        Delay_ms(1000);
    }
}















/*******************************************************************************
 End of File
*/