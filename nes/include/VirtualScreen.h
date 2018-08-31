#ifndef VIRTUALSCREEN_H
#define VIRTUALSCREEN_H

#ifdef DESKTOP
  #include <SFML/Graphics.hpp>
#else
  #include <errno.h>
  #include <fcntl.h> 
  #include <string.h>
  #include <termios.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <stdint.h>
  #include <stdio.h>
  #include <string.h>

  #include <stddef.h>
#endif

namespace sn
{

    #ifdef DESKTOP
    class VirtualScreen : public sf::Drawable
    {
    public:
        void create (unsigned int width, unsigned int height, float pixel_size, sf::Color color);
        void setPixel (std::size_t x, std::size_t y, sf::Color color);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2u m_screenSize;
        float m_pixelSize; //virtual pixel size in real pixels
        sf::VertexArray m_vertices;
    };
    #else
    class VirtualScreen
    {
    public:
        void create (unsigned int width, unsigned int height, float pixel_size, uint16_t color);
        void setPixel (unsigned int x, unsigned int y, uint16_t color);

		void draw();

    private:
        

        //sf::Vector2u m_screenSize;
        float m_pixelSize; //virtual pixel size in real pixels
        //sf::VertexArray m_vertices;
    };
    #endif 
};
#endif // VIRTUALSCREEN_H
