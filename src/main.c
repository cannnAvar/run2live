#include "gbatool.h"

typedef struct
{
    int x,y;
}Player;
Player P;

void buttons()                              
{
 if(KEY_R ){ P.x+=3; if(P.x>SW-1){ P.x=SW-1;}}
 if(KEY_L ){ P.x-=3; if(P.x<   0){ P.x=   0;}}
 if(KEY_U ){ P.y-=3; if(P.y<   0){ P.y=   0;}}
 if(KEY_D ){ P.y+=3; if(P.y>SH-1){ P.y=SH-1;}}
 if(KEY_A ){ } 
 if(KEY_B ){ } 
 if(KEY_LS){ } 
 if(KEY_RS){ } 
 if(KEY_ST){ } 
 if(KEY_SL){ } 
}

void clearBG()
{
    for(int x = 0;x < SW;x++)
    {
        for(int y = 0; y < SH;y++)
        {
            m3_plot(x, y, RGB15(5, 5, 5));
        }
    }
}


int main()
{
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

    P.x = 0;
    P.y = 0;

	while(1)
    {
        buttons();
        clearBG();
        m3_plot(P.x, P.y, RGB15(10,10,20));
        vid_vsync();
    }
    return 0;
}
