#ifndef EMULATOR_H
#define EMULATOR_H

#ifdef DESKTOP
  #include <SFML/Graphics.hpp>
#endif

#include <chrono>

#include "CPU.h"
#include "PPU.h"
#include "MainBus.h"
#include "PictureBus.h"
#include "Controller.h"

namespace sn
{
    using TimePoint = std::chrono::high_resolution_clock::time_point;

    const int NESVideoWidth = ScanlineVisibleDots;
    const int NESVideoHeight = VisibleScanlines;

    class Emulator
    {
    public:
        Emulator();
        void run(std::string rom_path);
        void setVideoWidth(int width);
        void setVideoHeight(int height);
        void setVideoScale(float scale);
        #ifdef DESKTOP
        void setKeys(std::vector<sf::Keyboard::Key>& p1, std::vector<sf::Keyboard::Key>& p2);
        #endif
    private:
        void DMA(Byte page);

        MainBus m_bus;
        PictureBus m_pictureBus;
        CPU m_cpu;
        PPU m_ppu;
        Cartridge m_cartridge;
        std::unique_ptr<Mapper> m_mapper;

        Controller m_controller1, m_controller2;

        #ifdef DESKTOP
        sf::RenderWindow m_window;
        #endif
        VirtualScreen m_emulatorScreen;
        float m_screenScale;

        TimePoint m_cycleTimer;

        std::chrono::high_resolution_clock::duration m_elapsedTime;
        std::chrono::nanoseconds m_cpuCycleDuration;
    };
}
#endif // EMULATOR_H
