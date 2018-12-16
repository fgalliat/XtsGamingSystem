#include "gui.hpp"
#include "config.hpp"

#ifdef XTSCONSOLE
 #include "../XtsConsole.h"
 XtsConsole console;
 Pad* pad;
#endif

int main(int argc, char *argv[])
{
        #ifdef XTSCONSOLE
          if ( ! console.init() ) {
              return -1;
          }
          console.delay(500);
        //   return 1;
        #endif

    GUI::load_settings();
    GUI::init();
    GUI::run();

    return 0;
}
