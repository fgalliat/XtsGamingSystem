/* =============
GameBoyCPU.cpp
============== */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#include <pthread.h>
#include <iostream>

#include "Logger.h"
#include "GameBoyVideo.h"
#include "GameBoyCPU.h"

// TMP - defined in main.cpp too !!!!!!
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define LT_GRAY 0xAAAAAA
#define GRAY 0x999999

//#define PAL_WIDTH 8
//#define PAL_HEIGHT 4
#define PAL_WIDTH 2
#define PAL_HEIGHT 2

const int GameBoyCPU::incAllValue[] = {
        4, 12, 8, 8, 4, 4, 8, 4, 20, 8,
        8, 8, 4, 4, 8, 4, 4, 12, 8, 8,
        4, 4, 8, 4, 12, 8, 8, 8, 4, 4,
        8, 4, 8, 12, 8, 8, 4, 4, 8, 4,
        8, 8, 8, 8, 4, 4, 8, 4, 8, 12,
        8, 8, 8, 8, 12, 4, 8, 8, 8, 8,
        4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4,
        4, 4, 4, 4, 8, 4, 4, 4, 4, 4,
        4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
        8, 4, 8, 8, 8, 8, 8, 8, 4, 8,
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4,
        4, 4, 4, 4, 8, 4, 4, 4, 4, 4,
        4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
        8, 4, 4, 4, 4, 4, 4, 4, 8, 4,
        4, 4, 4, 4, 4, 4, 8, 4, 4, 4,
        4, 4, 4, 4, 8, 4, 4, 4, 4, 4,
        4, 4, 8, 4, 4, 4, 4, 4, 4, 4,
        8, 4, 8, 12, 12, 16, 12, 16, 4, 16,
        8, 20, 12, 0, 12, 24, 4, 16, 8, 12,
        12, 0, 12, 16, 4, 16, 8, 20, 12, 0,
        12, 0, 4, 16, 12, 12, 8, 0, 0, 16,
        4, 16, 16, 4, 4, 0, 0, 0, 4, 16,
        12, 12, 8, 4, 0, 16, 4, 16, 12, 8,
        4, 4, 0, 0, 4, 16
    };

const int GameBoyCPU::incAllValueCB[] = {
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8, 8, 8, 8, 8,
        8, 8, 16, 8, 8, 8, 8, 8, 8, 8,
        16, 8, 8, 8, 8, 8, 8, 8, 16, 8,
        8, 8, 8, 8, 8, 8, 16, 8, 8, 8,
        8, 8, 8, 8, 16, 8
    };

