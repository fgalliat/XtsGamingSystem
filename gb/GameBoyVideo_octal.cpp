
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <pthread.h>
#include <iostream>


#include "Logger.h"
#include "GameBoyVideo.h"

//extern void setPixel(int addr, int color);
extern void setPixelIndexed(int addr, int colorIdx);
extern void setScreenDirty();

const int _PAL_WIDTH = 8;
const int _PAL_HEIGHT = 4;

const int PAL_WIDTH = 2;
const int PAL_HEIGHT = 2;

GameBoyVideo::GameBoyVideo(unsigned char* _GB_MEM, unsigned char* _VRAM) {
	
	GB_MEM = _GB_MEM;
	VRAM   = _VRAM;
	
	yLookUp = (int*) malloc(144 * sizeof(int));
  pixelColor = (int*) malloc(23040 * sizeof(int));
        
  //backPal = new int[4][8];
  backPal = (int*)malloc(_PAL_HEIGHT*_PAL_WIDTH * sizeof(int));
  forePal = (int*)malloc(_PAL_HEIGHT*_PAL_WIDTH * sizeof(int));
  pixelPriority = (bool*)malloc(23040*sizeof(bool));
  
	for(int i = 0; i < 144; i++) {
    yLookUp[i] = i * 160;
	}
}

void GameBoyVideo::refresh() {
	// nothing
setScreenDirty();
}

