#ifndef WIFI_H_
#define WIFI_H_ 1

 /**
  * Wifi subSystem 
  * 
  * Xtase - fgalliat @Sep 2018
  * 
  * 
  */


   class WiFi {
       private:

       public:
        WiFi();
        ~WiFi();

        bool up();
        void down();
        bool restart();

        bool add(char* essid, char* psk);
        void remove(char* essid);

        /* returns list of registered ESSID in wpa_supplicant ':' separated */
        char* getList(); 

        /* {0/1 (connected)} ':' ESSID ':' IP */
        char* getInfos();

        bool isConnected();

   };


#endif