xnes (from SimpleNES code - https://github.com/amhndu/SimpleNES)



Xtase - fgalliat @Aug 2018 for AriettaG25 subSystem



apt-get install libsfml-dev (gfx & sfx) (no sfx)

NES resolution :
256 x 240



In file included from Controller.cpp:1:0:
include/Controller.h:3:27: fatal error: SFML/Window.hpp: No such file or directory

 #include <SFML/Window.hpp>
                           ^
compilation terminated.
Compiling Emulator.cpp
In file included from Emulator.cpp:1:0:
include/Emulator.h:3:29: fatal error: SFML/Graphics.hpp: No such file or directory
 #include <SFML/Graphics.hpp>
                             ^
compilation terminated.
Compiling KeybindingsParser.cpp
In file included from KeybindingsParser.cpp:7:0:
include/Controller.h:3:27: fatal error: SFML/Window.hpp: No such file or directory
 #include <SFML/Window.hpp>include/VirtualScreen.h:3:29: fatal error: SFML/Graphics.hpp: No such file or directory

 #include <SFML/Graphics.hpp>
