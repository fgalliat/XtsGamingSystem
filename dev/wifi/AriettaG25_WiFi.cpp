#include "./Wifi.h"

/**
 * WiFi subSystem for AriettaG25
 * 
 * Xtase-fgalliat @Sep2018
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

    WiFi::WiFi() {}
    WiFi::~WiFi() {}



    bool WiFi::up() {
        printf("UP WIFI => OK");
        return true;
    }
    void WiFi::down() {
        printf("DOWN WIFI => OK");
    }
    bool WiFi::restart() {
        this->down();
        return this->up();
    }

    bool WiFi::add(char* essid, char* psk) {
        return true;
    }
    void WiFi::remove(char* essid) {

    }

    /* returns list of registered ESSID in wpa_supplicant ':' separated */
    char* WiFi::getList() {
        return (char*) "XXXX:YYYYY:ZZZZ";
    }

    /* {0/1 (connected)} ':' ESSID ':' IP */
    char* WiFi::getInfos() {
        return (char*) "0:NULL:0.0.0.0";
    }

    bool WiFi::isConnected() {
        return false;
    }