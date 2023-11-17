#include "./g_configurations.h"


void refill(char array[BIT_WINDOW_AMOUNT]){
    for (int i = 0; i<BIT_WINDOW_AMOUNT; i++ ){
        array[i]='0';
    }

}

void updateComplement(char source[BIT_WINDOW_AMOUNT],char complement[BIT_WINDOW_AMOUNT]){
    int i; 
    char ones[BIT_WINDOW_AMOUNT];
    char twos[BIT_WINDOW_AMOUNT]; 

  
    //  for ones complement flip every bit 
    for (i = 0; i < BIT_WINDOW_AMOUNT; i++) 
        ones[i] = (source[i]=='1') ? '0' : '1';
 
  
    //  for two's complement go from right to left in 
    //  ones complement and if we get 1 make, we make 
    //  them 0 and keep going left when we get first 
    //  0, make that 1 and go out of loop 
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
