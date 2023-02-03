cls
cd build
g++ -o game "../src/platform.cpp" "../src/entity.cpp" "../src/collision.cpp" "../src/main.cpp" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
.\game.exe