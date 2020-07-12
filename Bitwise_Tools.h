#ifndef Bitwise_Tools_H
#define Bitwise_Tools_H

        // PROTÓTIPOS
//        char setBit(char , char );
//        char clrBit(char , char );
//        char wrBit(char , char , char );
//        char rdBit(char , char );
//        char ivBit(char , char );

        unsigned long xtol( char* );
        // Operações com 16 bits.
        unsigned int setBit(unsigned int , char );
        unsigned int clrBit(unsigned int , char );
        unsigned int wrBit(unsigned int , char , char );
        char rdBit(unsigned int , char );
        unsigned int ivBit(unsigned int , char );

        void ByteToBinStr(char *, char );
        void IntToBinStr(char *, unsigned int );
        
        char *strtok_r(char *, const char *, char **);
        
#endif /*Bitwise_Tools_H*/