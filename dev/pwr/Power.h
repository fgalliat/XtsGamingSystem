#ifndef _XTS_POWER_H_
#define _XTS_POWER_H_ 1

/**
 * XtsConsole PowerManager API
 * 
 * Xtase - fgalliat @Sept 2018
 * 
 **/


  class Power {
     private:
       bool inRun   = false;
       bool inPause = false;

       const int ACCURACY = 5; // 5min accurate
       int _time = -1;

       void writeBattTimerFile(int value) {
           ...;
       }


       int readBattTimerFile() {
           _time = ...;
           return _time;
       }

       int incBattTimer() {
           if ( _time < 0 ) { readBattTimerFile(); }
           _time++;
           writeBattTimerFile(_time);
           return _time;
       }

       int rstBattTimer() {
          int battTime = 0;
          writeBattTimerFile(battTime);
          return battTime; 
       }

       static void *_xts_battThread(void *context){
          while(inRun) {
            if ( !inPause ) {
                ((Power*)context)->incBattTimer();
                printf("BATT TICK !\n");
                delay( ACCURACY * 60 * 1000 );
            }
          }
          inRun = false;
          inPause = false;
       }


       void startTickThread() {
           inPause = false;
           inRun = true;

           pthread_t t;
           bool ok = pthread_create(&t, NULL, _xts_battThread, this) == 0;
       }

       void pauseTickThread() { inPause = true; }
       void unpauseTickThread() { inPause = false; }

       void stopTickThread() { 
           inPause = true; inRun = false; 
           // no Thread::join() beacause of 5min latency
       }
     public:
       Power() {}
       ~Power();

       void init() {
            // not in constructor (to be not called if console already started)
            // for natives processes support
            startTickThread(); 
       }

       // battery discharging time in min. (5min accurate)
       int getTime() {
           if ( time < 0 ) {
               readBattTimerFile();
           }
           return _time * ACCURACY;
       }

       void resetTime() {
           pauseTickThread();
           rstBattTimer();
           unpauseTickThread();
       }

       void halt(); // stopTick; exit
       void reboot(); // stopTick; exit

       void exit() { stopTickThread(); ::exit(0); }
  };

#endif