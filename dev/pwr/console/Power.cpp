/**
 * XtsConsole PowerManager API
 * 
 * Xtase - fgalliat @Sept 2018
 * 
 **/

#include "../../../XtsConsole.h"

void Power::halt() {
    stopTickThread();
    // printf("FAKE HALT\n");
    system("halt");
    ::exit(0);
}

void Power::reboot() {
    stopTickThread();
    // printf("FAKE REBOOT\n");
    system("reboot");
    ::exit(0);
}