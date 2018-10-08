@echo off
color 17
echo "Compiling"
cd C:\Users\Dell\Documents\project\ArmyGame
g++ -g main.cpp source/GameEngine/renderer/LoadShader.cpp source/GameEngine/renderer/modelLoader.cpp -mwin32 -std=c++11 -o build/debug/a.exe  -L. -lopengl32 -lFLAC -lfreetype -logg -lopenal32 -lsfml-audio-d -lsfml-audio-s-d -lsfml-audio-s -lsfml-audio -lsfml-graphics-d -lsfml-graphics-s-d -lsfml-graphics-s -lsfml-graphics -lsfml-main-d -lsfml-main -lsfml-network-d -lsfml-network-s-d -lsfml-network-s -lsfml-network -lsfml-system-d -lsfml-system-s-d -lsfml-system-s -lsfml-system -lsfml-window-d -lsfml-window-s-d -lsfml-window-s -lsfml-window -lvorbis -lvorbisenc -lvorbisfile  -lglew32 -llibassimp 
cd build/debug/
start a.exe
pause..