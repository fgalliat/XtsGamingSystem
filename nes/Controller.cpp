#include "Controller.h"

#ifdef XTSCONSOLE
 #include "../XtsConsole.h"

 #include <time.h>
 #include <chrono>

 extern XtsConsole console;
 // extern Pad* pad;
#endif

namespace sn
{
    Controller::Controller() :
        m_keyStates(0)
        #ifdef DESKTOP
        ,
        m_keyBindings(TotalButtons)
        #endif
    {
//         m_keyBindings[A] = sf::Keyboard::J;
//         m_keyBindings[B] = sf::Keyboard::K;
//         m_keyBindings[Select] = sf::Keyboard::RShift;
//         m_keyBindings[Start] = sf::Keyboard::Return;
//         m_keyBindings[Up] = sf::Keyboard::W;
//         m_keyBindings[Down] = sf::Keyboard::S;
//         m_keyBindings[Left] = sf::Keyboard::A;
//         m_keyBindings[Right] = sf::Keyboard::D;
    }

    #ifdef DESKTOP
    void Controller::setKeyBindings(const std::vector<sf::Keyboard::Key>& keys)
    {
        m_keyBindings = keys;
    }
    #endif

    #ifdef XTSCONSOLE
      Pad* _innerPad = NULL;
      uint64_t _lastTime;

      

      Pad* _atomicPadRead() {
      	/*
          uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


          if ( _innerPad == NULL || ( _lastTime - now >= 50 ) ) {
              _lastTime = now;
              _innerPad = console.readPad();
          }
*/
_innerPad = console.getPad();
          return _innerPad;
          //return pad;
      }
    #endif

    void Controller::strobe(Byte b)
    {

//printf("pad strobe [%d] \n", b);

        m_strobe = (b & 1);
        if (!m_strobe)
        {
            m_keyStates = 0;
            int shift = 0;
            #ifdef DESKTOP
            for (int button = A; button < TotalButtons; ++button)
            {
                m_keyStates |= (sf::Keyboard::isKeyPressed(m_keyBindings[static_cast<Buttons>(button)]) << shift);
                ++shift;
            }
            #else
              Pad* pad = _atomicPadRead();
              if ( pad->bt1() )   { m_keyStates |= A; printf("[A]\n"); }
              if ( pad->bt2() )   { m_keyStates |= B; printf("[B]\n"); }
              if ( pad->start() ) { m_keyStates |= Start; printf("[Start]\n"); }
              // no select @ this time

              if ( pad->up() ) { m_keyStates |= Up; }
              else if ( pad->down() ) { m_keyStates |= Down; }

              if ( pad->left() ) { m_keyStates |= Left; }
              else if ( pad->right() ) { m_keyStates |= Right; }
            #endif
        }
    }

    Byte Controller::read()
    {
//printf("pad read\n");

        Byte ret;
        if (m_strobe)
            #ifdef DESKTOP
            ret = sf::Keyboard::isKeyPressed(m_keyBindings[A]);
            #else
            ret = _atomicPadRead()->bt1() ? 1 : 0;
            #endif
        else
        {
            ret = (m_keyStates & 1);
            m_keyStates >>= 1;
        }
        return ret | 0x40;
    }

}