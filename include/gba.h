

// --- rename unsigned short and long ---

typedef unsigned short u16;
typedef unsigned long  u32; 

// --- Video buffer ---

u16    *VRAM; 
#define VRAM_F         (u16*)0x6000000 
#define VRAM_B         (u16*)0x600A000
#define DISPCNT        *(u32*)0x4000000
#define BACKB   	   0x10 
volatile u16* Scanline=(volatile u16*)0x4000006;

// --- Modes ---


#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000


#define REG_DISPCNT     *((volatile u32*)(MEM_IO+0x0000))


// --- REG_DISPCNT defines ---
#define DCNT_MODE0     0x0000
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


// --- Scale mode 5 screen ---

#define REG_BG2PA *(volatile unsigned short *)0x4000020
#define REG_BG2PD *(volatile unsigned short *)0x4000026


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


// --- Timer for FPS ---
#define REG_TM2D       *(volatile u16*)0x4000108

// --- Fast Iwram and Ewram ---

#define IN_IWRAM       __attribute__ ((section (".iwram")))
#define IN_EWRAM       __attribute__ ((section (".ewram")))


//Extended sound control
#define REG_SOUNDCNT_X  *(volatile u16*)0x4000084

//DMG sound control
#define REG_SOUNDCNT_L  *(volatile u16*)0x4000080

//Direct sound control
#define REG_SOUNDCNT_H  *(volatile u16*)0x4000082 
#define REG_SOUND3CNT_L *(volatile u16*)0x4000070

//Use two banks of 32 steps each
#define SOUND3BANK32    0x0000 
#define SOUND3SETBANK1  0x0040
#define REG_WAVE_RAM0   *(volatile u32*)0x4000090 
#define REG_WAVE_RAM1   *(volatile u32*)0x4000094 
#define REG_WAVE_RAM2   *(volatile u32*)0x4000098 
#define REG_WAVE_RAM3   *(volatile u32*)0x400009C

//Bank to play 0 or 1 (non set bank is written to)
#define SOUND3SETBANK0  0x0000

//Output sound
#define SOUND3PLAY	    0x0080
#define REG_SOUND3CNT_H *(volatile u16*)0x4000072 

//Output unmodified
#define SOUND3OUTPUT1   0x2000 
#define REG_SOUND3CNT_X *(volatile u16*)0x4000074 

//Makes the sound restart
#define SOUND3INIT	    0x8000

//Play sound once
#define SOUND3PLAYONCE  0x4000

void PlayNote( u16 frequency, unsigned char length )
{

	unsigned char adjustedLength = 0xFF - length;

	REG_SOUNDCNT_X = 0x80;
	REG_SOUNDCNT_L=0xFF77;

	REG_SOUNDCNT_H = 2;

	REG_SOUND3CNT_L = SOUND3BANK32 | SOUND3SETBANK1;
	REG_WAVE_RAM0=0x10325476;
	REG_WAVE_RAM1=0x98badcfe;
	REG_WAVE_RAM2=0x10325476;
	REG_WAVE_RAM3=0x98badcfe;
	REG_SOUND3CNT_L = SOUND3BANK32 | SOUND3SETBANK0;

	REG_SOUND3CNT_L |= SOUND3PLAY;

	REG_SOUND3CNT_H = SOUND3OUTPUT1 | adjustedLength;
	REG_SOUND3CNT_X=SOUND3INIT|SOUND3PLAYONCE| frequency ;
}

