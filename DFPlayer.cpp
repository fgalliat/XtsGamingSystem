/**
 * DFPlayer mini MP3 module simple driver
 * 
 * https://community.particle.io/t/quickest-easiest-way-of-controlling-the-dfplayer-mini/40246/8
 * https://community.particle.io/t/a-great-very-cheap-mp3-sound-module-without-need-for-a-library/20111/62
 * 
 * 
 * 
0x01 1 Next * [DH]=0, [DL]=0 Next file in current folder.Loops when last file played
0x02 2 Previous * [DH]=0, [DL]=0 Previous file in current folder.Loops when last file played
0x03 3 Specify track(NUM) * [DH]=highByte(NUM), [DL]=lowByte(NUM) 1~2999 Playing order is order in which the numbers are stored. Filename and foldername are arbitrary, but when named starting with an increasing number and in one folder, files are played in that order and with correct track number. e.g. 0001-Joe Jackson.mp3...0348-Lets dance.mp3)
0x06 6 Specify volume * [DH]=0, [DL]=Volume (0-0x30) Default=0x30
0x07 7 Specify Equalizer * [DH]=0, [DL]= EQ(0/1/2/3/4/5) [Normal/Pop/Rock/Jazz/Classic/Base]
0x08 8 Specify repeat(NUM) * [DH]=highByte(NUM), [DL]=lowByte(NUM).Repeat the specified track number
0x0A 10 Enter into standby – low power loss * [DH]=0, [DL]=0 Works, but no command found yet to end standby (insert TF-card again will end standby mode)
0x0C 12 Reset module * [DH]=0, [DL]=0 Resets all (Track = 0x01, Volume = 0x30) Will return 0x3F initialization parameter (0x02 for TF-card) Clap sound after excecuting command (no solution found)
0x0D 13 Play * [DH]=0, [DL]=0 Play current selected track
0x0E 14 Pause * [DH]=0, [DL]=0 Pause track
0x0F 15 Specify folder and file to playback * [DH]=Folder, [DL]=File - Important: Folders must be named 01~99, files must be named 001~255
0x11 17 Loop play - Start at track 1 * [DH]=0, [DL]=1:play, 0:stop play
0x12 18 Play mp3 file [NUM] in mp3 folder * [DH]=highByte(NUM), [DL]=lowByte(NUM) Play mp3 file in folder named mp3 in your TF-card. File format exact - 4-digit number (0001~2999) e.g. 0235.mp3
0x16 22 Stop * [DH]=0, [DL]=0, Stop playing current track
0x17 23 Loop Folder 01 * [DH]=0, [DL]=1~99, Loops all tracks in folder named "01"
0x18 24 Random play * [DH]=0, [DL]=0 Random all tracks, always starts at track 1
0x19 25 Single loop * [DH]=0, [DL]=0 Loops the track that is playing
0x1A 26 Pause * [DH]=0, [DL]=(0x01:pause, 0x00:stop pause)
0x3F 63 Initialization parameters * [DH]=0, [DL]= 0 ~ 0x0F. Returned code when Reset (0x12) is used.(each bit represent one device of the low-four bits) See Datasheet. 0x02 is TF-card. Error 0x01 when no medium is inserted.
0x4F 79 The total number of folders * [DH]=0, [DL]=(NUM), Total number of folders, including root directory
 * 
 * default : 9600 bps
 * 
 * 
 * 
 */
 
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "./dev/arch.h"


Serial Serial1("/dev/ttyS2", 9600);
SoundCard snd( &Serial1 );


// ==================================================

// all files outside /MP3 folder 
void playMp3(int track) {
	snd.play(track);
	printf("Playing track >> %s <<\n", snd.getTrackName() );
} 

// ==============================================
// ==============================================
 
 
int main(int argc, char** argv) {
	printf("Start\n");
	
	bool init = argc > 1;
	
	if ( init ) {
		printf("Oups ! \n");
	} else {
  		int vol = snd.getVolume();
  		
  		snd.init();
		
		int track = 1;
		playMp3(track);
		
		char c;
		do {
		    c=getchar();
		    putchar (c);
		    
		    if ( c == 'n' ) {
		    	playMp3(++track);
		    }
		    if ( c == '>' ) {
		    	track += 5;
		    	playMp3(track);
		    }
		    else if ( c == 'N' ) {
		    	snd.next();
		    }
		    else if ( c == '+' ) {
		    	vol += 2;
  				snd.volume(vol);
		    }
		    else if ( c == '-' ) {
		    	vol -= 2; if ( vol < 0 ) { vol = 0; }
  				snd.volume(vol);
		    }
		    
  		} while (c != '.');

		snd.close();		

	}
	
	printf("Stop\n");
	return 0;
}





 