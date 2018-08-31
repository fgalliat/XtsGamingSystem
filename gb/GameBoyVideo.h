#ifndef __CBVID_H_
#define __CBVID_H_ 1

 class GameBoyVideo {
 	 public:
 	   // NB : on ne nomme pas les arguments
 	   GameBoyVideo(unsigned char*, unsigned char*);
 	   
 	   void refresh();
     int drawLine();
     int getBackColour(int, int);
     int getForeColour(int, int);
     void setVidMult(int);
     void setBackColour(int, int, int);
     void setForeColour(int, int, int);
     void setBGPointers(int);
     void setWinPointers(int);
     void setTileArea(int);

 	   
 	   
 	   
 	 private:
    unsigned char* GB_MEM;
    unsigned char* VRAM;
    int winPoint;
    int tileArea;
    int bgPoint;
    int vidMult;
    int currentLine;
    int scrollX;
    int scrollY;
    int tile;
    int xTile;
    int yTile;
    int bitX;
    int bitY;
    int colour;
    int charBnkSlct;
    int tileProp;
    int winX;
    int winY;
    int currentSpr;
    int sprX;
    int sprY;
    int sprF;
    int sprSize;
    int sprPerLine;
    int tx;
    int ty;
    int* yLookUp;
    int* pixelColor;
    int* backPal;
    int* forePal;
    bool* pixelPriority;
    static const int LCD_CTRL = 65344;
    static const int LCD_SCROLL_Y = 65346;
    static const int LCD_SCROLL_X = 65347;
    static const int LCD_Y_LOC = 65348;
    static const int LCD_WIN_Y = 65354;
    static const int LCD_WIN_X = 65355;
 };

#endif