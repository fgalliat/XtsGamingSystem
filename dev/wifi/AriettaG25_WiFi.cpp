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

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

std::string _w_exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}


    WiFi::WiFi() {}
    WiFi::~WiFi() {}


    bool WiFi::up() {
        system("/vm_mnt/bin/wifiUp.sh");
        return this->isConnected();
    }
    void WiFi::down() {
        // printf("DOWN WIFI => OK");
        system("/vm_mnt/bin/wifiDown.sh");
    }
    bool WiFi::restart() {
        this->down();
        return this->up();
    }

    bool WiFi::add(char* essid, char* psk) {
        printf("WiFi ADD network NYI\n");
        return true;
    }
    void WiFi::remove(char* essid) {
        printf("WiFi REM network NYI\n");
    }

    /* returns list of registered ESSID in wpa_supplicant ':' separated */
    char* WiFi::getList() {
        std::string str = _w_exec("/vm_mnt/bin/wifiList.sh");
        int len = str.length();

        char * cstr = new char [len+1];
        strcpy(cstr, str.c_str());

        for (int i=0; i < len; i++) {
            if ( cstr[i] == '\n' ) { cstr[i] = ':'; }
        }

        // return (char*) "XXXX:YYYYY:ZZZZ";
        return cstr;
    }

    /* {0/1 (connected)} ':' ESSID ':' IP */
    char* WiFi::getInfos() {
        // add a Timer control !
        


        std::string str = _w_exec("/vm_mnt/bin/wifiInfos.sh");
        int len = str.length();

        if ( len == 0 ) {
            return (char*) "0:NULL:0.0.0.0";
        }

        char * cstr = new char [len+1 +2 ]; // +2 Cf '1:'
        //strcpy(cstr, str.c_str());
        strcpy(cstr, "1:");
        strcat(cstr, str.c_str());

        for (int i=0; i < len; i++) {
            if ( cstr[i+2] == '\n' ) { cstr[i+2] = ':'; }
        }

        return cstr;
    }

    bool WiFi::isConnected() {
        char* infos = this->getInfos();
        return infos != NULL && strlen( infos ) > 0 && infos[0] == '1';
    }