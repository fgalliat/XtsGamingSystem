clear
 mkdir build 2>/dev/null

#MODE="DESKTOP"

# Oui pour emulation de la console !!!
MODE="XTSCONSOLE"

if [ "$1" = "arm" ]
then
 # Arietta version
 . ../arietta.arch
else
 # Desktop version
 . ../desktop.arch
fi




DEPS="$CPPs"

echo "Mode : $MODE"

for i in $DEPS
do
 echo "Compiling CORE $i"
 if [ -f build/$(basename $i).o ] 
 then
   echo "Skip."
 else
   g++ -std=c++11 -fPIC -fpermissive -D$ARCH $DIRECTIVES -I include -c ../$i -o build/$(basename $i).o
 fi
done

for i in $( ls *.cpp ) 
do
 echo "Compiling $i"
 if [ -f build/$(basename $i).o ] 
 then
    echo "Skip."
 else
    g++ -std=c++11 -fPIC -I . -D$MODE -c $i -o build/$i.o
 fi
done

echo "Linking whole"
 if [ "$MODE" = "DESKTOP" ] 
 then
   # g++ build/*.o -o ./xnes -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
   echo "Oups !"
 else
   g++ build/*.o -o ./xgb $LIBS -lpthread
 fi