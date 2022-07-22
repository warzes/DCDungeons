@call emcc -std=c++2b -Os -Wall -fno-rtti -fno-exceptions -s USE_SDL=2 -s FORCE_FILESYSTEM=1 -o ../bin/game.html --preload-file ../bin/data/@data/ -I. -I../source/3rdparty/ ../source/Game/Engine.cpp ../source/Game/Game.cpp ../source/Game/GameData.cpp ../source/Game/GameRender.cpp ../source/Game/GameUpdate.cpp ../source/Game/main.cpp

ren "../bin/game.html" "../bin/index.html"