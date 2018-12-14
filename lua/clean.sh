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
 echo "Cleaning CORE $i"
 if [ -f build/$(basename $i).o ] 
 then
   echo "clean. $(basename $i).o"
   rm build/$(basename $i).o
 else
   echo "Skip."
 fi
done

for i in $( ls lxts*.c | grep -v luac.c ) 
do
 echo "Compiling $i"
 if [ -f build/$(basename $i).o ] 
 then
    echo "clean $i.o"
    rm build/$i.o
 else
    echo "Skip."
 fi
done

echo "Cleaning whole"
 if [ "$MODE" = "DESKTOP" ] 
 then
   # g++ build/*.o -o ./xnes -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
   echo "Oups !"
 else
   rm ./lua
 fi