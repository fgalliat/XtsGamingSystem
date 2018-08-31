#include "VirtualScreen.h"

#ifdef XTSCONSOLE
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
 
 #include "../XtsConsole.h"
 extern XtsConsole console;
#endif

namespace sn
{

    #ifdef XTSCONSOLE

	unsigned int sch = 0;
	unsigned int mxh = 0;

    void VirtualScreen::create(unsigned int w, unsigned int h, float pixel_size, uint16_t color)
    {
    	// NEVER CALLED
    	sch = h;
    	printf("CREATE h=%d\n", h);
        console.getScreen()->cls();
    }

	uint16_t vram[256*240];
	bool dirty = false;

	void VirtualScreen::draw() {
		if ( !dirty ) { return; }
		// console.getScreen()->drawRGB16(0, 0, 256, 240, vram);
		dirty = false;
	}

    void VirtualScreen::setPixel(unsigned int  x, unsigned int  y, uint16_t color)
    {
    	//dirty = true;
    	
    	//if ( sch <= 0 ) { sch = 240-1; }
        
        console.getScreen()->drawPixel(x,y,color);
        
        vram[ (256*y)+x ] = color;
        
        //if (y > mxh) { mxh = y; printf("DRAW @%d\n",mxh); }
        
        if ( y >= sch && x >= 256-1 ) {
        	dirty = true;
        	draw();
        }
        
        /*
        if ( y >= sch && x >= 256-1 ) {
        	//printf("VBLANK\n");
        	//_VBlankSync();
        }*/
    }

    #else
    void VirtualScreen::create(unsigned int w, unsigned int h, float pixel_size, sf::Color color)
    {
        m_vertices.resize(w * h * 6);
        m_screenSize = {w, h};
        m_vertices.setPrimitiveType(sf::Triangles);
        m_pixelSize = pixel_size;
        for (std::size_t x = 0; x < w; ++x)
        {
            for (std::size_t y = 0; y < h; ++y)
            {
                auto index = (x * m_screenSize.y + y) * 6;
                sf::Vector2f coord2d (x * m_pixelSize, y * m_pixelSize);

                //Triangle-1
                //top-left
                m_vertices[index].position = coord2d;
                m_vertices[index].color    = color;

                //top-right
                m_vertices[index + 1].position = coord2d + sf::Vector2f{m_pixelSize, 0};
                m_vertices[index + 1].color = color;

                //bottom-right
                m_vertices[index + 2].position = coord2d + sf::Vector2f{m_pixelSize, m_pixelSize};
                m_vertices[index + 2].color = color;

                //Triangle-2
                //bottom-right
                m_vertices[index + 3].position = coord2d + sf::Vector2f{m_pixelSize, m_pixelSize};
                m_vertices[index + 3].color = color;

                //bottom-left
                m_vertices[index + 4].position = coord2d + sf::Vector2f{0, m_pixelSize};
                m_vertices[index + 4].color = color;

                //top-left
                m_vertices[index + 5].position = coord2d;
                m_vertices[index + 5].color    = color;
            }
        }
    }

    void VirtualScreen::setPixel(std::size_t x, std::size_t y, sf::Color color)
    {
        auto index = (x * m_screenSize.y + y) * 6;
        if (index >= m_vertices.getVertexCount())
            return;

        sf::Vector2f coord2d (x * m_pixelSize, y * m_pixelSize);

        //Triangle-1
        //top-left
        m_vertices[index].color    = color;

        //top-right
        m_vertices[index + 1].color = color;

        //bottom-right
        m_vertices[index + 2].color = color;

        //Triangle-2
        //bottom-right
        m_vertices[index + 3].color = color;

        //bottom-left
        m_vertices[index + 4].color = color;

        //top-left
        m_vertices[index + 5].color    = color;
    }

    void VirtualScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_vertices, states);
    }

    #endif
}