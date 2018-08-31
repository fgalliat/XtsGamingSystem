clear
 mkdir build 2>/dev/null

MODE="DESKTOP"
MODE="XTSCONSOLE"

echo "Compilling $1"
 rm build/$1.o
 g++ -std=c++11 -fPIC -I include -D$MODE -c $1 -o build/$1.o

echo "remember to link whole .... !"

# echo "Linking whole"
#  if [ "$MODE" = "DESKTOP" ] 
#  then
#    g++ build/*.o -o ./xnes -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
#  else
#    g++ build/*.o -o ./xnes
#  fi