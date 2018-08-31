#ifndef __CBCPU_H_
#define __CBCPU_H_ 1

 class GameBoyCPU {
 	 public:
 	   // NB : on ne nomme pas les arguments
 	   GameBoyCPU(bool*);
 	   
 	   void startThread();
 	   void stopThread();
 	   bool getThreadState();
 	   
 	   void tick();
 	   void run();
 	   
 	   bool loadRom(char* romName); // TO MOVE AWAY
 	   void fullReset();
 	   
 	   GameBoyVideo* getVideo();
 	   int* getBGPalette();
 	   int* getOBJ0Palette();
 	   int* getOBJ1Palette();
 	   
 	   void setBackPalette();
 	   void setForePalette0();
 	   void setForePalette1();
 	   
 	   //void setLCDControl();
 	   //void setTimer();
 	   
 	   //void handleGBInput();
 	   
 	   unsigned char getMem(int);
 	   //int getMemNN();
 	   //int getSignedMemN();
 	   //void setMem(int i, unsigned char c);
 	   
 	 private:
 	   //int getGBColour(int i);     // \
 	   //int rgb2GBUpper(int color); //  |- should staty non member static ??
 	   //int rgb2GBLower(int color); // /
 	  
 	   GameBoyVideo* VIDEO; 
 	   
 	  static const int incAllValue[];
    static const int incAllValueCB[];
 	   
    void setLCDControl();
    void setTimer();
    void handleGBInput();
    unsigned char getUpper(int i);
    unsigned char getLower(int i);
    int combine(unsigned char c, unsigned char c1);
    int getMemNN();
    int getSignedMemN();
    void setMem(int i, unsigned char c);
    int getGBColour(int i);
    int rgb2GBUpper(int color);
    int rgb2GBLower(int color);
    void ADC(unsigned char c);
    void ADD(unsigned char c);
    int ADD16(int i, int j);
    int ADDSP(int i);
    void AND(unsigned char c);
    
    void BIT(int i, unsigned char c);
    //int BIT(int i, int j);
    int BIT_get(int i, int j);
    
    void CALL();
    void CCF();
    void CP(unsigned char c);
    void CPL();
    void DAA();
    unsigned char DEC(unsigned char c);
    int DEC16(int i);
    unsigned char INC(unsigned char c);
    int INC16(int i);
    void JP();
    void JR();
    void OR(unsigned char c);
    int POP();
    void PUSH(int i);
    unsigned char RES(int i, unsigned char c);
    void RET();
    unsigned char RL(unsigned char c);
    void RLA();
    unsigned char RLC(unsigned char c);
    void RLCA();
    unsigned char RR(unsigned char c);
    void RRA();
    unsigned char RRC(unsigned char c);
    void RRCA();
    void RST(int i);
    void SBC(unsigned char c);
    void SUB(unsigned char c);
    void SCF();
    unsigned char SET(int i, unsigned char c);
    unsigned char SLA(unsigned char c);
    unsigned char SRA(unsigned char c);
    unsigned char SRL(unsigned char c);
    unsigned char SWAP(unsigned char c);
    void XOR(unsigned char c);
    void incAll(int i);
    void opCodeList1();
    void singleCPUStepCB();
    void createDAATable();
    void createSwapTable();
    
    static const int GB_MEM_length = 0x10000;
    static const int VRAM_length = 16384;
    static const int PAGED_RAM_length = 32768;
    
    unsigned char GB_MEM[0x10000];
    unsigned char VRAM[16384];
    unsigned char PAGED_RAM[32768];
    
    unsigned char* CART_RAM;
    unsigned char* CART_ROM;
    
    unsigned char A;
    unsigned char B;
    unsigned char C;
    unsigned char D;
    unsigned char E;
    unsigned char F;
    unsigned char H;
    unsigned char L;
    unsigned char* SWAP_TABLE;
    unsigned char tempChar;
    int AF;
    int BC;
    int DE;
    int HL;
    int PC;
    int SP;
    int* DAA_TABLE;
    int MBC;
    int MBC_MODE;
    int RAM_PAGE;
    int ROM_PAGE;
    int TIMER;
    int TIMER_MAX;
    int CPU_CYCLES;
    int CPU_SPEED;
    int TIMER_CYCLES;
    int DIV;
    int SPR_PER_LINE;
    int opCode;
    int opCode2;
    int tempOpCodeRegister;
    bool APPLET_RUNNING;
    bool* KEYS_PRESSED;
    bool IME;
    bool STOP;
    bool HALT;
    bool HALT_NEXT;
    bool TIMER_ON;
    bool RAM_ENABLE;
    bool RUMBLE_PACK;
    int* DEFAULTS;
    int* BGPALETTE;
    int* OBJ0PALETTE;
    int* OBJ1PALETTE;
    
    //private Thread instance;
    
    char* romName;
    
    static const unsigned char Z_FLAG = 128;
    static const unsigned char N_FLAG = 64;
    static const unsigned char H_FLAG = 32;
    static const unsigned char C_FLAG = 16;
    static const int JOYPAD = 65280;
    static const int SERIAL_DATA = 65281;
    static const int SERIAL_CTRL = 65282;
    static const int DIV_CNTR = 65284;
    static const int TIMER_COUNT = 65285;
    static const int TIMER_RELOAD = 65286;
    static const int TIMER_CRTL = 65287;
    static const int INT_FLAG = 65295;
    static const int SND_1_ENT = 65296;
    static const int SND_1_WAV_LEN = 65297;
    static const int SND_1_ENV = 65298;
    static const int SND_1_FREQ_KICK_LOWER = 65299;
    static const int SND_1_FREQ_KICK_UPPER = 65300;
    static const int SND_2_WAVE_LEN = 65302;
    static const int SND_2_ENV = 65303;
    static const int SND_2_FREQ_KICK_LOWER = 65304;
    static const int SND_2_FREQ_KICK_UPPER = 65305;
    static const int SND_3_ON_OFF = 65306;
    static const int SND_3_LEN = 65307;
    static const int SND_3_VOLUME = 65308;
    static const int SND_3_FREQ_KICK_LOWER = 65309;
    static const int SND_3_FREQ_KICK_UPPER = 65310;
    static const int SND_4_LEN = 65312;
    static const int SND_4_ENV = 65313;
    static const int SND_4_POLY_KICK_LOWER = 65314;
    static const int SND_4_POLY_KICK_UPPER = 65315;
    static const int SND_VOICE_INP = 65316;
    static const int SND_STEREO = 65317;
    static const int SND_STAT = 65318;
    static const int SND_BNK_10 = 65328;
    static const int SND_BNK_11 = 65329;
    static const int SND_BNK_12 = 65330;
    static const int SND_BNK_13 = 65331;
    static const int SND_BNK_14 = 65332;
    static const int SND_BNK_15 = 65333;
    static const int SND_BNK_16 = 65334;
    static const int SND_BNK_17 = 65335;
    static const int SND_BNK_20 = 65336;
    static const int SND_BNK_21 = 65337;
    static const int SND_BNK_22 = 65338;
    static const int SND_BNK_23 = 65339;
    static const int SND_BNK_24 = 65340;
    static const int SND_BNK_25 = 65341;
    static const int SND_BNK_26 = 65342;
    static const int SND_BNK_27 = 65343;
    static const int LCD_CTRL = 65344;
    static const int LCD_STAT = 65345;
    static const int LCD_SCROLL_Y = 65346;
    static const int LCD_SCROLL_X = 65347;
    static const int LCD_Y_LOC = 65348;
    static const int LCD_Y_COMP = 65349;
    static const int LCD_DMA = 65350;
    static const int LCD_BACK_PALETTE = 65351;
    static const int LCD_SPR0_PALETTE = 65352;
    static const int LCD_SPR1_PALETTE = 65353;
    static const int LCD_WIN_Y = 65354;
    static const int LCD_WIN_X = 65355;
    static const int CPU_SPEED_REG = 65357;
    static const int VRAM_BANK = 65359;
    static const int DMA_SRC_UPPER = 65361;
    static const int DMA_SRC_LOWER = 65362;
    static const int DMA_DST_UPPER = 65363;
    static const int DMA_DST_LOWER = 65364;
    static const int DMA_LEN_TYPE = 65365;
    static const int IR_PORT = 65366;
    static const int BGP_INDEX = 65384;
    static const int BGP_DATA = 65385;
    static const int OBP_INDEX = 65386;
    static const int OBP_DATA = 65387;
    static const int RAM_BANK = 65392;
    static const int INT_ENABLE = 65535;
    
    //const int DIK_UP = 0;
    //const int DIK_DOWN = 1;
    //const int DIK_LEFT = 2;
    //const int DIK_RIGHT = 3;
    //const int DIK_A = 4;
    //const int DIK_B = 5;
    //const int DIK_START = 6;
    //const int DIK_SELECT = 7;
 	   
 };

#endif