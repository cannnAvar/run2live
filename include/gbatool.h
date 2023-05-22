#pragma once 

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

typedef u16 COLOR;

#define INLINE static inline

// --- Buttons ---
#define KEY_STATE      (*(volatile u16*)0x4000130) 
#define KEY_A          !(KEY_STATE &   1)
#define KEY_B          !(KEY_STATE &   2)
#define KEY_SL         !(KEY_STATE &   4)
#define KEY_ST         !(KEY_STATE &   8)
#define KEY_R          !(KEY_STATE &  16)
#define KEY_L          !(KEY_STATE &  32)
#define KEY_U          !(KEY_STATE &  64)
#define KEY_D          !(KEY_STATE & 128)
#define KEY_RS         !(KEY_STATE & 256)
#define KEY_LS         !(KEY_STATE & 512)

// === (from tonc_memmap.h) ===========================================

#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000

#define REG_DISPCNT     *((volatile u32*)(MEM_IO+0x0000))
typedef volatile u16 vu16;
#define REG_VCOUNT  *(vu16*)0x04000006 

// === (from tonc_memdef.h) ===========================================

// --- REG_DISPCNT defines ---
#define DCNT_MODE0      0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000


// === (from tonc_video.h) ============================================

#define SW  240
#define SH  160

#define vid_mem     ((u16*)MEM_VRAM)

INLINE void m3_plot(int x, int y, COLOR clr)
{   vid_mem[y*SW+x]= clr;    }


INLINE void vid_vsync()
{
    while(REG_VCOUNT >= 160){}   // wait till VDraw
    while(REG_VCOUNT < 160){}  // wait till VBlank
}


INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }
