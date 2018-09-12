#ifndef _XTS_POWER_H_
#define _XTS_POWER_H_ 1

/**
 * XtsConsole PowerManager API
 * 
 * Xtase - fgalliat @Sept 2018
 * 
 **/

#include <sys/stat.h> // for mkdir

  class Power {
     private:
       bool inRun   = false;
       bool inPause = false;

       const int ACCURACY = 5; // 5min accurate
       int _time = -1;

       const char* BATT_LOG_FILE = "/vm_mnt/log/battery.log";

       void createLogDir() {
          // S_IRWXU => chmod 7
          // S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH => 775
          const int dir_err = mkdir("/vm_mnt/log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        //   if (-1 == dir_err) {
        //     printf("Error creating LOG directory! \n");
        //     exit(1);
        //   }
       }

       void writeBattTimerFile(int value) {
            createLogDir();
            FILE *f = fopen(BATT_LOG_FILE, "w");
            if (f == NULL) {
                printf("(!!) Error opening BATTERY-LOG file!\n");
                // _time = 999; // just not saving time
                return;
            }

            fprintf(f, "%d", value);

            fclose(f);
       }


       int readBattTimerFile() {
           createLogDir();
            char num[16];
            int numCpt = 0;

            FILE *f = fopen(BATT_LOG_FILE, "r");
            if (f == NULL) {
                _time = 0; // BEWARE w/ risk of an infinite loop
                return _time;
            }

            while(true) {
                char ch = fgetc(f);
                if ( ch == EOF || ch == '\n' ) {
                    break;
                }
                num[numCpt++] = ch;
            }
            num[numCpt++] = 0x00;

            fclose(f);

           _time = atoi(num);
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
          Power* _this = ((Power*)context);
          while(_this->inRun) {
            if ( !_this->inPause ) {
                _this->incBattTimer();
                printf("BATT TICK !\n");
            }
            delay( _this->ACCURACY * 60 * 1000 ); // 5min
            // delay( _this->ACCURACY * 1000 ); // 5sec
          }
          _this->inRun = false;
          _this->inPause = false;
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
       ~Power() {}

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