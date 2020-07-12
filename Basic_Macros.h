#ifndef Basic_Macros_H
#define Basic_Macros_H


   // Macros importantes do MikroC (Acho que é Standart do C)
   #include <stdint.h>
   #include <built_in.h>

   // Estruturas usadas nas funções "div"  nativas do MikroC.
   typedef struct divstruct {
               int quot;
               int rem;
   } div_t;


   typedef struct ldivstruct {
               long quot;
               long rem;
   } ldiv_t;


   typedef struct uldivstruct {
               unsigned long quot;
               unsigned long rem;
   } uldiv_t;


  /*==============================================================================
   ************** Defines (Macros) ********************
   definir todo macro comecado por "_" anderline
  ==============================================================================*/


  // Cria o tipo de variavel booleana
  #define true   1
  #define false  0
  #ifndef NULL
          #define NULL   0
  #endif
  #define bool   uint8_t


  //Configura direção dos pinos dos portos do micro
  #define   input   1
  #define   output  0

  

  
  
  
  
#endif