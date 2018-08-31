#ifndef __GBConsole_h_
#define __GBConsole_h_ 1

class GameBoyConsole {
	  int vidSize;
	
	public:
	  // see GameBoyConsole.cpp for values feeding
	  static bool KEYS_PRESSED[];// = { false, false, false, false, false, false, false, false };
	  static const int KEYS[];// = { 38, 40, 37, 39, 88, 90, 10, 16, 32 };
	  
	  void changeRom(char* romName);
	  void loadRom(char* romName);
	  
	  void init();
	  void stop();
};

#endif