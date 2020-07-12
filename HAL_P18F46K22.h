




#ifndef HAL_P18F46K22_H
#define HAL_P18F46K22_H


    /*===================== Defini��es =========================================
    Seleciona os pinos de entrada e saida by M�rcio.
    ==============================================================================*/
    #define Conversor              PORTD.F0    //Vari�vel liga desliga conversor, 1 = liga
    #define Display                PORTD.F1    //liga desliga back light display, 1 = liga

    #define Display_Direction      TRISD.F0    //
    #define Conversor_Direction    TRISD.F1    //

    void HAL_P18_Initialize( void );
    void Lcd_Initialize( void );

#endif  /*HAL_P18F46K22_H*/