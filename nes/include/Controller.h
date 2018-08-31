#ifndef CONTROLLER_H
#define CONTROLLER_H

#ifdef DESKTOP
  #include <SFML/Window.hpp>
#endif

#include <cstdint>
#include <vector>

namespace sn
{
    using Byte = std::uint8_t;
    class Controller
    {
    public:
        Controller();
        enum Buttons
        {
            A,
            B,
            Select,
            Start,
            Up,
            Down,
            Left,
            Right,
            TotalButtons,
        };

        void strobe(Byte b);
        Byte read();
        #ifdef DESKTOP
        void setKeyBindings(const std::vector<sf::Keyboard::Key>& keys);
        #endif
    private:
        bool m_strobe;
        unsigned int m_keyStates;

        #ifdef DESKTOP
        std::vector<sf::Keyboard::Key> m_keyBindings;
        #endif

//         sf::Keyboard::Key m_keyBindings[TotalButtons];
    };
}

#endif // CONTROLLER_H
