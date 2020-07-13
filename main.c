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


void Lcd_MostraTensoes(long  Trede, long Tfonte, long Tbateria, long Tsaida ){

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
    bool  PartidaInicial = false;
    /* Copnfigurações do Hardware - PIC, ADC, LCD, etc */
    HAL_P18_Initialize();

    /* Liga o Conversor */
    Conversor  = true;
    
    /* Tela de boas vindas */
    Lcd_Out(1,2, "JSM Engenharia");
    Lcd_Out(2,1, "NB-400W v.01.01");
    /* Tempo partida do COnversor e geração da saída */
    Delay_ms(2000);

    /* Limpa display Lcd */
    Lcd_Cmd(_LCD_CLEAR);

    /* WHILE PRINCIPAL */
    while (1){

        /* Faz a leitura das Tensões */
        Trede     = AD_Read_Tensao( AD_Rede );
        Tfonte    = AD_Read_Tensao( AD_Fonte );
        Tbateria  = AD_Read_Tensao( AD_Bateria );
        Tsaida    = AD_Read_Tensao( AD_Saida );
        
        /* Limpa LCD */
        Lcd_Cmd(_LCD_CLEAR);

        /******************************************************************

          CONTROLE DE OPERAçãO DO CONVERSOR

        *******************************************************************/
        /* Conversor Desligado - Tenta Ligar */
        if ( Conversor == false ){
        
            /*  */
            if ( (Tfonte/100) > 4 || (Tsaida/10) >= 112 ){
            
                /* Liga o conversor */
                Conversor  = true;
                
                Lcd_Out( 1, 1, "Partida Conv." );
                /* Mostra Bateria no LCD */
                sprintf(txt, "Bat.:%2.1fV", Tbateria/100. );
                Lcd_Out(2,1, txt);
                /* Mostra Tensão de Saída do NoBreak no LCD */
                sprinti(txt, "%uV", (uint16_t)Tsaida/10 );
                Lcd_Out(2,13, txt);
                /* Atraso para garantir que a partida do conversor antes do proximo teste */
                Delay_ms(3000);
                Lcd_Cmd(_LCD_CLEAR);
            }

        /* Conversor Ligado - Monitora Tensões p/ Desligar por Proteção */
        } else {
        
            /* Desliga Conversor se Tensão da Saída Baixar de 108 volts */
            if ( (Tsaida/10) <= 108 ){
            
                /* Desliaga o conversor - Proteção */
                Conversor  = false;
                
            }
        }
        
        /******************************************************************
        
          EXIBE INFORMAçõES NO LCD
        
        *******************************************************************/
        if ( Conversor == true ) {

            /* Mostra tela normal com as tensões */
            Lcd_MostraTensoes( Trede, Tfonte, Tbateria, Tsaida );
        
        
        } else {
        
            Lcd_Out( 1, 1, "Conv. Desligado" );
            /* Mostra Bateria no LCD */
            sprintf(txt, "Bat.:%2.1fV", Tbateria/100. );
            Lcd_Out(2,1, txt);
            /* Mostra Tensão de Saída do NoBreak no LCD */
            sprinti(txt, "%uV", (uint16_t)Tsaida/10 );
            Lcd_Out(2,13, txt);
        }
        
        /* Tempo entre atualizações da Tela do LCD */
        Delay_ms(1000);
    }
}















/*******************************************************************************
 End of File
*/