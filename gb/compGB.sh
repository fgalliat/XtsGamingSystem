# echo Compiling GameBoy layer
# g++ -fPIC -c GameBoyConsole.cpp
# g++ -fPIC -c GameBoyVideo.cpp
# g++ -fPIC -c GameBoyCPU.cpp

# echo Compiling Virtual Console hardware
# g++ -std=c++11 -fPIC -c ../dev/screen/wiredSPI/SPIWiredScreen.cpp 
# g++ -std=c++11 -fPIC -c ../dev/sound/DFSoundCard.cpp 
# g++ -std=c++11 -fPIC -c ../dev/serial/Serial.cpp 
# g++ -std=c++11 -fPIC -c ../dev/gpio/sx1509/SparkFunSX1509.cpp 
# echo Compiling Virtual Console layer
# g++ -std=c++11 -fPIC -c ../XtsConsole.cpp


#echo Compiling Virtual Console layer
#g++ -std=c++11 -fPIC -c ../dev/screen/wiredSPI/SPIWiredScreen.cpp ../dev/sound/DFSoundCard.cpp ../dev/serial/Serial.cpp ../dev/gpio/sx1509/SparkFunSX1509.cpp ../XtsConsole.cpp 

echo Compiling 'main'
g++ -std=c++11 -fPIC -c main.cpp

echo linking
g++ *.o -o xgb -lpthread 



