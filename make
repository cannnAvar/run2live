#include "gbatool.h"

int main()
{
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;

    m3_plot(10, 40, RGB15(10, 20, 30));
    m3_plot(12, 40, RGB15(30, 20, 31));
    m3_plot(13, 50, RGB15(13, 51, 31));
    m3_plot(14, 40, RGB15(11, 21, 31));

    while (1);
    return 0;
}

