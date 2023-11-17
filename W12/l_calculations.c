#include "./g_configurations.h"
#include "./l_calculations-definitions.h"

void refill(char array[BIT_WINDOW_AMOUNT]){
    for (int i = 0; i<BIT_WINDOW_AMOUNT; i++ ){
        array[i]='0';
    }

}

void updateComplement(char source[BIT_WINDOW_AMOUNT],char complement[BIT_WINDOW_AMOUNT]){
    int i; 
    char ones[BIT_WINDOW_AMOUNT];
    char twos[BIT_WINDOW_AMOUNT]; 


    for (i = 0; i < BIT_WINDOW_AMOUNT; i++) 
        ones[i] = SINV(source[i]);
 

    for (i = 0; i < BIT_WINDOW_AMOUNT; i++) 
        complement[i] = ones[i];
    int p   =  1;
    for (i = BIT_WINDOW_AMOUNT - 1; i >= 0 && p; i--) 
    { 
        if (ones[i] == '1') 
            complement[i] = '0'; 
        else
        { 
            complement[i] = '1'; 
            p = 0 ; 
        } 
    } 
  
    // If No break : all are 1  as in 111  or  11111; 
}

void updateBinary(char source[BIT_WINDOW_AMOUNT],char binary[BIT_WINDOW_AMOUNT]){
   for (int i = 0; i < BIT_WINDOW_AMOUNT; i++) {
       binary[i] = SINV(source[i]);
   }
   int carry = 1;
   for (int i = BIT_WINDOW_AMOUNT - 1; i >= 0; i--) {
       if (binary[i] == '1' && carry == 1) {
           binary[i] = '0';
       } else if (binary[i] == '0' && carry == 1) {
           binary[i] = '1';
           carry = 0;
       } else {
           binary[i] = binary[i];
       }
   }
}
