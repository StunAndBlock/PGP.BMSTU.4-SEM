#include <math.h>
#include "./logic_class.hpp"
#include <iostream>
int input(){
    int K;
    std::cout<<"ENTER STEP OF CURVE K=";
    int k = 0;
    std::cin >> k;
    if (k > STEP_MAX || k <0){
        std::cerr<<"VALUE ERROR, SET DEFAULT K=4" <<std::endl;
        K = 4;
    } else {
        K = k;
    }
    return K;
}

float window_offset(int K){
    return 1/pow(2,K);
}