//example 458*sin(90) would be written as (458*LUT_Sin[90])>>8
const int LUT_Sin[] =
{
0,4,9,13,18,22,27,31,36,40,44,49,53,58,62,66,71,75,79,83,88,
92,96,100,104,108,112,116,120,124,128,132,136,139,143,147,150,154,158,161,165,
168,171,175,178,181,184,187,190,193,196,199,202,204,207,210,212,215,217,219,222,
224,226,228,230,232,234,236,237,239,241,242,243,245,246,247,248,249,250,251,252,
253,254,254,255,255,255,256,256,256,256,256,256,256,255,255,255,254,254,253,252,
251,250,249,248,247,246,245,243,242,241,239,237,236,234,232,230,228,226,224,222,
219,217,215,212,210,207,204,202,199,196,193,190,187,184,181,178,175,171,168,165,
161,158,154,150,147,143,139,136,132,128,124,120,116,112,108,104,100,96,92,88,
83,79,75,71,66,62,58,53,49,44,40,36,31,27,22,18,13,9,4,0,
-4,-9,-13,-18,-22,-27,-31,-36,-40,-44,-49,-53,-58,-62,-66,-71,-75,-79,-83,-88,
-92,-96,-100,-104,-108,-112,-116,-120,-124,-128,-132,-136,-139,-143,-147,-150,-154,-158,-161,-165,
-168,-171,-175,-178,-181,-184,-187,-190,-193,-196,-199,-202,-204,-207,-210,-212,-215,-217,-219,-222,
-224,-226,-228,-230,-232,-234,-236,-237,-239,-241,-242,-243,-245,-246,-247,-248,-249,-250,-251,-252,
-253,-254,-254,-255,-255,-255,-256,-256,-256,-256,-256,-256,-256,-255,-255,-255,-254,-254,-253,-252,
-251,-250,-249,-248,-247,-246,-245,-243,-242,-241,-239,-237,-236,-234,-232,-230,-228,-226,-224,-222,
-219,-217,-215,-212,-210,-207,-204,-202,-199,-196,-193,-190,-187,-184,-181,-178,-175,-171,-168,-165,
-161,-158,-154,-150,-147,-143,-139,-136,-132,-128,-124,-120,-116,-112,-108,-104,-100,-96,-92,-88,
-83,-79,-75,-71,-66,-62,-58,-53,-49,-44,-40,-36,-31,-27,-22,-18,-13,-9,-4,
};

const int LUT_Cos[] =
{
256,256,256,256,255,255,255,254,254,253,252,251,250,249,248,247,246,245,243,242,241,
239,237,236,234,232,230,228,226,224,222,219,217,215,212,210,207,204,202,199,196,
193,190,187,184,181,178,175,171,168,165,161,158,154,150,147,143,139,136,132,128,
124,120,116,112,108,104,100,96,92,88,83,79,75,71,66,62,58,53,49,44,
40,36,31,27,22,18,13,9,4,0,-4,-9,-13,-18,-22,-27,-31,-36,-40,-44,
-49,-53,-58,-62,-66,-71,-75,-79,-83,-88,-92,-96,-100,-104,-108,-112,-116,-120,-124,-128,
-132,-136,-139,-143,-147,-150,-154,-158,-161,-165,-168,-171,-175,-178,-181,-184,-187,-190,-193,-196,
-199,-202,-204,-207,-210,-212,-215,-217,-219,-222,-224,-226,-228,-230,-232,-234,-236,-237,-239,-241,
-242,-243,-245,-246,-247,-248,-249,-250,-251,-252,-253,-254,-254,-255,-255,-255,-256,-256,-256,-256,
-256,-256,-256,-255,-255,-255,-254,-254,-253,-252,-251,-250,-249,-248,-247,-246,-245,-243,-242,-241,
-239,-237,-236,-234,-232,-230,-228,-226,-224,-222,-219,-217,-215,-212,-210,-207,-204,-202,-199,-196,
-193,-190,-187,-184,-181,-178,-175,-171,-168,-165,-161,-158,-154,-150,-147,-143,-139,-136,-132,-128,
-124,-120,-116,-112,-108,-104,-100,-96,-92,-88,-83,-79,-75,-71,-66,-62,-58,-53,-49,-44,
-40,-36,-31,-27,-22,-18,-13,-9,-4,0,4,9,13,18,22,27,31,36,40,44,
49,53,58,62,66,71,75,79,83,88,92,96,100,104,108,112,116,120,124,128,
132,136,139,143,147,150,154,158,161,165,168,171,175,178,181,184,187,190,193,196,
199,202,204,207,210,212,215,217,219,222,224,226,228,230,232,234,236,237,239,241,
242,243,245,246,247,248,249,250,251,252,253,254,254,255,255,255,256,256,256,
};

