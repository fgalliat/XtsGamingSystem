clear
 mkdir build 2>/dev/null

#MODE="DESKTOP"
MODE="XTSCONSOLE"

#FLAGS="-O3 -march=native -std=c++14 -Wno-unused-value"
#CPP="clang++"

FLAGS="-std=c++11 -Wno-unused-value"
CPP="g++"

for i in $( ls *.cpp ) 
do
 echo "Compiling $i"
 $CPP $FLAGS -fPIC -I include -I lib/include -I simpleini -D$MODE -c $i -o build/$i.o
done

for i in $( ls ./lib/*.cpp ) 
do
 echo "Compiling LIB $i"
 $CPP $FLAGS -fPIC -I include -I lib/include -I simpleini -D$MODE -c $i -o build/$(basename $i).o
done

for i in $( ls ./mappers/*.cpp ) 
do
 echo "Compiling MAPPER $i"
 $CPP $FLAGS -fPIC -I include -I lib/include -I simpleini -D$MODE -c $i -o build/$(basename $i).o
done

echo "Linking whole"
 g++ $FLAGS build/*.o -o ./laines -lSDL2 -lSDL2_image -lSDL2_ttf
