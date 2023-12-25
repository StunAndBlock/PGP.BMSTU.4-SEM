/* only c++11 compatibility granted*/
#include "./logic_class.hpp"
#include "./gi_class.hpp"
#include <iostream>



int main(int argc, char** argv){
    constexpr uint16_t N = 2;
    int K = input();
    uint16_t curve[(1U << N*K)][N];
    Hilbert<>::IsToVsN<N>(K,curve[0]);
    Genv obj;
    obj.graphics_init();
    obj.windows_init(window_offset(K));
    obj.draw_hilbert(N,K,curve);
    //     for (int i=0; i < 1U << N * K; i++){
    // for(int j=0;j < N;j++){
    //   std::cout<< curve[i][j]<< " ";
    // }
    // std::cout<< std::endl;
    // }
    obj.dispatch();
    return 0;
}


int Genv::dispatch(){
    XEvent event;
    int flag=1;
    while (flag)
    {
        XNextEvent(dpy,&event);
        switch (event.type)
        {
        case KeyPress:
            if(event.xkey.keycode == XKeysymToKeycode(dpy,_XK_ESCAPE)){
                    flag = 0;
            }
            std::cout<<1;
            break;
        case ButtonPress:
                    flag = 0;
            std::cout<<1;
        default:
            break;
        }
    }
    return flag;
}