#include "gba.h"
#include <math.h> 

// --- Global variables ---

//actual gba screen width 
#define  GBA_SW 160                   
//game screen width 
#define  SW     120                                     
//game screen height 
#define  SH      80                                    

//15 bit, 0-31, 5bit=r, 5bit=g, 5bit=b  
#define RGB(r,g,b) ((r)+((g)<<5)+((b)<<10))            
//for frames per second 
int lastFr=0,FPS=0;                                     

typedef struct  //player
{
    int x,y;       //position
}Player;
Player P;

void clearBackground()
{
    int x,y;
    for(x = 0; x < SW; x++)
    {
        //rgb values 0-31
        for(y=0; y<SH; y++)
        {
            //clear all 120x80 pixels
            VRAM[y*GBA_SW+x]=RGB(8,12,16);
        } 
    }
}

//buttons to press
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
    P.x=70; P.y=35; //init player
}

int main()
{
    // --- Init mode ---
    //mode 5 background 2 
    REG_DISPCNT = DCNT_MODE5 | DCNT_BG2;
    //enable timer for fps
    *(u16*)0x400010A = 0x82;
    //count timer overflow 
    *(u16*)0x400010E = 0x84;

    //scale small mode 5 screen to full screen
    //256=normal 128=scale 
    REG_BG2PA=256/2;
    REG_BG2PD=256/2;
    //256=normal 128=scale 
  
    init();

    while(1) 
    {
        //draw 15 frames a second
        if(REG_TM2D>>12!=lastFr)
        {
            clearBackground();
            buttons();

            //draw player dot
            VRAM[P.y*GBA_SW+P.x]=RGB(0,31,0);               

            //frames per second

           //draw fps 
           VRAM[15]=0; VRAM[FPS]=RGB(31,31,0);              
           //increase frame
           FPS+=1; if(lastFr>REG_TM2D>>12){ FPS=0;}          
           //reset counter
           lastFr=REG_TM2D>>12;                               

           // --- swap buffers ---
           //wait all scanlines 
           while(*Scanline<160){}	                           
           //back  buffer
           if  ( DISPCNT&BACKB)
           {
               DISPCNT &= ~BACKB;
               VRAM=(u16*)VRAM_B;
           }
           //front buffer  
           else
           {                 
               DISPCNT |=  BACKB; 
               VRAM=(u16*)VRAM_F;
           }
        }
    }
}
