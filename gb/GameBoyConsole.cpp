#include "GameBoyConsole.h"


/*
 ==== GameBoyConsole.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include <pthread.h>
#include <iostream>


#include "Logger.h"

bool GameBoyConsole::KEYS_PRESSED[] = { false, false, false, false, false, false, false, false };
const int GameBoyConsole::KEYS[] = { 38, 40, 37, 39, 88, 90, 10, 16, 32 };

// ===============
#include "GameBoyVideo.h"
#include "GameBoyCPU.h"
GameBoyCPU* CPU;


void GameBoyConsole::init() {
	CPU = new GameBoyCPU(KEYS_PRESSED);
  CPU->getVideo()->setVidMult(vidSize);
}

void GameBoyConsole::stop() {
	CPU->stopThread();
  //CPU = null;
}

void GameBoyConsole::loadRom(char* romName) {
	Logger_TMPDBUG(" 0x01 loadRom()");
	if (vidSize == 1) {
		// CPU.getVideo().getGraphics().drawImage(splashScreen, 0, 0, 320,
		// 288, this);
	}
	
	//if (CPU->loadRom(getDocumentBase(), "/roms/" + s)) {
	
	Logger_TMPDBUG(" 0x02 loadRom()");
	if (CPU->loadRom(romName)) {
		Logger_TMPDBUG(" 0x03 loadRom()");
		//if (CPU->getMem(323) >= '\200') {
		if (CPU->getMem(323) >= 0x80) {
			// paletteEditor.setEnabled(false);
		} else {
			// paletteEditor.setEnabled(true);
		}
		Logger_TMPDBUG(" 0x04 loadRom()");
		CPU->fullReset();
		Logger_TMPDBUG(" 0x05 loadRom()");
		Logger_debug("started");
		Logger_TMPDBUG(" 0x06 loadRom()");
		CPU->startThread();
		Logger_TMPDBUG(" 0x07 loadRom()");
	} else {
		Logger_debug("couldn't load ROM ");
	}
	Logger_TMPDBUG(" 0x08 loadRom()");
}

void GameBoyConsole::changeRom(char* romName) {
Logger_TMPDBUG("0x01");
	CPU->stopThread();
Logger_TMPDBUG("0x02");
	CPU->getVideo()->setVidMult(1);
Logger_TMPDBUG("0x03");
  loadRom(romName);
Logger_TMPDBUG("0x04");
}