GameBoyCPU::GameBoyCPU( bool* keystate ) {
	//GB_MEM = new char[0x10000];
  //VRAM = new char[16384];
  //PAGED_RAM = new char[32768];

  //int PAL_HEIGHT = 2; // ???
  //int PAL_WIDTH = 2; // ???
  
  DEFAULTS    = (int*)malloc( PAL_HEIGHT * PAL_WIDTH * sizeof(int) );
  BGPALETTE   = (int*)malloc( PAL_HEIGHT * PAL_WIDTH * sizeof(int) );
  OBJ0PALETTE = (int*)malloc( PAL_HEIGHT * PAL_WIDTH * sizeof(int) );
  OBJ1PALETTE = (int*)malloc( PAL_HEIGHT * PAL_WIDTH * sizeof(int) );

  int i=0;
  //for(int k=0; k < 8; k++) {
    DEFAULTS[i++] = WHITE;
    DEFAULTS[i++] = LT_GRAY;
    DEFAULTS[i++] = GRAY;
    DEFAULTS[i++] = BLACK;
  //}

  memcpy( BGPALETTE, DEFAULTS, sizeof(DEFAULTS) );
  memcpy( OBJ0PALETTE, DEFAULTS, sizeof(DEFAULTS) );
  memcpy( OBJ1PALETTE, DEFAULTS, sizeof(DEFAULTS) );

  createDAATable();
  createSwapTable();
  VIDEO = new GameBoyVideo(GB_MEM, VRAM);
  KEYS_PRESSED = keystate;
}

 void GameBoyCPU::tick() {
 	//printf("tick\n");
 	
   opCodeList1();
 }

 void GameBoyCPU::startThread() {
 	 /*
   if(instance == null) {
     APPLET_RUNNING = true;
     instance = new Thread(this);
     instance.start();
   }
   */
   APPLET_RUNNING = true;
   run(); //--> BEWARE it was a thread !!!
 }

 void GameBoyCPU::stopThread() {
   APPLET_RUNNING = false;
   //instance = null;
 }

 void GameBoyCPU::run() {
   //instance.setPriority(Thread.MAX_PRIORITY);
   while(APPLET_RUNNING)  {
     tick();
//            try { Thread.sleep(10); } catch(Exception ex) {}
   }
 }

 bool GameBoyCPU::loadRom(char* romName) {
   bool flag;

Logger_TMPDBUG("  0x01 loadRomCPU()");

   FILE* romInputStream = fopen( romName, "r" );
   if ( romInputStream == NULL ) {
   	 //Logger_debug("file not found %s\n", romName);
   	 Logger_debug("file not found\n");
   	 exit(1);
   }
Logger_TMPDBUG("  0x02 loadRomCPU()");

   int i = 0;
   int j = 0;
   int k = 32768;
   int l = 0;

   // casually remove path+ext from romName
   // but ... LATER
   //for(int i1 = 0; i1 < s.length(); i1++)
   //    if(s.charAt(i1) == '.')
   //      romName = s.substring(0, i1);

   unsigned char abyte0[1];
   int j1 = 0;
   
   do {
   	 //Logger_TMPDBUG("  0x02 loadRomCPU()");
     if(j1 >= 32768) {
     	 //Logger_debug("");
     	 Logger_TMPDBUG("  0x03 loadRomCPU() break");
       break;
     }

     if ( fread( &abyte0, 1, 1, romInputStream ) < 1 ) {
       Logger_debug("The rom file is smaller than it should be and may be corrupt");
       break;
     }
     //Logger_TMPDBUG("  0x04 loadRomCPU()");

     GB_MEM[j1] = abyte0[0];
     j1++;
     //Logger_TMPDBUG("  0x05 loadRomCPU()");
   } while(true);
   Logger_TMPDBUG("  0x05 loadRomCPU() loaded rom");

   printf( "GB MEM %d bytes long\n",GB_MEM_length );

   switch(GB_MEM[328]) {
    case 0: // '\0'
        i = 32768;
        break;

    case 1: // '\001'
        i = 0x10000;
        break;

    case 2: // '\002'
        i = 0x20000;
        break;

    case 3: // '\003'
        i = 0x40000;
        break;

    case 4: // '\004'
        i = 0x80000;
        break;

    case 5: // '\005'
        i = 0x100000;
        break;

    case 6: // '\006'
        i = 0x200000;
        break;

    case 7: // '\007'
        i = 0x400000;
        break;

    case 82: // 'R'
        i = 0x120000;
        break;

    case 83: // 'S'
        i = 0x140000;
        break;

    case 84: // 'T'
        i = 0x180000;
        break;

    default:
        Logger_debug("Unknown file size");
        break;
   }
   printf("  Cartridge size will be : %d bytes long\n", i);


   CART_ROM = (unsigned char*)malloc(i);
   for(int k1 = 0; k1 < 32768; k1++) {
     CART_ROM[k1] = GB_MEM[k1];
   }
   Logger_TMPDBUG(" ROM page loaded");

   //try {
       do {
           //if(rominputstream.read(abyte0, 0, 1) == -1)
           
           if ( fread( &abyte0, 1, 1, romInputStream ) < 1 ) {
               break;
           }
           
           if ( k >= i ) {
           	Logger_TMPDBUG(" The rom file is larger than it should be and may be corrupt");
           	break;
           }
           
           CART_ROM[k++] = abyte0[0];
           //if((k & 0xfff) == 0) {
             // romLoading.setPercentage((float)k / (float)i);
           //}
       } while(true);
   //}
   //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception) {
   //    Logger.debug("The rom file is larger than it should be and may be corrupt");
   //}
   fclose( romInputStream );
   //Logger_debug("Loaded %s\n", romName);
   Logger_debug("Loaded\n");

   switch(GB_MEM[329]) {
     case 0: // '\0'
         j = 0;
         break;

     case 1: // '\001'
         j = 1280;
         break;

     case 2: // '\002'
         j = 8192;
         break;

     case 3: // '\003'
         j = 32768;
         break;

     case 4: // '\004'
         j = 0x16000;
         break;

     default:
         Logger_debug("Unknown ram size");
         break;
   }

   if(j > 0) {
     CART_RAM = (unsigned char*)malloc(j);
     // --- try to read .sav file
     /*
     try {
         DataInputStream datainputstream = new DataInputStream((new URL(url+ romName + ".sav")).openStream());
         try {
							// ramLoading.setPercentage(0.0F);
             do {
                 if(datainputstream.read(abyte0, 0, 1) == -1)
                     break;
                 CART_RAM[l++] = (char)(abyte0[0] < 0 ? abyte0[0] + 256 : abyte0[0]);
                 if((l & 0xff) == 0) {
										// ramLoading.setPercentage((float)l / (float)j);
                 }
             } while(true);
         }
         catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception1)
         {
             Logger.debug("The ram file is larger than it should be and may be corrupt");
         }
         datainputstream.close();
     }
     catch(IOException ioexception1) { }
     */
   } else {
     CART_RAM = NULL;
   }

   if(GB_MEM[323] < '\200') {
   		/*
   		// ---- try to read the palette ----
     try {
         DataInputStream datainputstream1 = new DataInputStream((new URL(url+ romName + ".pal")).openStream());
         int l1;
         for(l1 = 0; datainputstream1.readLine() != null; l1++);
         datainputstream1 = new DataInputStream((new URL(url+ romName + ".pal")).openStream());
         for(int i2 = 0; i2 < l1; i2++) {
             String s1 = datainputstream1.readLine();
             for(int j2 = 0; j2 < s1.length(); j2++) {
                 if(s1.charAt(j2) != '=')
                     continue;
                 if(s1.substring(0, j2).equals("bg0"))
                     BGPALETTE[0][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("bg1"))
                     BGPALETTE[0][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("bg2"))
                     BGPALETTE[1][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("bg3"))
                     BGPALETTE[1][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj00"))
                     OBJ0PALETTE[0][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj01"))
                     OBJ0PALETTE[0][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj02"))
                     OBJ0PALETTE[1][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj03"))
                     OBJ0PALETTE[1][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj10"))
                     OBJ1PALETTE[0][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj11"))
                     OBJ1PALETTE[0][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj12"))
                     OBJ1PALETTE[1][0] = stringToColor(s1.substring(j2 + 1, s1.length()));
                 if(s1.substring(0, j2).equals("obj13"))
                     OBJ1PALETTE[1][1] = stringToColor(s1.substring(j2 + 1, s1.length()));
             }
         }

         datainputstream1.close();
     }
     catch(IOException ioexception2) {
         BGPALETTE[0][0] = DEFAULTS[0][0];
         BGPALETTE[0][1] = DEFAULTS[0][1];
         BGPALETTE[1][0] = DEFAULTS[1][0];
         BGPALETTE[1][1] = DEFAULTS[1][1];
         OBJ0PALETTE[0][0] = DEFAULTS[0][0];
         OBJ0PALETTE[0][1] = DEFAULTS[0][1];
         OBJ0PALETTE[1][0] = DEFAULTS[1][0];
         OBJ0PALETTE[1][1] = DEFAULTS[1][1];
         OBJ1PALETTE[0][0] = DEFAULTS[0][0];
         OBJ1PALETTE[0][1] = DEFAULTS[0][1];
         OBJ1PALETTE[1][0] = DEFAULTS[1][0];
         OBJ1PALETTE[1][1] = DEFAULTS[1][1];
     }
     */

     setBackPalette();
     setForePalette0();
     setForePalette1();
   } // end of pal instr

   flag = true;
   //}
   //catch(IOException ioexception) {
   //    flag = false;
   //}
   return flag;
 }



 void GameBoyCPU::fullReset() {
        AF = 4528;
        BC = 19;
        DE = 216;
        HL = 333;
        SP = 65534;
        PC = 256;
        A = getUpper(AF);
        F = getLower(AF);
        B = getUpper(BC);
        C = getLower(BC);
        D = getUpper(DE);
        E = getLower(DE);
        H = getUpper(HL);
        L = getLower(HL);
        for(int i = 0; i < GB_MEM_length - 32768; i++)
            GB_MEM[32768 + i] = '\0';

        for(int j = 0; j < VRAM_length; j++)
            VRAM[j] = '\0';

        for(int k = 0; k < PAGED_RAM_length; k++)
            PAGED_RAM[k] = '\0';

        MBC = 0;
        MBC_MODE = 0;
        RAM_PAGE = 0;
        ROM_PAGE = 0;
        TIMER = 0;
        TIMER_MAX = 0;
        CPU_CYCLES = 0;
        CPU_SPEED = 0;
        TIMER_CYCLES = 0;
        DIV = 0;
        SPR_PER_LINE = 0;
        IME = false;
        STOP = false;
        HALT = false;
        HALT_NEXT = false;
        TIMER_ON = false;
        RAM_ENABLE = false;
        RUMBLE_PACK = false;
        GB_MEM[65280] = '\317';
        GB_MEM[65281] = '\0';
        GB_MEM[65282] = '~';
        GB_MEM[65283] = '\377';
        GB_MEM[65284] = '\257';
        GB_MEM[65285] = '\0';
        GB_MEM[65286] = '\0';
        GB_MEM[65287] = '\370';
        GB_MEM[65288] = '\377';
        GB_MEM[65289] = '\377';
        GB_MEM[65290] = '\377';
        GB_MEM[65291] = '\377';
        GB_MEM[65292] = '\377';
        GB_MEM[65293] = '\377';
        GB_MEM[65294] = '\377';
        GB_MEM[65295] = '\0';
        GB_MEM[65296] = '\200';
        GB_MEM[65297] = '\277';
        GB_MEM[65298] = '\363';
        GB_MEM[65299] = '\377';
        GB_MEM[65300] = '\277';
        GB_MEM[65301] = '\377';
        GB_MEM[65302] = '?';
        GB_MEM[65303] = '\0';
        GB_MEM[65304] = '\377';
        GB_MEM[65305] = '\277';
        GB_MEM[65306] = '\177';
        GB_MEM[65307] = '\377';
        GB_MEM[65308] = '\237';
        GB_MEM[65309] = '\377';
        GB_MEM[65310] = '\277';
        GB_MEM[65310] = '\377';
        GB_MEM[65311] = '\377';
        GB_MEM[65312] = '\377';
        GB_MEM[65313] = '\0';
        GB_MEM[65314] = '\0';
        GB_MEM[65315] = '\277';
        GB_MEM[65316] = 'w';
        GB_MEM[65317] = '\363';
        GB_MEM[65318] = '\361';
        GB_MEM[65328] = '\006';
        GB_MEM[65329] = '\376';
        GB_MEM[65330] = '\016';
        GB_MEM[65331] = '\177';
        GB_MEM[65332] = '\0';
        GB_MEM[65333] = '\377';
        GB_MEM[65334] = 'X';
        GB_MEM[65335] = '\337';
        GB_MEM[65336] = '\0';
        GB_MEM[65337] = '\354';
        GB_MEM[65338] = '\0';
        GB_MEM[65339] = '\277';
        GB_MEM[65340] = '\f';
        GB_MEM[65341] = '\355';
        GB_MEM[65342] = '\003';
        GB_MEM[65343] = '\367';
        GB_MEM[65344] = '\221';
        GB_MEM[65345] = '\205';
        GB_MEM[65346] = '\0';
        GB_MEM[65347] = '\0';
        GB_MEM[65348] = '\0';
        GB_MEM[65349] = '\0';
        GB_MEM[65350] = '\0';
        GB_MEM[65351] = '\374';
        GB_MEM[65352] = '\377';
        GB_MEM[65353] = '\377';
        GB_MEM[65354] = '\0';
        GB_MEM[65355] = '\0';
        GB_MEM[65356] = '\377';
        GB_MEM[65357] = '~';
        GB_MEM[65358] = '\377';
        GB_MEM[65359] = '\376';
        GB_MEM[65360] = '\377';
        GB_MEM[65361] = '\0';
        GB_MEM[65362] = '\0';
        GB_MEM[65363] = '\0';
        GB_MEM[65364] = '\0';
        GB_MEM[65365] = '\377';
        GB_MEM[65366] = '\0';
        GB_MEM[65384] = '\300';
        GB_MEM[65385] = '\0';
        GB_MEM[65386] = '\301';
        GB_MEM[65387] = '\0';
        GB_MEM[65392] = '\370';
        GB_MEM[65535] = '\0';
        switch(GB_MEM[327]) {
          case 0: // '\0'
              MBC = 0;
              break;

          case 1: // '\001'
              MBC = 1;
              break;

          case 2: // '\002'
              MBC = 1;
              break;

          case 3: // '\003'
              MBC = 1;
              break;

          case 5: // '\005'
              MBC = 2;
              break;

          case 6: // '\006'
              MBC = 2;
              break;

          case 8: // '\b'
              MBC = 0;
              break;

          case 9: // '\t'
              MBC = 0;
              break;

          case 11: // '\013'
              MBC = 101;
              break;

          case 12: // '\f'
              MBC = 101;
              break;

          case 13: // '\r'
              MBC = 101;
              break;

          case 15: // '\017'
              MBC = 3;
              break;

          case 16: // '\020'
              MBC = 3;
              break;

          case 17: // '\021'
              MBC = 3;
              break;

          case 18: // '\022'
              MBC = 3;
              break;

          case 19: // '\023'
              MBC = 3;
              break;

          case 21: // '\025'
              MBC = 4;
              break;

          case 22: // '\026'
              MBC = 4;
              break;

          case 23: // '\027'
              MBC = 4;
              break;

          case 25: // '\031'
              MBC = 5;
              break;

          case 26: // '\032'
              MBC = 5;
              break;

          case 27: // '\033'
              MBC = 5;
              break;

          case 28: // '\034'
              MBC = 5;
              RUMBLE_PACK = true;
              break;

          case 29: // '\035'
              MBC = 5;
              RUMBLE_PACK = true;
              break;

          case 30: // '\036'
              MBC = 5;
              RUMBLE_PACK = true;
              break;

          case 31: // '\037'
              MBC = 0;
              break;

          case 253:
              MBC = 0;
              break;

          case 254:
              MBC = 3;
              break;

          case 255:
              MBC = 1;
              break;
        }

        for(int l = 0; l < 4; l++) {
            for(int i1 = 0; i1 < 8; i1++) {
                VIDEO->setBackColour(l, i1, WHITE);
                VIDEO->setForeColour(l, i1, WHITE);
            }
        }

        setLCDControl();
        setTimer();
 }

 GameBoyVideo* GameBoyCPU::getVideo() {
   return VIDEO;
 }

 int* GameBoyCPU::getBGPalette() {
   return BGPALETTE;
 }

 int* GameBoyCPU::getOBJ0Palette() {
   return OBJ0PALETTE;
 }

 int* GameBoyCPU::getOBJ1Palette() {
   return OBJ1PALETTE;
 }

 void GameBoyCPU::setBackPalette() {
   for(int i = 0; i < 4; i++)
     VIDEO->setBackColour(i, 0, BGPALETTE[ (BIT_get(GB_MEM[65351], (i << 1) + 1))*PAL_WIDTH+(BIT_get(GB_MEM[65351], i << 1))]);

 }

 void GameBoyCPU::setForePalette0() {
   for(int i = 0; i < 4; i++)
     VIDEO->setForeColour(i, 0, OBJ0PALETTE[ (BIT_get(GB_MEM[65352], (i << 1) + 1))*PAL_WIDTH+(BIT_get(GB_MEM[65352], i << 1))]);

 }

 void GameBoyCPU::setForePalette1() {
   for(int i = 0; i < 4; i++)
     VIDEO->setForeColour(i, 1, OBJ1PALETTE[ (BIT_get(GB_MEM[65353], (i << 1) + 1))*PAL_WIDTH+(BIT_get(GB_MEM[65353], i << 1))]);

 }

 // =========

 void GameBoyCPU::setLCDControl() {
        VIDEO->setWinPointers((GB_MEM[65344] & 0x40) <= 0 ? 6144 : 7168);
        VIDEO->setTileArea((GB_MEM[65344] & 0x10) <= 0 ? 2048 : 0);
        VIDEO->setBGPointers((GB_MEM[65344] & 8) <= 0 ? 6144 : 7168);
 }

 void GameBoyCPU::setTimer() {
   TIMER_ON = (GB_MEM[65287] & 4) > 0;
   TIMER_MAX = (GB_MEM[65287] & 2) <= 0 ? ((int) ((GB_MEM[65287] & '\001') <= 0 ? 16 : 1024)) : (GB_MEM[65287] & '\001') <= 0 ? 64 : 256;
 }

 void GameBoyCPU::handleGBInput()
    {
        GB_MEM[65280] &= '\360';
        if(GB_MEM[65280] == '0')
            GB_MEM[65280] = '?';
        if(GB_MEM[65280] == ' ')
        {
            if(!KEYS_PRESSED[1])
                GB_MEM[65280] |= '\b';
            if(!KEYS_PRESSED[0])
                GB_MEM[65280] |= '\004';
            if(!KEYS_PRESSED[2])
                GB_MEM[65280] |= '\002';
            if(!KEYS_PRESSED[3])
                GB_MEM[65280] |= '\001';
        } else
        if(GB_MEM[65280] == '\020')
        {
            if(!KEYS_PRESSED[6])
                GB_MEM[65280] |= '\b';
            if(!KEYS_PRESSED[7])
                GB_MEM[65280] |= '\004';
            if(!KEYS_PRESSED[5])
                GB_MEM[65280] |= '\002';
            if(!KEYS_PRESSED[4])
                GB_MEM[65280] |= '\001';
        }
    }

    unsigned char GameBoyCPU::getUpper(int i) {
        return (unsigned char)(i >> 8 & 0xff);
    }

    unsigned char GameBoyCPU::getLower(int i) {
        return (unsigned char)(i & 0xff);
    }

    int GameBoyCPU::combine(unsigned char c, unsigned char c1) {
        return c << 8 | c1;
    }


    unsigned char GameBoyCPU::getMem(int i) {
        i &= 0xffff;
        if(MBC > 0 && i >= 16384 && i < 32768) {
            //try {
                unsigned char c = CART_ROM[(i - 16384) + (ROM_PAGE << 14)];
                return c;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception)
            //{
            //    GB_MEM[65357] = '\0';
            //}
            //STOP = true;
            //Logger_debug("Attempted array out of bounds access in CART_ROM at rom page: " + Integer.toHexString(ROM_PAGE));
            //char c5 = '\0';
            //return c5;
        }
        if(i >= 32768 && i < 40960) {
            //try {
                char c1 = VRAM[(i - 32768) + ((GB_MEM[65359] & '\001') << 13)];
                return c1;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception1) {
            //    GB_MEM[65357] = '\0';
            //}
            //STOP = true;
            //Logger.debug("Attempted array out of bounds access in VRAM at vram page: " + Integer.toString(GB_MEM[65359] & '\001'));
            //char c6 = '\0';
            //return c6;
        }
        if(MBC > 0 && i >= 40960 && i < 49152 && RAM_ENABLE) {
            //try {
                char c2 = CART_RAM[(i - 40960) + (RAM_PAGE << 13)];
                return c2;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception2) {
            //    GB_MEM[65357] = '\0';
            //}
            //STOP = true;
            //Logger.debug("Attempted array out of bounds access in CART_RAM at ram page: " + Integer.toHexString(RAM_PAGE));
            //char c7 = '\0';
            //return c7;
        }
        if(i >= 53248 && i < 57344) {
            //try {
                char c3 = PAGED_RAM[(i - 53248) + ((GB_MEM[65392] & 7) << 12)];
                return c3;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception3) {
            //    GB_MEM[65357] = '\0';
            //}
            //STOP = true;
            //Logger.debug("Attempted array out of bounds access in PAGED_RAM at ram bank: " + Integer.toHexString(65392));
            //char c8 = '\0';
            //return c8;
        }

        //try {
            char c4 = GB_MEM[i];
            return c4;
        //}
        //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception4) {
        //    GB_MEM[65357] = '\0';
        //}
        //STOP = true;
        //Logger.debug("Attempted array out of bounds access in GB_MEM at location: " + Integer.toHexString(i));
        //char c9 = '\0';
        //return c9;
    }

    int GameBoyCPU::getMemNN() {
        PC += 2;
        return getMem(PC - 1) << 8 | getMem(PC - 2);
    }

    int GameBoyCPU::getSignedMemN() {
        tempChar = getMem(PC++);
        return tempChar <= '\177' ? tempChar : tempChar - 256;
    }

    void GameBoyCPU::setMem(int i, unsigned char c) {
        if(i < 32768) {
            if(MBC == 1) {
                if(i < 8192)
                    RAM_ENABLE = (c & 0xf) == 10;
                else
                if(i >= 8192 && i < 16384)
                    ROM_PAGE = c & 0x1f;
                else
                if(MBC_MODE == 1 && i >= 16384 && i < 24576)
                    RAM_PAGE = c & 3;
                else
                if(MBC_MODE == 0 && i >= 16384 && i < 24576)
                    ROM_PAGE = ROM_PAGE & 7 | (c & 3) << 3;
                else
                if(i >= 24576 && i < 32768)
                    MBC_MODE = c & '\001';
            } else
            if(MBC == 2)
            {
                if(i >= 8192 && i < 16384)
                    ROM_PAGE = c & 0xf;
            } else
            if(MBC == 3)
            {
                if(i < 8192)
                    RAM_ENABLE = (c & 0xf) == 10;
                else
                if(i >= 8192 && i < 16384)
                    ROM_PAGE = c & 0x7f;
                else
                if(i >= 16384 && i < 24576)
                    RAM_PAGE = c & 3;
            } else
            if(MBC == 5)
                if(i < 8192)
                    RAM_ENABLE = (c & 0xf) == 10;
                else
                if(i >= 8192 && i < 12288)
                    ROM_PAGE = ROM_PAGE & 0x100 | c & 0xff;
                else
                if(i >= 12288 && i < 16384)
                    ROM_PAGE |= (c & '\001') << 8;
                else
                if(i >= 16384 && i < 24576)
                    RAM_PAGE = RUMBLE_PACK ? c & 3 : c & 0xf;
        } else
        if(i == 65348)
            GB_MEM[65348] = '\0';
        else
        if(i == 65365 && GB_MEM[323] >= '\200')
        {
            GB_MEM[65365] = c;
            for(int j = 0; j < ((c & 0x7f) + 1) * 16; j++)
                setMem((GB_MEM[65363] << 8 | GB_MEM[65364]) + j, getMem((GB_MEM[65361] << 8 | GB_MEM[65362]) + j));

            GB_MEM[65365] &= '\200';
        } else
        if(i == 65284)
            GB_MEM[65284] = '\0';
        else
        if(i == 65344)
        {
            GB_MEM[65344] = c;
            setLCDControl();
        } else
        if(i == 65350)
        {
            GB_MEM[65350] = c;
            for(int k = 0; k < 160; k++)
                GB_MEM[65024 + k] = getMem((GB_MEM[65350] << 8) + k);

        } else
        if(i == 65280)
        {
            GB_MEM[65280] = c;
            handleGBInput();
        } else
        if(i == 65287)
        {
            GB_MEM[65287] = c;
            setTimer();
        } else
        if(i == 65351 && GB_MEM[323] < '\200')
        {
            GB_MEM[65351] = c;
            setBackPalette();
        } else
        if(i == 65352 && GB_MEM[323] < '\200')
        {
            GB_MEM[65352] = c;
            setForePalette0();
        } else
        if(i == 65353 && GB_MEM[323] < '\200')
        {
            GB_MEM[65353] = c;
            setForePalette1();
        } else
        if(i == 65385 && GB_MEM[323] >= '\200')
        {
            GB_MEM[65385] = c;
            int l = (GB_MEM[65384] & 0x38) >> 3;
            int j1 = (GB_MEM[65384] & 6) >> 1;
            VIDEO->setBackColour(j1, l, getGBColour((GB_MEM[65384] & '\001') <= 0 ? rgb2GBUpper(VIDEO->getBackColour(j1, l)) | c : rgb2GBLower(VIDEO->getBackColour(j1, l)) | c << (GB_MEM[65384] & '\001') * 8));
            if((GB_MEM[65384] & 0x80) > 0)
                if((GB_MEM[65384] & 0x3f) != 63)
                    GB_MEM[65384]++;
                else
                    GB_MEM[65384] &= '\300';
        } else
        if(i == 65387 && GB_MEM[323] >= '\200')
        {
            GB_MEM[65387] = c;
            int i1 = (GB_MEM[65386] & 0x38) >> 3;
            int k1 = (GB_MEM[65386] & 6) >> 1;
            VIDEO->setForeColour(k1, i1, getGBColour((GB_MEM[65386] & '\001') <= 0 ? rgb2GBUpper(VIDEO->getForeColour(k1, i1)) | c : rgb2GBLower(VIDEO->getForeColour(k1, i1)) | c << (GB_MEM[65386] & '\001') * 8));
            if((GB_MEM[65386] & 0x80) > 0)
                if((GB_MEM[65386] & 0x3f) != 63)
                    GB_MEM[65386]++;
                else
                    GB_MEM[65386] &= '\300';
        } else
        if(i >= 32768 && i < 40960)
            VRAM[(i - 32768) + 8192 * (GB_MEM[65359] & '\001')] = c;
        else
        if(i >= 40960 && i < 49152 && RAM_ENABLE)
            //try {
                CART_RAM[(i - 40960) + (RAM_PAGE << 13)] = c;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception) {
            //    Logger.debug("Attempted array out of bounds write in CART_RAM at location: " + Integer.toHexString((i - 40960) + (RAM_PAGE << 13)));
            ///}
        else
        if(i >= 49152 && i < 53248)
        {
            GB_MEM[i] = c;
            GB_MEM[i + 8192] = c;
        } else
        if(i >= 53248 && i < 57344)
        {
            PAGED_RAM[(i - 53248) + 4096 * (GB_MEM[65392] & 7)] = c;
            if(i < 56832)
                GB_MEM[i + 8192] = c;
        } else
        if(i >= 57344 && i < 61440)
        {
            GB_MEM[i] = c;
            GB_MEM[i - 8192] = c;
        } else
        if(i >= 61440 && i < 65024)
        {
            GB_MEM[i] = c;
            PAGED_RAM[(i - 61440) + 4096 * (GB_MEM[65392] & 7)] = c;
        } else
        {
            //try {
                GB_MEM[i] = c;
            //}
            //catch(ArrayIndexOutOfBoundsException arrayindexoutofboundsexception1) {
            //    Logger.debug("Attempted array out of bounds write in GB_MEM at location: " + Integer.toHexString(i));
            //}
        }
    }

    int GameBoyCPU::getGBColour(int i)
    {
        //return Color.argb(255, (i & 0x1f) * 8, (i >> 5 & 0x1f) * 8, (i >> 10 & 0x1f) * 8);
        return (255<<24)+(((i & 0x1f) * 8)<<16)+(((i >> 5 & 0x1f) * 8)<<8)+((i >> 10 & 0x1f) * 8);
    }

    int GameBoyCPU::rgb2GBUpper(int color)
    {
    	return (128 / 8 << 10) + (128 / 8 << 5) & 0x7f00;
        //return (color.getBlue() / 8 << 10) + (color.getGreen() / 8 << 5) & 0x7f00;
    }

    int GameBoyCPU::rgb2GBLower(int color)
    {
    	   return (128 / 8 << 5) + 128 / 8 & 0xff;
//        return (color.getGreen() / 8 << 5) + color.getRed() / 8 & 0xff;
    }

  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    void GameBoyCPU::ADC(unsigned char c) {
        tempOpCodeRegister = A + c + ((F & 0x10) <= 0 ? 0 : 1);
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | ((A & 0xf) + (c & 0xf) + ((F & 0x10) <= 0 ? 0 : 1) <= 15 ? 0 : 0x20) | (tempOpCodeRegister <= 255 ? 0 : 0x10));
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    void GameBoyCPU::ADD(unsigned char c) {
        tempOpCodeRegister = A + c;
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | ((A & 0xf) + (c & 0xf) <= 15 ? 0 : 0x20) | (tempOpCodeRegister <= 255 ? 0 : 0x10));
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    int GameBoyCPU::ADD16(int i, int j) {
        tempOpCodeRegister = i + j;
        F = (unsigned char)(((tempOpCodeRegister & 0xffff) != 0 ? 0 : 0x80) | ((A & 0xfff) + (j & 0xfff) <= 4095 ? 0 : 0x20) | (tempOpCodeRegister <= 65535 ? 0 : 0x10));
        AF = combine(A, F);
        return tempOpCodeRegister & 0xffff;
    }

    int GameBoyCPU::ADDSP(int i) {
        tempOpCodeRegister = SP + i;
        F = (unsigned char)(tempOpCodeRegister <= 65535 ? 0 : 16);
        AF = combine(A, F);
        return tempOpCodeRegister & 0xffff;
    }

    void GameBoyCPU::AND(unsigned char c) {
        A &= c;
        A &= '\377';
        F = (unsigned char)((A != '\0' ? 0 : 0x80) | 0x20);
        AF = combine(A, F);
    }

    void GameBoyCPU::BIT(int i, unsigned char c) {
        if((c & 1 << i) > 0)
            //F &= '\uFF7F';
            F &= 0x7F;
        else
            F |= '\200';
        //F &= '\uFFBF';
        F &= 0xBF;
        F |= ' ';
        AF = combine(A, F);
    }

    int GameBoyCPU::BIT_get(int i, int j) {
        return (i & 1 << j) <= 0 ? 0 : 1;
    }

    void GameBoyCPU::CALL() {
        PUSH(PC + 2);
        PC = getMemNN();
    }

    void GameBoyCPU::CCF() {
        //F &= '\uFFBF';
        F &= 0xBF;
        //F &= '\uFFDF';
        F &= 0xDF;
        F ^= '\020';
        AF = combine(A, F);
    }

    void GameBoyCPU::CP(unsigned char c) {
        F = (unsigned char)((A != c ? 0 : 0x80) | 0x40 | ((A & 0xf) >= (c & 0xf) ? 0 : 0x20) | (A >= c ? 0 : 0x10));
        AF = combine(A, F);
    }

    void GameBoyCPU::CPL() {
        A ^= '\377';
        A &= '\377';
        F |= '@';
        F |= ' ';
        AF = combine(A, F);
    }

    void GameBoyCPU::DAA() {
        tempOpCodeRegister = A;
        if((F & 0x10) > 0)
            tempOpCodeRegister |= 0x100;
        if((F & 0x20) > 0)
            tempOpCodeRegister |= 0x200;
        if((F & 0x40) > 0)
            tempOpCodeRegister |= 0x400;
        A = getUpper(DAA_TABLE[tempOpCodeRegister]);
        if((DAA_TABLE[tempOpCodeRegister] & 0x40) > 0)
            F |= '\200';
        else
            //F &= '\uFF7F';
            F &= 0x7F;
        //F &= '\uFFDF';
        F &= 0xDF;
        if((DAA_TABLE[tempOpCodeRegister] & 1) > 0)
            F |= '\020';
        else
            //F &= '\uFFEF';
            F &= 0xEF;
        AF = combine(A, F);
    }

    unsigned char GameBoyCPU::DEC(unsigned char c) {
        if(c == '\0')
            c = '\377';
        else
            c--;
        if(c == '\0')
            F |= '\200';
        else
            //F &= '\uFF7F';
            F &= 0x7F;
        F |= '@';
        if((c & 0xf) == 15)
            F |= ' ';
        else
            //F &= '\uFFDF';
            F &= 0xDF;
        AF = combine(A, F);
        return c;
    }

    int GameBoyCPU::DEC16(int i) {
        if(i == 0)
            i = 65535;
        else
            i--;
        return i;
    }

    unsigned char GameBoyCPU::INC(unsigned char c) {
        if(c == '\377')
            c = '\0';
        else
            c++;
        if(c == '\0')
            F |= '\200';
        else
            //F &= '\uFF7F';
            F &= 0x7F;
        //F &= '\uFFBF';
        F &= 0xBF;
        if((c & 0xf) > 0)
            //F &= '\uFFDF';
            F &= 0xDF;
        else
            F |= ' ';
        AF = combine(A, F);
        return c;
    }

    int GameBoyCPU::INC16(int i) {
        if(i == 65535)
            i = 0;
        else
            i++;
        return i;
    }

    void GameBoyCPU::JP() {
        PC = getMemNN();
    }

    void GameBoyCPU::JR() {
        PC = getSignedMemN() + PC;
    }

    void GameBoyCPU::OR(unsigned char c) {
        A |= c;
        A &= '\377';
        F = (unsigned char)(A != '\0' ? 0 : 128);
        AF = combine(A, F);
    }

    int GameBoyCPU::POP() {
        SP += 2;
        return getMem(SP - 1) << 8 | getMem(SP - 2);
    }

    void GameBoyCPU::PUSH(int i) {
        setMem(--SP, getUpper(i));
        setMem(--SP, getLower(i));
    }

    unsigned char GameBoyCPU::RES(int i, unsigned char c) {
        return getLower(c & ~(1 << i));
    }

    void GameBoyCPU::RET() {
        PC = POP();
    }

    unsigned char GameBoyCPU::RL(unsigned char c) {
        tempOpCodeRegister = c << 1 | ((F & 0x10) <= 0 ? 0 : 1);
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | (tempOpCodeRegister <= 255 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    void GameBoyCPU::RLA() {
        tempOpCodeRegister = A << 1 | ((F & 0x10) <= 0 ? 0 : 1);
        F = (unsigned char)(tempOpCodeRegister <= 255 ? 0 : 16);
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    unsigned char GameBoyCPU::RLC(unsigned char c) {
        tempOpCodeRegister = c << 1 | BIT_get(c, 7);
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | (tempOpCodeRegister <= 255 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    void GameBoyCPU::RLCA() {
        tempOpCodeRegister = A << 1 | BIT_get(A, 7);
        F = (unsigned char)(tempOpCodeRegister <= 255 ? 0 : 16);
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    unsigned char GameBoyCPU::RR(unsigned char c) {
        tempOpCodeRegister = c >> 1 | ((F & 0x10) <= 0 ? 0 : 1) << 7;
        F = (unsigned char)((tempOpCodeRegister != 0 ? 0 : 0x80) | ((c & '\001') <= 0 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    void GameBoyCPU::RRA() {
        tempOpCodeRegister = A >> 1 | ((F & 0x10) <= 0 ? 0 : 1) << 7;
        F = (unsigned char)((A & '\001') <= 0 ? 0 : 16);
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    unsigned char GameBoyCPU::RRC(unsigned char c) {
        tempOpCodeRegister = c >> 1 | BIT_get(c, 0) << 7;
        F = (unsigned char)((tempOpCodeRegister != 0 ? 0 : 0x80) | ((c & '\001') <= 0 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    void GameBoyCPU::RRCA() {
        tempOpCodeRegister = A >> 1 | BIT_get(A, 0) << 7;
        F = (unsigned char)((A & '\001') <= 0 ? 0 : 16);
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    void GameBoyCPU::RST(int i) {
        PUSH(PC);
        PC = i;
    }

    void GameBoyCPU::SBC(unsigned char c) {
        tempOpCodeRegister = A - c - ((F & 0x10) <= 0 ? 0 : 1);
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | 0x40 | ((A & 0xf) >= (c - ((F & 0x10) <= 0 ? 0 : 1) & 0xf) ? 0 : 0x20) | (tempOpCodeRegister >= 0 ? 0 : 0x10));
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    void GameBoyCPU::SUB(unsigned char c) {
        tempOpCodeRegister = A - c;
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | 0x40 | ((A & 0xf) >= (c & 0xf) ? 0 : 0x20) | (tempOpCodeRegister >= 0 ? 0 : 0x10));
        A = getLower(tempOpCodeRegister);
        AF = combine(A, F);
    }

    void GameBoyCPU::SCF() {
        F |= '\020';
        //F &= '\uFFBF';
        F &= 0xBF;
        //F &= '\uFFDF';
        F &= 0xDF;
        AF = combine(A, F);
    }

    unsigned char GameBoyCPU::SET(int i, unsigned char c) {
        return getLower(c | 1 << i);
    }

    unsigned char GameBoyCPU::SLA(unsigned char c) {
        tempOpCodeRegister = c << 1;
        F = (unsigned char)(((tempOpCodeRegister & 0xff) != 0 ? 0 : 0x80) | (tempOpCodeRegister <= 255 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    unsigned char GameBoyCPU::SRA(unsigned char c) {
        tempOpCodeRegister = c >> 1 | c & 0x80;
        F = (unsigned char)((tempOpCodeRegister != 0 ? 0 : 0x80) | ((c & '\001') <= 0 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    unsigned char GameBoyCPU::SRL(unsigned char c) {
        tempOpCodeRegister = c >> 1;
        F = (unsigned char)((tempOpCodeRegister != 0 ? 0 : 0x80) | ((c & '\001') <= 0 ? 0 : 0x10));
        AF = combine(A, F);
        return getLower(tempOpCodeRegister);
    }

    unsigned char GameBoyCPU::SWAP(unsigned char c) {
        F = (unsigned char)(c != '\0' ? 0 : 128);
        AF = combine(A, F);
        printf("(CPU)used SWAP table\n");
        return SWAP_TABLE[c];
    }

    void GameBoyCPU::XOR(unsigned char c) {
        A ^= c;
        A &= '\377';
        F = (unsigned char)(A != '\0' ? 0 : 128);
        AF = combine(A, F);
    }
  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


  void GameBoyCPU::incAll(int i) {
        CPU_CYCLES += i;
        DIV += i;
        if(DIV > 256 << CPU_SPEED) {
            DIV = 0;
            GB_MEM[65284]++;
            if(GB_MEM[65284] == '\377')
                GB_MEM[65284] = '\0';
        }
        if(TIMER_ON) {
            TIMER += i;
            if(TIMER > TIMER_MAX << CPU_SPEED) {
                TIMER = 0;
                GB_MEM[65285]++;
                if(GB_MEM[65285] == '\377') {
                    GB_MEM[65285] = '\0';
                    GB_MEM[65295] |= '\004';
                }
            }
        }
    }

 void GameBoyCPU::opCodeList1() {
        if(STOP) {
            if((GB_MEM[65357] & '\001') > 0)
            {
                GB_MEM[65357] |= '\200';
                CPU_SPEED ^= 1;
                STOP = false;
            }
            return;
        }
        
        //printf( "cycle:%d\n", CPU_CYCLES );
        
        
        if(CPU_CYCLES > 456 << CPU_SPEED)
        {
        	
        //	printf( "cycle:%d > 456 \n", CPU_CYCLES );
        	
            CPU_CYCLES = 0;
            if(GB_MEM[65348] == '\231')
                GB_MEM[65348] = '\0';
            else
                GB_MEM[65348]++;
            if(GB_MEM[65348] == GB_MEM[65349])
            {
                GB_MEM[65345] |= '\004';
                if((GB_MEM[65345] & 0x40) > 0)
                    GB_MEM[65295] |= '\002';
            } else
            {
                GB_MEM[65345] &= '\373';
            }
        }
        
        printf( "X %d %d \n", GB_MEM[65348], '\220');
        if(GB_MEM[65348] < '\220')
        
        //printf( "X %d %d \n", GB_MEM[65348], 144);
        //if(GB_MEM[65348] < 144)
        {
        	
	printf( "A \n");	
            if(CPU_CYCLES < 81 << CPU_SPEED && (GB_MEM[65345] & 3) != 2)
            {
  
  printf( "B \n");	
                GB_MEM[65345] = (char)(GB_MEM[65345] & 0xfc | 2);
                if((GB_MEM[65345] & 0x20) > 0)
                    GB_MEM[65295] |= '\002';
            } else
            if(CPU_CYCLES >= 81 << CPU_SPEED && CPU_CYCLES < 174 + 12 * SPR_PER_LINE << CPU_SPEED && (GB_MEM[65345] & 3) != 3)
            {
            	
printf( "C \n");	
                SPR_PER_LINE = VIDEO->drawLine();
                GB_MEM[65345] = (char)(GB_MEM[65345] & 0xfc | 3);
            } else
            if(CPU_CYCLES >= 174 + 12 * SPR_PER_LINE << CPU_SPEED && (GB_MEM[65345] & 3) != 0)
            {
                GB_MEM[65345] &= '\374';
                if((GB_MEM[65345] & 8) > 0)
                    GB_MEM[65295] |= '\002';
            }
        } else
        if(GB_MEM[65348] >= '\220' && (GB_MEM[65345] & 3) != 1)
        {
            VIDEO->refresh();
            GB_MEM[65345] = (char)(GB_MEM[65345] & 0xfc | 1);
            if((GB_MEM[65345] & 0x10) > 0)
                GB_MEM[65295] |= '\002';
            GB_MEM[65295] |= '\001';
        }
        if(IME && GB_MEM[65295] > '\0')
            if((GB_MEM[65295] & '\001') > 0 && (GB_MEM[65535] & '\001') > 0)
            {
                HALT = false;
                PUSH(PC);
                PC = 64;
                IME = false;
                //GB_MEM[65295] &= '\uFFFE';
                GB_MEM[65295] &= 0xFE;
            } else
            if((GB_MEM[65295] & 2) > 0 && (GB_MEM[65535] & 2) > 0)
            {
                HALT = false;
                PUSH(PC);
                PC = 72;
                IME = false;
                //GB_MEM[65295] &= '\uFFFD';
                GB_MEM[65295] &= 0xFD;
            } else
            if((GB_MEM[65295] & 4) > 0 && (GB_MEM[65535] & 4) > 0)
            {
                HALT = false;
                PUSH(PC);
                PC = 80;
                IME = false;
                //GB_MEM[65295] &= '\uFFFB';
                GB_MEM[65295] &= 0xFB;
            } else
            if((GB_MEM[65295] & 8) > 0 && (GB_MEM[65535] & 8) > 0)
            {
                HALT = false;
                PUSH(PC);
                PC = 88;
                IME = false;
                //GB_MEM[65295] &= '\uFFF7';
                GB_MEM[65295] &= 0xF7;
            } else
            if((GB_MEM[65295] & 0x10) > 0 && (GB_MEM[65535] & 0x10) > 0)
            {
                HALT = false;
                PUSH(PC);
                PC = 96;
                IME = false;
                //GB_MEM[65295] &= '\uFFEF';
                GB_MEM[65295] &= 0xEF;
            }
        if(PC > 65535)
        {
            GB_MEM[65357] = '\0';
            STOP = true;
            Logger_debug("   Program Counter out of Memory!!!\n");
            return;
        }
        if(HALT)
        {
            incAll(4);
            return;
        }
        opCode = getMem(PC++);
        incAll(incAllValue[opCode]);
        
        int i;
        switch(opCode)
        {
        case 0: // '\0'
            break;

        case 1: // '\001'
            BC = getMemNN();
            B = getUpper(BC);
            C = getLower(BC);
            break;

        case 2: // '\002'
            setMem(BC, A);
            break;

        case 3: // '\003'
            BC = INC16(BC);
            B = getUpper(BC);
            C = getLower(BC);
            break;

        case 4: // '\004'
            B = INC(B);
            BC = combine(B, C);
            break;

        case 5: // '\005'
            B = DEC(B);
            BC = combine(B, C);
            break;

        case 6: // '\006'
            B = getMem(PC++);
            BC = combine(B, C);
            break;

        case 7: // '\007'
            RLCA();
            break;

        case 8: // '\b'
            i = getMemNN();
            setMem(i, getLower(SP));
            setMem(i + 1, getUpper(SP));
            break;

        case 9: // '\t'
            HL = ADD16(HL, BC);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 10: // '\n'
            A = getMem(BC);
            AF = combine(A, F);
            break;

        case 11: // '\013'
            BC = DEC16(BC);
            B = getUpper(BC);
            C = getLower(BC);
            break;

        case 12: // '\f'
            C = INC(C);
            BC = combine(B, C);
            break;

        case 13: // '\r'
            C = DEC(C);
            BC = combine(B, C);
            break;

        case 14: // '\016'
            C = getMem(PC++);
            BC = combine(B, C);
            break;

        case 15: // '\017'
            RRCA();
            break;

        case 16: // '\020'
            STOP = true;
            break;

        case 17: // '\021'
            DE = getMemNN();
            D = getUpper(DE);
            E = getLower(DE);
            break;

        case 18: // '\022'
            setMem(DE, A);
            break;

        case 19: // '\023'
            DE = INC16(DE);
            D = getUpper(DE);
            E = getLower(DE);
            break;

        case 20: // '\024'
            D = INC(D);
            DE = combine(D, E);
            break;

        case 21: // '\025'
            D = DEC(D);
            DE = combine(D, E);
            break;

        case 22: // '\026'
            D = getMem(PC++);
            DE = combine(D, E);
            break;

        case 23: // '\027'
            RLA();
            break;

        case 24: // '\030'
            JR();
            break;

        case 25: // '\031'
            HL = ADD16(HL, DE);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 26: // '\032'
            A = getMem(DE);
            AF = combine(A, F);
            break;

        case 27: // '\033'
            DE = DEC16(DE);
            D = getUpper(DE);
            E = getLower(DE);
            break;

        case 28: // '\034'
            E = INC(E);
            DE = combine(D, E);
            break;

        case 29: // '\035'
            E = DEC(E);
            DE = combine(D, E);
            break;

        case 30: // '\036'
            E = getMem(PC++);
            DE = combine(D, E);
            break;

        case 31: // '\037'
            RRA();
            break;

        case 32: // ' '
            if((F & 0x80) == 0)
            {
                incAll(4);
                JR();
            } else
            {
                PC++;
            }
            break;

        case 33: // '!'
            HL = getMemNN();
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 34: // '"'
            setMem(HL, A);
            HL = INC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 35: // '#'
            HL = INC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 36: // '$'
            H = INC(H);
            HL = combine(H, L);
            break;

        case 37: // '%'
            H = DEC(H);
            HL = combine(H, L);
            break;

        case 38: // '&'
            H = getMem(PC++);
            HL = combine(H, L);
            break;

        case 39: // '\''
            DAA();
            break;

        case 40: // '('
            if((F & 0x80) > 0)
            {
                incAll(4);
                JR();
            } else
            {
                PC++;
            }
            break;

        case 41: // ')'
            HL = ADD16(HL, HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 42: // '*'
            A = getMem(HL);
            AF = combine(A, F);
            HL = INC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 43: // '+'
            HL = DEC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 44: // ','
            L = INC(L);
            HL = combine(H, L);
            break;

        case 45: // '-'
            L = DEC(L);
            HL = combine(H, L);
            break;

        case 46: // '.'
            L = getMem(PC++);
            HL = combine(H, L);
            break;

        case 47: // '/'
            CPL();
            break;

        case 48: // '0'
            if((F & 0x10) == 0)
            {
                incAll(4);
                JR();
            } else
            {
                PC++;
            }
            break;

        case 49: // '1'
            SP = getMemNN();
            break;

        case 50: // '2'
            setMem(HL, A);
            HL = DEC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 51: // '3'
            SP = INC16(SP);
            break;

        case 52: // '4'
            setMem(HL, INC(getMem(HL)));
            break;

        case 53: // '5'
            setMem(HL, DEC(getMem(HL)));
            break;

        case 54: // '6'
            setMem(HL, getMem(PC++));
            break;

        case 55: // '7'
            SCF();
            break;

        case 56: // '8'
            if((F & 0x10) > 0)
            {
                incAll(4);
                JR();
            } else
            {
                PC++;
            }
            break;

        case 57: // '9'
            HL = ADD16(HL, SP);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 58: // ':'
            A = getMem(HL);
            AF = combine(A, F);
            HL = DEC16(HL);
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 59: // ';'
            SP = DEC16(SP);
            break;

        case 60: // '<'
            A = INC(A);
            AF = combine(A, F);
            break;

        case 61: // '='
            A = DEC(A);
            AF = combine(A, F);
            break;

        case 62: // '>'
            A = getMem(PC++);
            AF = combine(A, F);
            break;

        case 63: // '?'
            CCF();
            break;

        case 64: // '@'
            B = B;
            BC = combine(B, C);
            break;

        case 65: // 'A'
            B = C;
            BC = combine(B, C);
            break;

        case 66: // 'B'
            B = D;
            BC = combine(B, C);
            break;

        case 67: // 'C'
            B = E;
            BC = combine(B, C);
            break;

        case 68: // 'D'
            B = H;
            BC = combine(B, C);
            break;

        case 69: // 'E'
            B = L;
            BC = combine(B, C);
            break;

        case 70: // 'F'
            B = getMem(HL);
            BC = combine(B, C);
            break;

        case 71: // 'G'
            B = A;
            BC = combine(B, C);
            break;

        case 72: // 'H'
            C = B;
            BC = combine(B, C);
            break;

        case 73: // 'I'
            C = C;
            BC = combine(B, C);
            break;

        case 74: // 'J'
            C = D;
            BC = combine(B, C);
            break;

        case 75: // 'K'
            C = E;
            BC = combine(B, C);
            break;

        case 76: // 'L'
            C = H;
            BC = combine(B, C);
            break;

        case 77: // 'M'
            C = L;
            BC = combine(B, C);
            break;

        case 78: // 'N'
            C = getMem(HL);
            BC = combine(B, C);
            break;

        case 79: // 'O'
            C = A;
            BC = combine(B, C);
            break;

        case 80: // 'P'
            D = B;
            DE = combine(D, E);
            break;

        case 81: // 'Q'
            D = C;
            DE = combine(D, E);
            break;

        case 82: // 'R'
            D = D;
            DE = combine(D, E);
            break;

        case 83: // 'S'
            D = E;
            DE = combine(D, E);
            break;

        case 84: // 'T'
            D = H;
            DE = combine(D, E);
            break;

        case 85: // 'U'
            D = L;
            DE = combine(D, E);
            break;

        case 86: // 'V'
            D = getMem(HL);
            DE = combine(D, E);
            break;

        case 87: // 'W'
            D = A;
            DE = combine(D, E);
            break;

        case 88: // 'X'
            E = B;
            DE = combine(D, E);
            break;

        case 89: // 'Y'
            E = C;
            DE = combine(D, E);
            break;

        case 90: // 'Z'
            E = D;
            DE = combine(D, E);
            break;

        case 91: // '['
            E = E;
            DE = combine(D, E);
            break;

        case 92: // '\\'
            E = H;
            DE = combine(D, E);
            break;

        case 93: // ']'
            E = L;
            DE = combine(D, E);
            break;

        case 94: // '^'
            E = getMem(HL);
            DE = combine(D, E);
            break;

        case 95: // '_'
            E = A;
            DE = combine(D, E);
            break;

        case 96: // '`'
            H = B;
            HL = combine(H, L);
            break;

        case 97: // 'a'
            H = C;
            HL = combine(H, L);
            break;

        case 98: // 'b'
            H = D;
            HL = combine(H, L);
            break;

        case 99: // 'c'
            H = E;
            HL = combine(H, L);
            break;

        case 100: // 'd'
            H = H;
            HL = combine(H, L);
            break;

        case 101: // 'e'
            H = L;
            HL = combine(H, L);
            break;

        case 102: // 'f'
            H = getMem(HL);
            HL = combine(H, L);
            break;

        case 103: // 'g'
            H = A;
            HL = combine(H, L);
            break;

        case 104: // 'h'
            L = B;
            HL = combine(H, L);
            break;

        case 105: // 'i'
            L = C;
            HL = combine(H, L);
            break;

        case 106: // 'j'
            L = D;
            HL = combine(H, L);
            break;

        case 107: // 'k'
            L = E;
            HL = combine(H, L);
            break;

        case 108: // 'l'
            L = H;
            HL = combine(H, L);
            break;

        case 109: // 'm'
            L = L;
            HL = combine(H, L);
            break;

        case 110: // 'n'
            L = getMem(HL);
            HL = combine(H, L);
            break;

        case 111: // 'o'
            L = A;
            HL = combine(H, L);
            break;

        case 112: // 'p'
            setMem(HL, B);
            break;

        case 113: // 'q'
            setMem(HL, C);
            break;

        case 114: // 'r'
            setMem(HL, D);
            break;

        case 115: // 's'
            setMem(HL, E);
            break;

        case 116: // 't'
            setMem(HL, H);
            break;

        case 117: // 'u'
            setMem(HL, L);
            break;

        case 118: // 'v'
            if(IME)
                HALT = true;
            else
                HALT_NEXT = true;
            break;

        case 119: // 'w'
            setMem(HL, A);
            break;

        case 120: // 'x'
            A = B;
            AF = combine(A, F);
            break;

        case 121: // 'y'
            A = C;
            AF = combine(A, F);
            break;

        case 122: // 'z'
            A = D;
            AF = combine(A, F);
            break;

        case 123: // '{'
            A = E;
            AF = combine(A, F);
            break;

        case 124: // '|'
            A = H;
            AF = combine(A, F);
            break;

        case 125: // '}'
            A = L;
            AF = combine(A, F);
            break;

        case 126: // '~'
            A = getMem(HL);
            AF = combine(A, F);
            break;

        case 127: // '\177'
            A = A;
            AF = combine(A, F);
            break;

        case 128: 
            ADD(B);
            break;

        case 129: 
            ADD(C);
            break;

        case 130: 
            ADD(D);
            break;

        case 131: 
            ADD(E);
            break;

        case 132: 
            ADD(H);
            break;

        case 133: 
            ADD(L);
            break;

        case 134: 
            ADD(getMem(HL));
            break;

        case 135: 
            ADD(A);
            break;

        case 136: 
            ADC(B);
            break;

        case 137: 
            ADC(C);
            break;

        case 138: 
            ADC(D);
            break;

        case 139: 
            ADC(E);
            break;

        case 140: 
            ADC(H);
            break;

        case 141: 
            ADC(L);
            break;

        case 142: 
            ADC(getMem(HL));
            break;

        case 143: 
            ADC(A);
            break;

        case 144: 
            SUB(B);
            break;

        case 145: 
            SUB(C);
            break;

        case 146: 
            SUB(D);
            break;

        case 147: 
            SUB(E);
            break;

        case 148: 
            SUB(H);
            break;

        case 149: 
            SUB(L);
            break;

        case 150: 
            SUB(getMem(HL));
            break;

        case 151: 
            SUB(A);
            break;

        case 152: 
            SBC(B);
            break;

        case 153: 
            SBC(C);
            break;

        case 154: 
            SBC(D);
            break;

        case 155: 
            SBC(E);
            break;

        case 156: 
            SBC(H);
            break;

        case 157: 
            SBC(L);
            break;

        case 158: 
            SBC(getMem(HL));
            break;

        case 159: 
            SBC(A);
            break;

        case 160: 
            AND(B);
            break;

        case 161: 
            AND(C);
            break;

        case 162: 
            AND(D);
            break;

        case 163: 
            AND(E);
            break;

        case 164: 
            AND(H);
            break;

        case 165: 
            AND(L);
            break;

        case 166: 
            AND(getMem(HL));
            break;

        case 167: 
            AND(A);
            break;

        case 168: 
            XOR(B);
            break;

        case 169: 
            XOR(C);
            break;

        case 170: 
            XOR(D);
            break;

        case 171: 
            XOR(E);
            break;

        case 172: 
            XOR(H);
            break;

        case 173: 
            XOR(L);
            break;

        case 174: 
            XOR(getMem(HL));
            break;

        case 175: 
            XOR(A);
            break;

        case 176: 
            OR(B);
            break;

        case 177: 
            OR(C);
            break;

        case 178: 
            OR(D);
            break;

        case 179: 
            OR(E);
            break;

        case 180: 
            OR(H);
            break;

        case 181: 
            OR(L);
            break;

        case 182: 
            OR(getMem(HL));
            break;

        case 183: 
            OR(A);
            break;

        case 184: 
            CP(B);
            break;

        case 185: 
            CP(C);
            break;

        case 186: 
            CP(D);
            break;

        case 187: 
            CP(E);
            break;

        case 188: 
            CP(H);
            break;

        case 189: 
            CP(L);
            break;

        case 190: 
            CP(getMem(HL));
            break;

        case 191: 
            CP(A);
            break;

        case 192: 
            if((F & 0x80) == 0)
            {
                incAll(12);
                RET();
            }
            break;

        case 193: 
            BC = POP();
            B = getUpper(BC);
            C = getLower(BC);
            break;

        case 194: 
            if((F & 0x80) == 0)
            {
                incAll(4);
                JP();
            } else
            {
                PC += 2;
            }
            break;

        case 195: 
            JP();
            break;

        case 196: 
            if((F & 0x80) == 0)
            {
                incAll(12);
                CALL();
            } else
            {
                PC += 2;
            }
            break;

        case 197: 
            PUSH(BC);
            break;

        case 198: 
            ADD(getMem(PC++));
            break;

        case 199: 
            RST(0);
            break;

        case 200: 
            if((F & 0x80) == 128)
            {
                incAll(12);
                RET();
            }
            break;

        case 201: 
            RET();
            break;

        case 202: 
            if((F & 0x80) == 128)
            {
                incAll(4);
                JP();
            } else
            {
                PC += 2;
            }
            break;

        case 203: 
            singleCPUStepCB();
            break;

        case 204: 
            if((F & 0x80) == 128)
            {
                incAll(12);
                CALL();
            } else
            {
                PC += 2;
            }
            break;

        case 205: 
            CALL();
            break;

        case 206: 
            ADC(getMem(PC++));
            break;

        case 207: 
            RST(8);
            break;

        case 208: 
            if((F & 0x10) == 0)
            {
                incAll(12);
                RET();
            }
            break;

        case 209: 
            DE = POP();
            D = getUpper(DE);
            E = getLower(DE);
            break;

        case 210: 
            if((F & 0x10) == 0)
            {
                incAll(4);
                JP();
            } else
            {
                PC += 2;
            }
            break;

        case 211: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xD3 " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xD3 ");
            break;

        case 212: 
            if((F & 0x10) == 0)
            {
                incAll(12);
                CALL();
            } else
            {
                PC += 2;
            }
            break;

        case 213: 
            PUSH(DE);
            break;

        case 214: 
            SUB(getMem(PC++));
            break;

        case 215: 
            RST(16);
            break;

        case 216: 
            if((F & 0x10) == 16)
            {
                incAll(12);
                RET();
            }
            break;

        case 217: 
            RET();
            opCodeList1();
            IME = true;
            if(HALT_NEXT)
            {
                HALT = true;
                HALT_NEXT = false;
            }
            break;

        case 218: 
            if((F & 0x10) == 16)
            {
                incAll(4);
                JP();
            } else
            {
                PC += 2;
            }
            break;

        case 219: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xDB " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xDB ");
            break;

        case 220: 
            if((F & 0x10) == 16)
            {
                incAll(12);
                CALL();
            } else
            {
                PC += 2;
            }
            break;

        case 221: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xDD " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xDD ");
            break;

        case 222: 
            SBC(getMem(PC++));
            break;

        case 223: 
            RST(24);
            break;

        case 224: 
            setMem(65280 + getMem(PC++), A);
            break;

        case 225: 
            HL = POP();
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 226: 
            setMem(65280 + C, A);
            break;

        case 227: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xE3 " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xE3 ");
            break;

        case 228: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xE4 " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xE4 ");
            break;

        case 229: 
            PUSH(HL);
            break;

        case 230: 
            AND(getMem(PC++));
            break;

        case 231: 
            RST(32);
            break;

        case 232: 
            SP = ADDSP(getSignedMemN());
            break;

        case 233: 
            PC = HL;
            break;

        case 234: 
            setMem(getMemNN(), A);
            break;

        case 235: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xEB " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xEB ");
            break;

        case 236: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xEC " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xEC ");
            break;

        case 237: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xED " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xED ");
            break;

        case 238: 
            XOR(getMem(PC++));
            break;

        case 239: 
            RST(40);
            break;

        case 240: 
            A = getMem(65280 + getMem(PC++));
            AF = combine(A, F);
            break;

        case 241: 
            AF = POP();
            A = getUpper(AF);
            F = getLower(AF);
            break;

        case 242: 
            A = getMem(65280 + C);
            AF = combine(A, F);
            break;

        case 243: 
            IME = false;
            break;

        case 244: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xF4 " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xF4 ");
            break;

        case 245: 
            PUSH(AF);
            break;

        case 246: 
            OR(getMem(PC++));
            break;

        case 247: 
            RST(48);
            break;

        case 248: 
            HL = ADDSP(getSignedMemN());
            H = getUpper(HL);
            L = getLower(HL);
            break;

        case 249: 
            SP = HL;
            break;

        case 250: 
            A = getMem(getMemNN());
            AF = combine(A, F);
            break;

        case 251: 
            opCodeList1();
            IME = true;
            if(HALT_NEXT)
            {
                HALT = true;
                HALT_NEXT = false;
            }
            break;

        case 252: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xFC " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xFC ");
            break;

        case 253: 
            GB_MEM[65357] = '\0';
            STOP = true;
            //Logger_debug("Un needed opCode 0xFD " + Integer.toHexString(PC - 1));
            Logger_debug("Un needed opCode 0xFD ");
            break;

        case 254: 
            CP(getMem(PC++));
            break;

        case 255: 
            RST(56);
            break;

        default:
            //Logger_debug("Unknown op code " + Integer.toHexString(opCode));
            Logger_debug("Un needed opCode (default) ");
            break;
        }
    }
    
    // @@@@@@@@@@@ end of CPU dispatch routine @@@@@@@@@@@
    
    void GameBoyCPU::singleCPUStepCB() {
        opCode2 = getMem(PC++);
        incAll(incAllValue[opCode2]);
        switch(opCode2)
        {
        case 0: // '\0'
            B = RLC(B);
            BC = combine(B, C);
            break;

        case 1: // '\001'
            C = RLC(C);
            BC = combine(B, C);
            break;

        case 2: // '\002'
            D = RLC(D);
            DE = combine(D, E);
            break;

        case 3: // '\003'
            E = RLC(E);
            DE = combine(D, E);
            break;

        case 4: // '\004'
            H = RLC(H);
            HL = combine(H, L);
            break;

        case 5: // '\005'
            L = RLC(L);
            HL = combine(H, L);
            break;

        case 6: // '\006'
            setMem(HL, RLC(getMem(HL)));
            break;

        case 7: // '\007'
            A = RLC(A);
            AF = combine(A, F);
            break;

        case 8: // '\b'
            B = RRC(B);
            BC = combine(B, C);
            break;

        case 9: // '\t'
            C = RRC(C);
            BC = combine(B, C);
            break;

        case 10: // '\n'
            D = RRC(D);
            DE = combine(D, E);
            break;

        case 11: // '\013'
            E = RRC(E);
            DE = combine(D, E);
            break;

        case 12: // '\f'
            H = RRC(H);
            HL = combine(H, L);
            break;

        case 13: // '\r'
            L = RRC(L);
            HL = combine(H, L);
            break;

        case 14: // '\016'
            setMem(HL, RRC(getMem(HL)));
            break;

        case 15: // '\017'
            A = RRC(A);
            AF = combine(A, F);
            break;

        case 16: // '\020'
            B = RL(B);
            BC = combine(B, C);
            break;

        case 17: // '\021'
            C = RL(C);
            BC = combine(B, C);
            break;

        case 18: // '\022'
            D = RL(D);
            DE = combine(D, E);
            break;

        case 19: // '\023'
            E = RL(E);
            DE = combine(D, E);
            break;

        case 20: // '\024'
            H = RL(H);
            HL = combine(H, L);
            break;

        case 21: // '\025'
            L = RL(L);
            HL = combine(H, L);
            break;

        case 22: // '\026'
            setMem(HL, RL(getMem(HL)));
            break;

        case 23: // '\027'
            A = RL(A);
            AF = combine(A, F);
            break;

        case 24: // '\030'
            B = RR(B);
            BC = combine(B, C);
            break;

        case 25: // '\031'
            C = RR(C);
            BC = combine(B, C);
            break;

        case 26: // '\032'
            D = RR(D);
            DE = combine(D, E);
            break;

        case 27: // '\033'
            E = RR(E);
            DE = combine(D, E);
            break;

        case 28: // '\034'
            H = RR(H);
            HL = combine(H, L);
            break;

        case 29: // '\035'
            L = RR(L);
            HL = combine(H, L);
            break;

        case 30: // '\036'
            setMem(HL, RR(getMem(HL)));
            break;

        case 31: // '\037'
            A = RR(A);
            AF = combine(A, F);
            break;

        case 32: // ' '
            B = SLA(B);
            BC = combine(B, C);
            break;

        case 33: // '!'
            C = SLA(C);
            BC = combine(B, C);
            break;

        case 34: // '"'
            D = SLA(D);
            DE = combine(D, E);
            break;

        case 35: // '#'
            E = SLA(E);
            DE = combine(D, E);
            break;

        case 36: // '$'
            H = SLA(H);
            HL = combine(H, L);
            break;

        case 37: // '%'
            L = SLA(L);
            HL = combine(H, L);
            break;

        case 38: // '&'
            setMem(HL, SLA(getMem(HL)));
            break;

        case 39: // '\''
            A = SLA(A);
            AF = combine(A, F);
            break;

        case 40: // '('
            B = SRA(B);
            BC = combine(B, C);
            break;

        case 41: // ')'
            C = SRA(C);
            BC = combine(B, C);
            break;

        case 42: // '*'
            D = SRA(D);
            DE = combine(D, E);
            break;

        case 43: // '+'
            E = SRA(E);
            DE = combine(D, E);
            break;

        case 44: // ','
            H = SRA(H);
            HL = combine(H, L);
            break;

        case 45: // '-'
            L = SRA(L);
            HL = combine(H, L);
            break;

        case 46: // '.'
            setMem(HL, SRA(getMem(HL)));
            break;

        case 47: // '/'
            A = SRA(A);
            AF = combine(A, F);
            break;

        case 48: // '0'
            B = SWAP(B);
            BC = combine(B, C);
            break;

        case 49: // '1'
            C = SWAP(C);
            BC = combine(B, C);
            break;

        case 50: // '2'
            D = SWAP(D);
            DE = combine(D, E);
            break;

        case 51: // '3'
            E = SWAP(E);
            DE = combine(D, E);
            break;

        case 52: // '4'
            H = SWAP(H);
            HL = combine(H, L);
            break;

        case 53: // '5'
            L = SWAP(L);
            HL = combine(H, L);
            break;

        case 54: // '6'
            setMem(HL, SWAP(getMem(HL)));
            break;

        case 55: // '7'
            A = SWAP(A);
            AF = combine(A, F);
            break;

        case 56: // '8'
            B = SRL(B);
            BC = combine(B, C);
            break;

        case 57: // '9'
            C = SRL(C);
            BC = combine(B, C);
            break;

        case 58: // ':'
            D = SRL(D);
            DE = combine(D, E);
            break;

        case 59: // ';'
            E = SRL(E);
            DE = combine(D, E);
            break;

        case 60: // '<'
            H = SRL(H);
            HL = combine(H, L);
            break;

        case 61: // '='
            L = SRL(L);
            HL = combine(H, L);
            break;

        case 62: // '>'
            setMem(HL, SRL(getMem(HL)));
            break;

        case 63: // '?'
            A = SRL(A);
            AF = combine(A, F);
            break;

        case 64: // '@'
            BIT(0, B);
            break;

        case 65: // 'A'
            BIT(0, C);
            break;

        case 66: // 'B'
            BIT(0, D);
            break;

        case 67: // 'C'
            BIT(0, E);
            break;

        case 68: // 'D'
            BIT(0, H);
            break;

        case 69: // 'E'
            BIT(0, L);
            break;

        case 70: // 'F'
            BIT(0, getMem(HL));
            break;

        case 71: // 'G'
            BIT(0, A);
            break;

        case 72: // 'H'
            BIT(1, B);
            break;

        case 73: // 'I'
            BIT(1, C);
            break;

        case 74: // 'J'
            BIT(1, D);
            break;

        case 75: // 'K'
            BIT(1, E);
            break;

        case 76: // 'L'
            BIT(1, H);
            break;

        case 77: // 'M'
            BIT(1, L);
            break;

        case 78: // 'N'
            BIT(1, getMem(HL));
            break;

        case 79: // 'O'
            BIT(1, A);
            break;

        case 80: // 'P'
            BIT(2, B);
            break;

        case 81: // 'Q'
            BIT(2, C);
            break;

        case 82: // 'R'
            BIT(2, D);
            break;

        case 83: // 'S'
            BIT(2, E);
            break;

        case 84: // 'T'
            BIT(2, H);
            break;

        case 85: // 'U'
            BIT(2, L);
            break;

        case 86: // 'V'
            BIT(2, getMem(HL));
            break;

        case 87: // 'W'
            BIT(2, A);
            break;

        case 88: // 'X'
            BIT(3, B);
            break;

        case 89: // 'Y'
            BIT(3, C);
            break;

        case 90: // 'Z'
            BIT(3, D);
            break;

        case 91: // '['
            BIT(3, E);
            break;

        case 92: // '\\'
            BIT(3, H);
            break;

        case 93: // ']'
            BIT(3, L);
            break;

        case 94: // '^'
            BIT(3, getMem(HL));
            break;

        case 95: // '_'
            BIT(3, A);
            break;

        case 96: // '`'
            BIT(4, B);
            break;

        case 97: // 'a'
            BIT(4, C);
            break;

        case 98: // 'b'
            BIT(4, D);
            break;

        case 99: // 'c'
            BIT(4, E);
            break;

        case 100: // 'd'
            BIT(4, H);
            break;

        case 101: // 'e'
            BIT(4, L);
            break;

        case 102: // 'f'
            BIT(4, getMem(HL));
            break;

        case 103: // 'g'
            BIT(4, A);
            break;

        case 104: // 'h'
            BIT(5, B);
            break;

        case 105: // 'i'
            BIT(5, C);
            break;

        case 106: // 'j'
            BIT(5, D);
            break;

        case 107: // 'k'
            BIT(5, E);
            break;

        case 108: // 'l'
            BIT(5, H);
            break;

        case 109: // 'm'
            BIT(5, L);
            break;

        case 110: // 'n'
            BIT(5, getMem(HL));
            break;

        case 111: // 'o'
            BIT(5, A);
            break;

        case 112: // 'p'
            BIT(6, B);
            break;

        case 113: // 'q'
            BIT(6, C);
            break;

        case 114: // 'r'
            BIT(6, D);
            break;

        case 115: // 's'
            BIT(6, E);
            break;

        case 116: // 't'
            BIT(6, H);
            break;

        case 117: // 'u'
            BIT(6, L);
            break;

        case 118: // 'v'
            BIT(6, getMem(HL));
            break;

        case 119: // 'w'
            BIT(6, A);
            break;

        case 120: // 'x'
            BIT(7, B);
            break;

        case 121: // 'y'
            BIT(7, C);
            break;

        case 122: // 'z'
            BIT(7, D);
            break;

        case 123: // '{'
            BIT(7, E);
            break;

        case 124: // '|'
            BIT(7, H);
            break;

        case 125: // '}'
            BIT(7, L);
            break;

        case 126: // '~'
            BIT(7, getMem(HL));
            break;

        case 127: // '\177'
            BIT(7, A);
            break;

        case 128: 
            B = RES(0, B);
            BC = combine(B, C);
            break;

        case 129: 
            C = RES(0, C);
            BC = combine(B, C);
            break;

        case 130: 
            D = RES(0, D);
            DE = combine(D, E);
            break;

        case 131: 
            E = RES(0, E);
            DE = combine(D, E);
            break;

        case 132: 
            H = RES(0, H);
            HL = combine(H, L);
            break;

        case 133: 
            L = RES(0, L);
            HL = combine(H, L);
            break;

        case 134: 
            setMem(HL, RES(0, getMem(HL)));
            break;

        case 135: 
            A = RES(0, A);
            AF = combine(A, F);
            break;

        case 136: 
            B = RES(1, B);
            BC = combine(B, C);
            break;

        case 137: 
            C = RES(1, C);
            BC = combine(B, C);
            break;

        case 138: 
            D = RES(1, D);
            DE = combine(D, E);
            break;

        case 139: 
            E = RES(1, E);
            DE = combine(D, E);
            break;

        case 140: 
            H = RES(1, H);
            HL = combine(H, L);
            break;

        case 141: 
            L = RES(1, L);
            HL = combine(H, L);
            break;

        case 142: 
            setMem(HL, RES(1, getMem(HL)));
            break;

        case 143: 
            A = RES(1, A);
            AF = combine(A, F);
            break;

        case 144: 
            B = RES(2, B);
            BC = combine(B, C);
            break;

        case 145: 
            C = RES(2, C);
            BC = combine(B, C);
            break;

        case 146: 
            D = RES(2, D);
            DE = combine(D, E);
            break;

        case 147: 
            E = RES(2, E);
            DE = combine(D, E);
            break;

        case 148: 
            H = RES(2, H);
            HL = combine(H, L);
            break;

        case 149: 
            L = RES(2, L);
            HL = combine(H, L);
            break;

        case 150: 
            setMem(HL, RES(2, getMem(HL)));
            break;

        case 151: 
            A = RES(2, A);
            AF = combine(A, F);
            break;

        case 152: 
            B = RES(3, B);
            BC = combine(B, C);
            break;

        case 153: 
            C = RES(3, C);
            BC = combine(B, C);
            break;

        case 154: 
            D = RES(3, D);
            DE = combine(D, E);
            break;

        case 155: 
            E = RES(3, E);
            DE = combine(D, E);
            break;

        case 156: 
            H = RES(3, H);
            HL = combine(H, L);
            break;

        case 157: 
            L = RES(3, L);
            HL = combine(H, L);
            break;

        case 158: 
            setMem(HL, RES(3, getMem(HL)));
            break;

        case 159: 
            A = RES(3, A);
            AF = combine(A, F);
            break;

        case 160: 
            B = RES(4, B);
            BC = combine(B, C);
            break;

        case 161: 
            C = RES(4, C);
            BC = combine(B, C);
            break;

        case 162: 
            D = RES(4, D);
            DE = combine(D, E);
            break;

        case 163: 
            E = RES(4, E);
            DE = combine(D, E);
            break;

        case 164: 
            H = RES(4, H);
            HL = combine(H, L);
            break;

        case 165: 
            L = RES(4, L);
            HL = combine(H, L);
            break;

        case 166: 
            setMem(HL, RES(4, getMem(HL)));
            break;

        case 167: 
            A = RES(4, A);
            AF = combine(A, F);
            break;

        case 168: 
            B = RES(5, B);
            BC = combine(B, C);
            break;

        case 169: 
            C = RES(5, C);
            BC = combine(B, C);
            break;

        case 170: 
            D = RES(5, D);
            DE = combine(D, E);
            break;

        case 171: 
            E = RES(5, E);
            DE = combine(D, E);
            break;

        case 172: 
            H = RES(5, H);
            HL = combine(H, L);
            break;

        case 173: 
            L = RES(5, L);
            HL = combine(H, L);
            break;

        case 174: 
            setMem(HL, RES(5, getMem(HL)));
            break;

        case 175: 
            A = RES(5, A);
            AF = combine(A, F);
            break;

        case 176: 
            B = RES(6, B);
            BC = combine(B, C);
            break;

        case 177: 
            C = RES(6, C);
            BC = combine(B, C);
            break;

        case 178: 
            D = RES(6, D);
            DE = combine(D, E);
            break;

        case 179: 
            E = RES(6, E);
            DE = combine(D, E);
            break;

        case 180: 
            H = RES(6, H);
            HL = combine(H, L);
            break;

        case 181: 
            L = RES(6, L);
            HL = combine(H, L);
            break;

        case 182: 
            setMem(HL, RES(6, getMem(HL)));
            break;

        case 183: 
            A = RES(6, A);
            AF = combine(A, F);
            break;

        case 184: 
            B = RES(7, B);
            BC = combine(B, C);
            break;

        case 185: 
            C = RES(7, C);
            BC = combine(B, C);
            break;

        case 186: 
            D = RES(7, D);
            DE = combine(D, E);
            break;

        case 187: 
            E = RES(7, E);
            DE = combine(D, E);
            break;

        case 188: 
            H = RES(7, H);
            HL = combine(H, L);
            break;

        case 189: 
            L = RES(7, L);
            HL = combine(H, L);
            break;

        case 190: 
            setMem(HL, RES(7, getMem(HL)));
            break;

        case 191: 
            A = RES(7, A);
            AF = combine(A, F);
            break;

        case 192: 
            B = SET(0, B);
            BC = combine(B, C);
            break;

        case 193: 
            C = SET(0, C);
            BC = combine(B, C);
            break;

        case 194: 
            D = SET(0, D);
            DE = combine(D, E);
            break;

        case 195: 
            E = SET(0, E);
            DE = combine(D, E);
            break;

        case 196: 
            H = SET(0, H);
            HL = combine(H, L);
            break;

        case 197: 
            L = SET(0, L);
            HL = combine(H, L);
            break;

        case 198: 
            setMem(HL, SET(0, getMem(HL)));
            break;

        case 199: 
            A = SET(0, A);
            AF = combine(A, F);
            break;

        case 200: 
            B = SET(1, B);
            BC = combine(B, C);
            break;

        case 201: 
            C = SET(1, C);
            BC = combine(B, C);
            break;

        case 202: 
            D = SET(1, D);
            DE = combine(D, E);
            break;

        case 203: 
            E = SET(1, E);
            DE = combine(D, E);
            break;

        case 204: 
            H = SET(1, H);
            HL = combine(H, L);
            break;

        case 205: 
            L = SET(1, L);
            HL = combine(H, L);
            break;

        case 206: 
            setMem(HL, SET(1, getMem(HL)));
            break;

        case 207: 
            A = SET(1, A);
            AF = combine(A, F);
            break;

        case 208: 
            B = SET(2, B);
            BC = combine(B, C);
            break;

        case 209: 
            C = SET(2, C);
            BC = combine(B, C);
            break;

        case 210: 
            D = SET(2, D);
            DE = combine(D, E);
            break;

        case 211: 
            E = SET(2, E);
            DE = combine(D, E);
            break;

        case 212: 
            H = SET(2, H);
            HL = combine(H, L);
            break;

        case 213: 
            L = SET(2, L);
            HL = combine(H, L);
            break;

        case 214: 
            setMem(HL, SET(2, getMem(HL)));
            break;

        case 215: 
            A = SET(2, A);
            AF = combine(A, F);
            break;

        case 216: 
            B = SET(3, B);
            BC = combine(B, C);
            break;

        case 217: 
            C = SET(3, C);
            BC = combine(B, C);
            break;

        case 218: 
            D = SET(3, D);
            DE = combine(D, E);
            break;

        case 219: 
            E = SET(3, E);
            DE = combine(D, E);
            break;

        case 220: 
            H = SET(3, H);
            HL = combine(H, L);
            break;

        case 221: 
            L = SET(3, L);
            HL = combine(H, L);
            break;

        case 222: 
            setMem(HL, SET(3, getMem(HL)));
            break;

        case 223: 
            A = SET(3, A);
            AF = combine(A, F);
            break;

        case 224: 
            B = SET(4, B);
            BC = combine(B, C);
            break;

        case 225: 
            C = SET(4, C);
            BC = combine(B, C);
            break;

        case 226: 
            D = SET(4, D);
            DE = combine(D, E);
            break;

        case 227: 
            E = SET(4, E);
            DE = combine(D, E);
            break;

        case 228: 
            H = SET(4, H);
            HL = combine(H, L);
            break;

        case 229: 
            L = SET(4, L);
            HL = combine(H, L);
            break;

        case 230: 
            setMem(HL, SET(4, getMem(HL)));
            break;

        case 231: 
            A = SET(4, A);
            AF = combine(A, F);
            break;

        case 232: 
            B = SET(5, B);
            BC = combine(B, C);
            break;

        case 233: 
            C = SET(5, C);
            BC = combine(B, C);
            break;

        case 234: 
            D = SET(5, D);
            DE = combine(D, E);
            break;

        case 235: 
            E = SET(5, E);
            DE = combine(D, E);
            break;

        case 236: 
            H = SET(5, H);
            HL = combine(H, L);
            break;

        case 237: 
            L = SET(5, L);
            HL = combine(H, L);
            break;

        case 238: 
            setMem(HL, SET(5, getMem(HL)));
            break;

        case 239: 
            A = SET(5, A);
            AF = combine(A, F);
            break;

        case 240: 
            B = SET(6, B);
            BC = combine(B, C);
            break;

        case 241: 
            C = SET(6, C);
            BC = combine(B, C);
            break;

        case 242: 
            D = SET(6, D);
            DE = combine(D, E);
            break;

        case 243: 
            E = SET(6, E);
            DE = combine(D, E);
            break;

        case 244: 
            H = SET(6, H);
            HL = combine(H, L);
            break;

        case 245: 
            L = SET(6, L);
            HL = combine(H, L);
            break;

        case 246: 
            setMem(HL, SET(6, getMem(HL)));
            break;

        case 247: 
            A = SET(6, A);
            AF = combine(A, F);
            break;

        case 248: 
            B = SET(7, B);
            BC = combine(B, C);
            break;

        case 249: 
            C = SET(7, C);
            BC = combine(B, C);
            break;

        case 250: 
            D = SET(7, D);
            DE = combine(D, E);
            break;

        case 251: 
            E = SET(7, E);
            DE = combine(D, E);
            break;

        case 252: 
            H = SET(7, H);
            HL = combine(H, L);
            break;

        case 253: 
            L = SET(7, L);
            HL = combine(H, L);
            break;

        case 254: 
            setMem(HL, SET(7, getMem(HL)));
            break;

        case 255: 
            A = SET(7, A);
            AF = combine(A, F);
            break;

        default:
            //Logger_debug("Unknown CB op code " + Integer.toHexString(opCode2));
            Logger_debug("Unknown CB op code ");
            break;
        }
    }
    // @@@@@@@@@@@ end of 2nd CPU dispatch routine @@@@@@@@@@@
    
    bool GameBoyCPU::getThreadState() {
        return APPLET_RUNNING;
    }
    
    
    // ================================================================
    // ================================================================
    
    void GameBoyCPU::createDAATable()
    {
        const int tmp_DAA_TABLE[] = {
            68, 256, 512, 772, 1024, 1284, 1540, 1792, 2056, 2316, 
            4112, 4372, 4628, 4880, 5140, 5392, 4096, 4356, 4612, 4864, 
            5124, 5376, 5632, 5892, 6156, 6408, 8240, 8500, 8756, 9008, 
            9268, 9520, 8224, 8484, 8740, 8992, 9252, 9504, 9760, 10020, 
            10284, 10536, 12340, 12592, 12848, 13108, 13360, 13620, 12324, 12576, 
            12832, 13092, 13344, 13604, 13860, 14112, 14376, 14636, 16400, 16660, 
            16916, 17168, 17428, 17680, 16384, 16644, 16900, 17152, 17412, 17664, 
            17920, 18180, 18444, 18696, 20500, 20752, 21008, 21268, 21520, 21780, 
            20484, 20736, 20992, 21252, 21504, 21764, 22020, 22272, 22536, 22796, 
            24628, 24880, 25136, 25396, 25648, 25908, 24612, 24864, 25120, 25380, 
            25632, 25892, 26148, 26400, 26664, 26924, 28720, 28980, 29236, 29488, 
            29748, 30000, 28704, 28964, 29220, 29472, 29732, 29984, 30240, 30500, 
            30764, 31016, 32912, 33172, 33428, 33680, 33940, 34192, 32896, 33156, 
            33412, 33664, 33924, 34176, 34432, 34692, 34956, 35208, 37012, 37264, 
            37520, 37780, 38032, 38292, 36996, 37248, 37504, 37764, 38016, 38276, 
            38532, 38784, 39048, 39308, 85, 273, 529, 789, 1041, 1301, 
            69, 257, 513, 773, 1025, 1285, 1541, 1793, 2057, 2317, 
            4113, 4373, 4629, 4881, 5141, 5393, 4097, 4357, 4613, 4865, 
            5125, 5377, 5633, 5893, 6157, 6409, 8241, 8501, 8757, 9009, 
            9269, 9521, 8225, 8485, 8741, 8993, 9253, 9505, 9761, 10021, 
            10285, 10537, 12341, 12593, 12849, 13109, 13361, 13621, 12325, 12577, 
            12833, 13093, 13345, 13605, 13861, 14113, 14377, 14637, 16401, 16661, 
            16917, 17169, 17429, 17681, 16385, 16645, 16901, 17153, 17413, 17665, 
            17921, 18181, 18445, 18697, 20501, 20753, 21009, 21269, 21521, 21781, 
            20485, 20737, 20993, 21253, 21505, 21765, 22021, 22273, 22537, 22797, 
            24629, 24881, 25137, 25397, 25649, 25909, 24613, 24865, 25121, 25381, 
            25633, 25893, 26149, 26401, 26665, 26925, 28721, 28981, 29237, 29489, 
            29749, 30001, 28705, 28965, 29221, 29473, 29733, 29985, 30241, 30501, 
            30765, 31017, 32913, 33173, 33429, 33681, 33941, 34193, 32897, 33157, 
            33413, 33665, 33925, 34177, 34433, 34693, 34957, 35209, 37013, 37265, 
            37521, 37781, 38033, 38293, 36997, 37249, 37505, 37765, 38017, 38277, 
            38533, 38785, 39049, 39309, 41141, 41393, 41649, 41909, 42161, 42421, 
            41125, 41377, 41633, 41893, 42145, 42405, 42661, 42913, 43177, 43437, 
            45233, 45493, 45749, 46001, 46261, 46513, 45217, 45477, 45733, 45985, 
            46245, 46497, 46753, 47013, 47277, 47529, 49301, 49553, 49809, 50069, 
            50321, 50581, 49285, 49537, 49793, 50053, 50305, 50565, 50821, 51073, 
            51337, 51597, 53393, 53653, 53909, 54161, 54421, 54673, 53377, 53637, 
            53893, 54145, 54405, 54657, 54913, 55173, 55437, 55689, 57521, 57781, 
            58037, 58289, 58549, 58801, 57505, 57765, 58021, 58273, 58533, 58785, 
            59041, 59301, 59565, 59817, 61621, 61873, 62129, 62389, 62641, 62901, 
            61605, 61857, 62113, 62373, 62625, 62885, 63141, 63393, 63657, 63917, 
            85, 273, 529, 789, 1041, 1301, 69, 257, 513, 773, 
            1025, 1285, 1541, 1793, 2057, 2317, 4113, 4373, 4629, 4881, 
            5141, 5393, 4097, 4357, 4613, 4865, 5125, 5377, 5633, 5893, 
            6157, 6409, 8241, 8501, 8757, 9009, 9269, 9521, 8225, 8485, 
            8741, 8993, 9253, 9505, 9761, 10021, 10285, 10537, 12341, 12593, 
            12849, 13109, 13361, 13621, 12325, 12577, 12833, 13093, 13345, 13605, 
            13861, 14113, 14377, 14637, 16401, 16661, 16917, 17169, 17429, 17681, 
            16385, 16645, 16901, 17153, 17413, 17665, 17921, 18181, 18445, 18697, 
            20501, 20753, 21009, 21269, 21521, 21781, 20485, 20737, 20993, 21253, 
            21505, 21765, 22021, 22273, 22537, 22797, 24629, 24881, 25137, 25397, 
            25649, 25909, 1540, 1792, 2056, 2316, 2572, 2824, 3084, 3336, 
            3592, 3852, 4112, 4372, 4628, 4880, 5140, 5392, 5632, 5892, 
            6156, 6408, 6664, 6924, 7176, 7436, 7692, 7944, 8240, 8500, 
            8756, 9008, 9268, 9520, 9760, 10020, 10284, 10536, 10792, 11052, 
            11304, 11564, 11820, 12072, 12340, 12592, 12848, 13108, 13360, 13620, 
            13860, 14112, 14376, 14636, 14892, 15144, 15404, 15656, 15912, 16172, 
            16400, 16660, 16916, 17168, 17428, 17680, 17920, 18180, 18444, 18696, 
            18952, 19212, 19464, 19724, 19980, 20232, 20500, 20752, 21008, 21268, 
            21520, 21780, 22020, 22272, 22536, 22796, 23052, 23304, 23564, 23816, 
            24072, 24332, 24628, 24880, 25136, 25396, 25648, 25908, 26148, 26400, 
            26664, 26924, 27180, 27432, 27692, 27944, 28200, 28460, 28720, 28980, 
            29236, 29488, 29748, 30000, 30240, 30500, 30764, 31016, 31272, 31532, 
            31784, 32044, 32300, 32552, 32912, 33172, 33428, 33680, 33940, 34192, 
            34432, 34692, 34956, 35208, 35464, 35724, 35976, 36236, 36492, 36744, 
            37012, 37264, 37520, 37780, 38032, 38292, 38532, 38784, 39048, 39308, 
            39564, 39816, 40076, 40328, 40584, 40844, 85, 273, 529, 789, 
            1041, 1301, 1541, 1793, 2057, 2317, 2573, 2825, 3085, 3337, 
            3593, 3853, 4113, 4373, 4629, 4881, 5141, 5393, 5633, 5893, 
            6157, 6409, 6665, 6925, 7177, 7437, 7693, 7945, 8241, 8501, 
            8757, 9009, 9269, 9521, 9761, 10021, 10285, 10537, 10793, 11053, 
            11305, 11565, 11821, 12073, 12341, 12593, 12849, 13109, 13361, 13621, 
            13861, 14113, 14377, 14637, 14893, 15145, 15405, 15657, 15913, 16173, 
            16401, 16661, 16917, 17169, 17429, 17681, 17921, 18181, 18445, 18697, 
            18953, 19213, 19465, 19725, 19981, 20233, 20501, 20753, 21009, 21269, 
            21521, 21781, 22021, 22273, 22537, 22797, 23053, 23305, 23565, 23817, 
            24073, 24333, 24629, 24881, 25137, 25397, 25649, 25909, 26149, 26401, 
            26665, 26925, 27181, 27433, 27693, 27945, 28201, 28461, 28721, 28981, 
            29237, 29489, 29749, 30001, 30241, 30501, 30765, 31017, 31273, 31533, 
            31785, 32045, 32301, 32553, 32913, 33173, 33429, 33681, 33941, 34193, 
            34433, 34693, 34957, 35209, 35465, 35725, 35977, 36237, 36493, 36745, 
            37013, 37265, 37521, 37781, 38033, 38293, 38533, 38785, 39049, 39309, 
            39565, 39817, 40077, 40329, 40585, 40845, 41141, 41393, 41649, 41909, 
            42161, 42421, 42661, 42913, 43177, 43437, 43693, 43945, 44205, 44457, 
            44713, 44973, 45233, 45493, 45749, 46001, 46261, 46513, 46753, 47013, 
            47277, 47529, 47785, 48045, 48297, 48557, 48813, 49065, 49301, 49553, 
            49809, 50069, 50321, 50581, 50821, 51073, 51337, 51597, 51853, 52105, 
            52365, 52617, 52873, 53133, 53393, 53653, 53909, 54161, 54421, 54673, 
            54913, 55173, 55437, 55689, 55945, 56205, 56457, 56717, 56973, 57225, 
            57521, 57781, 58037, 58289, 58549, 58801, 59041, 59301, 59565, 59817, 
            60073, 60333, 60585, 60845, 61101, 61353, 61621, 61873, 62129, 62389, 
            62641, 62901, 63141, 63393, 63657, 63917, 64173, 64425, 64685, 64937, 
            65193, 65453, 85, 273, 529, 789, 1041, 1301, 1541, 1793, 
            2057, 2317, 2573, 2825, 3085, 3337, 3593, 3853, 4113, 4373, 
            4629, 4881, 5141, 5393, 5633, 5893, 6157, 6409, 6665, 6925, 
            7177, 7437, 7693, 7945, 8241, 8501, 8757, 9009, 9269, 9521, 
            9761, 10021, 10285, 10537, 10793, 11053, 11305, 11565, 11821, 12073, 
            12341, 12593, 12849, 13109, 13361, 13621, 13861, 14113, 14377, 14637, 
            14893, 15145, 15405, 15657, 15913, 16173, 16401, 16661, 16917, 17169, 
            17429, 17681, 17921, 18181, 18445, 18697, 18953, 19213, 19465, 19725, 
            19981, 20233, 20501, 20753, 21009, 21269, 21521, 21781, 22021, 22273, 
            22537, 22797, 23053, 23305, 23565, 23817, 24073, 24333, 24629, 24881, 
            25137, 25397, 25649, 25909, 70, 258, 514, 774, 1026, 1286, 
            1542, 1794, 2058, 2318, 1026, 1286, 1542, 1794, 2058, 2318, 
            4098, 4358, 4614, 4866, 5126, 5378, 5634, 5894, 6158, 6410, 
            5126, 5378, 5634, 5894, 6158, 6410, 8226, 8486, 8742, 8994, 
            9254, 9506, 9762, 10022, 10286, 10538, 9254, 9506, 9762, 10022, 
            10286, 10538, 12326, 12578, 12834, 13094, 13346, 13606, 13862, 14114, 
            14378, 14638, 13346, 13606, 13862, 14114, 14378, 14638, 16386, 16646, 
            16902, 17154, 17414, 17666, 17922, 18182, 18446, 18698, 17414, 17666, 
            17922, 18182, 18446, 18698, 20486, 20738, 20994, 21254, 21506, 21766, 
            22022, 22274, 22538, 22798, 21506, 21766, 22022, 22274, 22538, 22798, 
            24614, 24866, 25122, 25382, 25634, 25894, 26150, 26402, 26666, 26926, 
            25634, 25894, 26150, 26402, 26666, 26926, 28706, 28966, 29222, 29474, 
            29734, 29986, 30242, 30502, 30766, 31018, 29734, 29986, 30242, 30502, 
            30766, 31018, 32898, 33158, 33414, 33666, 33926, 34178, 34434, 34694, 
            34958, 35210, 33926, 34178, 34434, 34694, 34958, 35210, 36998, 37250, 
            37506, 37766, 38018, 38278, 38534, 38786, 39050, 39310, 13347, 13607, 
            13863, 14115, 14379, 14639, 16387, 16647, 16903, 17155, 17415, 17667, 
            17923, 18183, 18447, 18699, 17415, 17667, 17923, 18183, 18447, 18699, 
            20487, 20739, 20995, 21255, 21507, 21767, 22023, 22275, 22539, 22799, 
            21507, 21767, 22023, 22275, 22539, 22799, 24615, 24867, 25123, 25383, 
            25635, 25895, 26151, 26403, 26667, 26927, 25635, 25895, 26151, 26403, 
            26667, 26927, 28707, 28967, 29223, 29475, 29735, 29987, 30243, 30503, 
            30767, 31019, 29735, 29987, 30243, 30503, 30767, 31019, 32899, 33159, 
            33415, 33667, 33927, 34179, 34435, 34695, 34959, 35211, 33927, 34179, 
            34435, 34695, 34959, 35211, 36999, 37251, 37507, 37767, 38019, 38279, 
            38535, 38787, 39051, 39311, 38019, 38279, 38535, 38787, 39051, 39311, 
            41127, 41379, 41635, 41895, 42147, 42407, 42663, 42915, 43179, 43439, 
            42147, 42407, 42663, 42915, 43179, 43439, 45219, 45479, 45735, 45987, 
            46247, 46499, 46755, 47015, 47279, 47531, 46247, 46499, 46755, 47015, 
            47279, 47531, 49287, 49539, 49795, 50055, 50307, 50567, 50823, 51075, 
            51339, 51599, 50307, 50567, 50823, 51075, 51339, 51599, 53379, 53639, 
            53895, 54147, 54407, 54659, 54915, 55175, 55439, 55691, 54407, 54659, 
            54915, 55175, 55439, 55691, 57507, 57767, 58023, 58275, 58535, 58787, 
            59043, 59303, 59567, 59819, 58535, 58787, 59043, 59303, 59567, 59819, 
            61607, 61859, 62115, 62375, 62627, 62887, 63143, 63395, 63659, 63919, 
            62627, 62887, 63143, 63395, 63659, 63919, 71, 259, 515, 775, 
            1027, 1287, 1543, 1795, 2059, 2319, 1027, 1287, 1543, 1795, 
            2059, 2319, 4099, 4359, 4615, 4867, 5127, 5379, 5635, 5895, 
            6159, 6411, 5127, 5379, 5635, 5895, 6159, 6411, 8227, 8487, 
            8743, 8995, 9255, 9507, 9763, 10023, 10287, 10539, 9255, 9507, 
            9763, 10023, 10287, 10539, 12327, 12579, 12835, 13095, 13347, 13607, 
            13863, 14115, 14379, 14639, 13347, 13607, 13863, 14115, 14379, 14639, 
            16387, 16647, 16903, 17155, 17415, 17667, 17923, 18183, 18447, 18699, 
            17415, 17667, 17923, 18183, 18447, 18699, 20487, 20739, 20995, 21255, 
            21507, 21767, 22023, 22275, 22539, 22799, 21507, 21767, 22023, 22275, 
            22539, 22799, 24615, 24867, 25123, 25383, 25635, 25895, 26151, 26403, 
            26667, 26927, 25635, 25895, 26151, 26403, 26667, 26927, 28707, 28967, 
            29223, 29475, 29735, 29987, 30243, 30503, 30767, 31019, 29735, 29987, 
            30243, 30503, 30767, 31019, 32899, 33159, 33415, 33667, 33927, 34179, 
            34435, 34695, 34959, 35211, 33927, 34179, 34435, 34695, 34959, 35211, 
            36999, 37251, 37507, 37767, 38019, 38279, 38535, 38787, 39051, 39311, 
            38019, 38279, 38535, 38787, 39051, 39311, 64190, 64442, 64702, 64954, 
            65210, 65470, 70, 258, 514, 774, 1026, 1286, 1542, 1794, 
            2058, 2318, 2590, 2842, 3102, 3354, 3610, 3870, 4098, 4358, 
            4614, 4866, 5126, 5378, 5634, 5894, 6158, 6410, 6682, 6942, 
            7194, 7454, 7710, 7962, 8226, 8486, 8742, 8994, 9254, 9506, 
            9762, 10022, 10286, 10538, 10810, 11070, 11322, 11582, 11838, 12090, 
            12326, 12578, 12834, 13094, 13346, 13606, 13862, 14114, 14378, 14638, 
            14910, 15162, 15422, 15674, 15930, 16190, 16386, 16646, 16902, 17154, 
            17414, 17666, 17922, 18182, 18446, 18698, 18970, 19230, 19482, 19742, 
            19998, 20250, 20486, 20738, 20994, 21254, 21506, 21766, 22022, 22274, 
            22538, 22798, 23070, 23322, 23582, 23834, 24090, 24350, 24614, 24866, 
            25122, 25382, 25634, 25894, 26150, 26402, 26666, 26926, 27198, 27450, 
            27710, 27962, 28218, 28478, 28706, 28966, 29222, 29474, 29734, 29986, 
            30242, 30502, 30766, 31018, 31290, 31550, 31802, 32062, 32318, 32570, 
            32898, 33158, 33414, 33666, 33926, 34178, 34434, 34694, 34958, 35210, 
            35482, 35742, 35994, 36254, 36510, 36762, 36998, 37250, 37506, 37766, 
            13347, 13607, 13863, 14115, 14379, 14639, 14911, 15163, 15423, 15675, 
            15931, 16191, 16387, 16647, 16903, 17155, 17415, 17667, 17923, 18183, 
            18447, 18699, 18971, 19231, 19483, 19743, 19999, 20251, 20487, 20739, 
            20995, 21255, 21507, 21767, 22023, 22275, 22539, 22799, 23071, 23323, 
            23583, 23835, 24091, 24351, 24615, 24867, 25123, 25383, 25635, 25895, 
            26151, 26403, 26667, 26927, 27199, 27451, 27711, 27963, 28219, 28479, 
            28707, 28967, 29223, 29475, 29735, 29987, 30243, 30503, 30767, 31019, 
            31291, 31551, 31803, 32063, 32319, 32571, 32899, 33159, 33415, 33667, 
            33927, 34179, 34435, 34695, 34959, 35211, 35483, 35743, 35995, 36255, 
            36511, 36763, 36999, 37251, 37507, 37767, 38019, 38279, 38535, 38787, 
            39051, 39311, 39583, 39835, 40095, 40347, 40603, 40863, 41127, 41379, 
            41635, 41895, 42147, 42407, 42663, 42915, 43179, 43439, 43711, 43963, 
            44223, 44475, 44731, 44991, 45219, 45479, 45735, 45987, 46247, 46499, 
            46755, 47015, 47279, 47531, 47803, 48063, 48315, 48575, 48831, 49083, 
            49287, 49539, 49795, 50055, 50307, 50567, 50823, 51075, 51339, 51599, 
            51871, 52123, 52383, 52635, 52891, 53151, 53379, 53639, 53895, 54147, 
            54407, 54659, 54915, 55175, 55439, 55691, 55963, 56223, 56475, 56735, 
            56991, 57243, 57507, 57767, 58023, 58275, 58535, 58787, 59043, 59303, 
            59567, 59819, 60091, 60351, 60603, 60863, 61119, 61371, 61607, 61859, 
            62115, 62375, 62627, 62887, 63143, 63395, 63659, 63919, 64191, 64443, 
            64703, 64955, 65211, 65471, 71, 259, 515, 775, 1027, 1287, 
            1543, 1795, 2059, 2319, 2591, 2843, 3103, 3355, 3611, 3871, 
            4099, 4359, 4615, 4867, 5127, 5379, 5635, 5895, 6159, 6411, 
            6683, 6943, 7195, 7455, 7711, 7963, 8227, 8487, 8743, 8995, 
            9255, 9507, 9763, 10023, 10287, 10539, 10811, 11071, 11323, 11583, 
            11839, 12091, 12327, 12579, 12835, 13095, 13347, 13607, 13863, 14115, 
            14379, 14639, 14911, 15163, 15423, 15675, 15931, 16191, 16387, 16647, 
            16903, 17155, 17415, 17667, 17923, 18183, 18447, 18699, 18971, 19231, 
            19483, 19743, 19999, 20251, 20487, 20739, 20995, 21255, 21507, 21767, 
            22023, 22275, 22539, 22799, 23071, 23323, 23583, 23835, 24091, 24351, 
            24615, 24867, 25123, 25383, 25635, 25895, 26151, 26403, 26667, 26927, 
            27199, 27451, 27711, 27963, 28219, 28479, 28707, 28967, 29223, 29475, 
            29735, 29987, 30243, 30503, 30767, 31019, 31291, 31551, 31803, 32063, 
            32319, 32571, 32899, 33159, 33415, 33667, 33927, 34179, 34435, 34695, 
            34959, 35211, 35483, 35743, 35995, 36255, 36511, 36763, 36999, 37251, 
            37507, 37767, 38019, 38279, 38535, 38787, 39051, 39311
        };
        DAA_TABLE = (int*)tmp_DAA_TABLE;
    }
    
    void GameBoyCPU::createSwapTable()
    {
        const /*unsigned*/ char tmp_SWAP_TABLE[] = {
            '\0', '\020', ' ', '0', '@', 'P', '`', 'p', '\200', '\220', 
            '\240', '\260', '\300', '\320', '\340', '\360', '\001', '\021', '!', '1', 
            'A', 'Q', 'a', 'q', '\201', '\221', '\241', '\261', '\301', '\321', 
            '\341', '\361', '\002', '\022', '"', '2', 'B', 'R', 'b', 'r', 
            '\202', '\222', '\242', '\262', '\302', '\322', '\342', '\362', '\003', '\023', 
            '#', '3', 'C', 'S', 'c', 's', '\203', '\223', '\243', '\263', 
            '\303', '\323', '\343', '\363', '\004', '\024', '$', '4', 'D', 'T', 
            'd', 't', '\204', '\224', '\244', '\264', '\304', '\324', '\344', '\364', 
            '\005', '\025', '%', '5', 'E', 'U', 'e', 'u', '\205', '\225', 
            '\245', '\265', '\305', '\325', '\345', '\365', '\006', '\026', '&', '6', 
            'F', 'V', 'f', 'v', '\206', '\226', '\246', '\266', '\306', '\326', 
            '\346', '\366', '\007', '\027', '\'', '7', 'G', 'W', 'g', 'w', 
            '\207', '\227', '\247', '\267', '\307', '\327', '\347', '\367', '\b', '\030', 
            '(', '8', 'H', 'X', 'h', 'x', '\210', '\230', '\250', '\270', 
            '\310', '\330', '\350', '\370', '\t', '\031', ')', '9', 'I', 'Y', 
            'i', 'y', '\211', '\231', '\251', '\271', '\311', '\331', '\351', '\371', 
            '\n', '\032', '*', ':', 'J', 'Z', 'j', 'z', '\212', '\232', 
            '\252', '\272', '\312', '\332', '\352', '\372', '\013', '\033', '+', ';', 
            'K', '[', 'k', '{', '\213', '\233', '\253', '\273', '\313', '\333', 
            '\353', '\373', '\f', '\034', ',', '<', 'L', '\\', 'l', '|', 
            '\214', '\234', '\254', '\274', '\314', '\334', '\354', '\374', '\r', '\035', 
            '-', '=', 'M', ']', 'm', '}', '\215', '\235', '\255', '\275', 
            '\315', '\335', '\355', '\375', '\016', '\036', '.', '>', 'N', '^', 
            'n', '~', '\216', '\236', '\256', '\276', '\316', '\336', '\356', '\376', 
            '\017', '\037', '/', '?', 'O', '_', 'o', '\177', '\217', '\237', 
            '\257', '\277', '\317', '\337', '\357', '\377'
        };
        SWAP_TABLE = (unsigned char*)tmp_SWAP_TABLE;
    }
    
    
    
    
    
    
    
    