int GameBoyVideo::drawLine() {
	
	printf("dl\n");
	
    if(GB_MEM[65348] < '\220')
    {
        currentLine = GB_MEM[65348];
        sprPerLine = 0;
        if((GB_MEM[65344] & '\001') > 0)
        {
            scrollX = GB_MEM[65347];
            scrollY = GB_MEM[65346];
            for(int i = 0; i < 160; i++)
            {
                if(scrollY + currentLine > 255)
                    scrollY -= 255;
                if(scrollX + i > 255)
                    scrollX -= 255;
                xTile = scrollX + i >> 3;
                yTile = scrollY + currentLine >> 3;
                bitX = scrollX + i & 7;
                bitY = scrollY + currentLine & 7;
                tileProp = VRAM[8192 + bgPoint + (yTile << 5) + xTile];
                tile = VRAM[bgPoint + (yTile << 5) + xTile];
                if(tileArea == 2048)
                    tile ^= 0x80;
                if((tileProp & 0x20) > 0)
                    bitX = 7 - bitX;
                if((tileProp & 0x40) > 0)
                    bitY = 7 - bitY;
                charBnkSlct = (tileProp & 8) <= 0 ? 0 : 8192;
                colour = (VRAM[charBnkSlct + tileArea + 1 + (bitY << 1) + (tile << 4)] >> 7 - bitX & 1) << 1 | VRAM[charBnkSlct + tileArea + (bitY << 1) + (tile << 4)] >> 7 - bitX & 1;
                
//                    GBMain.getInstance().fb[yLookUp[currentLine] + i] = backPal[colour][tileProp & 7];
                //GBMain.instance.setPixel(yLookUp[currentLine] + i,  backPal[colour][tileProp & 7]);
              
                // moa - may not support gbc..
                //setPixel(yLookUp[currentLine] + i,  backPal[colour * PAL_WIDTH + (tileProp & 7) ]);
                setPixelIndexed(yLookUp[currentLine] + i, colour);
                
                pixelColor[yLookUp[currentLine] + i] = colour;
                pixelPriority[yLookUp[currentLine] + i] = (tileProp & 0x80) > 0;
            }

        }
        if((GB_MEM[65344] & 0x20) > 0 && GB_MEM[65354] <= currentLine)
        {
            winX = GB_MEM[65355] - 7;
            winY = GB_MEM[65354];
            for(int j = 0; j < 160 - winX; j++)
            {
                xTile = j >> 3;
                yTile = currentLine - winY >> 3;
                bitX = j & 7;
                bitY = currentLine - winY & 7;
                tileProp = VRAM[8192 + winPoint + (yTile << 5) + xTile];
                tile = VRAM[winPoint + (yTile << 5) + xTile];
                if(tileArea == 2048)
                    tile ^= 0x80;
                charBnkSlct = (tileProp & 8) <= 0 ? 0 : 8192;
                colour = (VRAM[charBnkSlct + tileArea + 1 + (bitY << 1) + (tile << 4)] >> 7 - bitX & 1) << 1 | VRAM[charBnkSlct + tileArea + (bitY << 1) + (tile << 4)] >> 7 - bitX & 1;
                if(j + winX < 160 && j + winX >= 0)
                {
//                        GBMain.getInstance().fb[yLookUp[currentLine] + (j + winX)] = backPal[colour][tileProp & 7];
                	//GBMain.instance.setPixel(yLookUp[currentLine] + (j + winX), backPal[colour][tileProp & 7]);
                  
                    // moa - may not support GBC
                	//setPixel(yLookUp[currentLine] + (j + winX), backPal[colour * PAL_WIDTH + (tileProp & 7) ]);
                    setPixelIndexed(yLookUp[currentLine] + (j + winX), colour);
                	
                    pixelColor[yLookUp[currentLine] + (j + winX)] = colour;
                    pixelPriority[yLookUp[currentLine] + (j + winX)] = (tileProp & 0x80) > 0;
                }
            }

        }
        if((GB_MEM[65344] & 2) > 0)
        {
            sprSize = (GB_MEM[65344] & 4) <= 0 ? 7 : 15;
            for(int k = 39; k >= 0; k--)
            {
                currentSpr = k << 2;
                sprY = GB_MEM[65024 + currentSpr] - 16;
                if(sprY > currentLine || sprY + sprSize < currentLine)
                    continue;
                sprPerLine++;
                sprY = currentLine - sprY;
                sprX = GB_MEM[65025 + currentSpr] - 8;
                tile = GB_MEM[65026 + currentSpr];
                sprF = GB_MEM[65027 + currentSpr];
                if((sprF & 0x40) > 0)
                    sprY = sprSize - sprY;
                for(int l = 0; l < 8; l++)
                {
                    tx = (sprF & 0x20) <= 0 ? sprX + l : sprX + (7 - l);
                    if(tx < 0 || tx >= 160 || pixelPriority[yLookUp[currentLine] + tx] && (!pixelPriority[yLookUp[currentLine] + tx] || pixelColor[yLookUp[currentLine] + tx] != 0) || (sprF & 0x80) != 0 && ((sprF & 0x80) <= 0 || pixelColor[yLookUp[currentLine] + tx] != 0))
                        continue;
                    charBnkSlct = (sprF & 8) <= 0 ? 0 : 8192;
                    colour = (VRAM[charBnkSlct + 1 + (sprY << 1) + (tile << 4)] >> 7 - l & 1) << 1 | VRAM[charBnkSlct + (sprY << 1) + (tile << 4)] >> 7 - l & 1;
                    if(colour != 0) {
                    	
//                            GBMain.getInstance().fb[yLookUp[currentLine] + tx] = forePal[colour][GB_MEM[323] < '\200' ? ((int) ((sprF & 0x10) <= 0 ? 0 : 1)) : sprF & 7];
                    	//GBMain.instance.setPixel(yLookUp[currentLine] + tx, forePal[colour][GB_MEM[323] < '\200' ? ((int) ((sprF & 0x10) <= 0 ? 0 : 1)) : sprF & 7]);
                    	
                        // moa may not support gbc
                        //setPixel(yLookUp[currentLine] + tx, forePal[colour*PAL_WIDTH + GB_MEM[323] < '\200' ? ((int) ((sprF & 0x10) <= 0 ? 0 : 1)) : sprF & 7]);
                        setPixelIndexed(yLookUp[currentLine] + tx, colour);
                    } 
                  
                }

            }

        }
    }
    
    //setScreenDirty();
    
    return sprPerLine <= 10 ? sprPerLine : 10;
}

    int GameBoyVideo::getBackColour(int i, int j)
    {
        return backPal[i*PAL_WIDTH + j];
    }

    int GameBoyVideo::getForeColour(int i, int j)
    {
        return forePal[i*PAL_WIDTH + j];
    }

    // screen scaling
    void GameBoyVideo::setVidMult(int i)
    {
        vidMult = i;
//        xOffSet = 160 - (160 * vidMult) / 2;
//        yOffSet = 144 - (144 * vidMult) / 2;
//        imageWidth = 160 * vidMult;
//        imageHeight = 144 * vidMult;
    }

    void GameBoyVideo::setBackColour(int i, int j, int color)
    {
        //if(i > backPal[0].length || j > backPal[1].length)
        //if(i > backPal.length || j > backPal[1].length)
        if(i > _PAL_HEIGHT || j > _PAL_WIDTH)
            Logger_debug("You have tried to set a background palette color outside of normal boundaries");
        else
            backPal[i*_PAL_WIDTH + j] = color;
    }

    void GameBoyVideo::setForeColour(int i, int j, int color)
    {
        //if(i > backPal[0].length || j > backPal[1].length)
        //if(i > backPal.length || j > backPal[1].length)
        if(i > _PAL_HEIGHT || j > _PAL_WIDTH)
            Logger_debug("You have tried to set a foreground palette color outside of normal boundaries");
        else
            forePal[i*_PAL_WIDTH+j] = color;
    }

    void GameBoyVideo::setBGPointers(int i)
    {
        bgPoint = i;
    }

    void GameBoyVideo::setWinPointers(int i)
    {
        winPoint = i;
    }

    void GameBoyVideo::setTileArea(int i)
    {
        tileArea = i;
    }