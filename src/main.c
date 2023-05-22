#include "gbatool.h"

void vid_vsync()
{
    while(REG_VCOUNT >= 160);   // wait till VDraw
    while(REG_VCOUNT < 160);    // wait till VBlank
}

int main()
{
    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;

	while(1)
    {
        m3_plot(30, 79, RGB15(10,10,20));
        vid_vsync();
    }
    return 0;
}
