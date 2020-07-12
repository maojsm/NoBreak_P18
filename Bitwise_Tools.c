
#include <built_in.h>
#include <string.h>


/*==================== OPERAÇÕES COM BITS ======================================
 LEITURA, ESCRITA BIT A BIT PARA USO GERAL
 _Byte  -> Variável a ser alterada.
 _bit   -> Numero do Bit selecionado, de 0 a 7
 _valor -> Valor para o bit, 0 ou 1
==============================================================================*/

/******************************************************************************
  Converte string com até 8 caracteres hexadecimais em `unsigned long`
*/
unsigned long xtol( char* strxlong)
{
    char strx_Hi[5], strx_Lo[5];
    char LongLen;
    unsigned long valor;
    // Pega o comprimento da string
    LongLen = strlen(strxlong);
    if (LongLen < 4)
    {
        valor = xtoi( strxlong );
        return valor;
    }
    else if (LongLen >= 4)
    {
        // strxlong="12345678" -> strx_hi="1234"
        strncpy( strx_Hi, strxlong, 4);
        // strxlong="12345678" -> strx_hi="4678" ou até `\0`
        strcpy( strx_Lo, strxlong+4);
        // Monmta valor unsigned long
        LoWord(valor) = xtoi(strx_Lo);
        HiWord(valor) = xtoi(strx_Hi);
        //
        return valor;

    }
}//~
     
  
/*
 * OPERANDO COM 16 BITS
 */
     
//Seta (1) um Bit e retorna o Byte sem alterar os outros bits
unsigned int setBit(unsigned int _Byte, char _bit) { return (_Byte | (0x0001 << _bit)); }

//Clear (0) um Bit e retorna o Byte sem alterar os outros bits
unsigned int clrBit(unsigned int _Byte, char _bit) { return (_Byte & ~(0x0001 << _bit)); }

//Escreve um valor no bit, conforme o valor informado 1 ou 0. Retorna Byte Alterado.
unsigned int wrBit(unsigned int _Byte, char _bit, char _valor) {
            return (_valor.F0) ? setBit(_Byte, _bit) : clrBit(_Byte, _bit); }
            
//Faz a leitura de um bit e retorna o byte 1 ou 0 representando o valor binario
char rdBit(unsigned int _Byte, char _bit) { return (char)((_Byte >> _bit) & 0x0001); }

//Alterna o Valor de um Bit, 0->1 ou 1->0. Retorna o Byte alterado.
unsigned int ivBit(unsigned int _Byte, char _bit) {
     return rdBit(_Byte, _bit) ? clrBit(_Byte, _bit) : setBit(_Byte, _bit); }
     
  

/* IntToBinStr *************************************************************/
/* Descricao:                                                              */
/*     Funcao que converte um número p/ uma string no formato binario.     */
/*     A string fornecida deve ter tamanho do numero de bits, +1.          */
/* Entrada:                                                                */
/*     char *str - String que ira receber o numero convertido (Pointer)    */
/*     int Num   - Numero a ser convertido                                 */
/*     lenBits   - Comprimento do byte, usar `sizeof( Numero )`            */
/* Retorno:                                                                */
/*     void                                                                */
/***************************************************************************/
void ByteToBinStr(char *str, char Num)
{
    char count;
    //
    for(count = 0; count < 8 /*8 bits*/; count++)
    {
      // Pega valor do bit e converte em `1` ou `0`.
      *str = ( Num.F7 ) ?  '1' : '0';
      // Passa para proximo ponto de memória do ponteiro
      str++;
      // Gira o numero a ser convertido em string de bits.
      Num <<= 1;
    }
    // Finaliza a string
    *str = '\0';

}//~

void IntToBinStr(char *str, unsigned int Num)
{
    char count;
    //
    for(count = 0; count < 16 /*16 bits*/; count++)
    {
      // Pega valor do bit e converte em `1` ou `0`.
      *str = ( Num & 0x0001 ) ?  '1' : '0';
      // Passa para proximo ponto de memória do ponteiro
      str++;
      // Gira o numero a ser convertido em string de bits.
      Num <<= 1;
    }
    // Finaliza a string
    *str = '\0';

}//~








/*******************************************************************************
 End of File
*/