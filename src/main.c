#include "gba.h"

typedef struct
{
    int x,y;
    
}Entity;
Entity P;

void clearBackground()
{
    int x,y;
    for(x = 0; x < SW; x++)
    {                                               
    //rgb values 0-31
    for(y=0;y<SH;y++)
    {
        m3_plot(x, y, RGB15(8, 12, 16));
    } 
    //clear all 120x80 pixels
 }
}


void buttons()
{
 //move right
 if(KEY_R ){ P.x+=3; if(P.x>SW-1){ P.x=SW-1;}}            
 //move left
 if(KEY_L ){ P.x-=3; if(P.x<   0){ P.x=   0;}}             
 //move up
 if(KEY_U ){ P.y-=3; if(P.y<   0){ P.y=   0;}}             
 //move down
 if(KEY_D ){ P.y+=3; if(P.y>SH-1){ P.y=SH-1;}}             
 if(KEY_A ){ } 
 if(KEY_B ){ } 
 if(KEY_LS){ } 
 if(KEY_RS){ } 
 if(KEY_ST){ } 
 if(KEY_SL){ } 
}

void init()
{
    P.x = 100;
    P.y = 80;
}


int main()
{
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
    init();

    while(1)
    {
        clearBackground();
        buttons();
        m3_plot(P.x,P.y,RGB15(0, 15, 0));
    }
    return 0;
}       
