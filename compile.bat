@echo off
color 0a
:compile
cls
echo Checking if Process already opened
FOR /F %%x IN ('tasklist /FI "IMAGENAME eq a.exe"') DO IF "%%x"=="a.exe" GOTO foundtask
echo No Program running
:noprocessrunning
echo Now Compiling
cd D:\ArmyGame

g++ -g main.cpp source/GameEngine/renderer/LoadShader.cpp source/GameEngine/renderer/modelLoader.cpp source/GameEngine/renderer/imageloader.cpp -std=c++11 -mwin32 -o build/debug/a.exe  -L. -lglew32 -lopengl32 -lFLAC -lfreetype -logg -lopenal32 -lsfml-audio-d -lsfml-audio-s-d -lsfml-audio-s -lsfml-audio -lsfml-graphics-d -lsfml-graphics-s-d -lsfml-graphics-s -lsfml-graphics -lsfml-main-d -lsfml-main -lsfml-network-d -lsfml-network-s-d -lsfml-network-s -lsfml-network -lsfml-system-d -lsfml-system-s-d -lsfml-system-s -lsfml-system -lsfml-window-d -lsfml-window-s-d -lsfml-window-s -lsfml-window -lvorbis -lvorbisenc -lvorbisfile -lglew32 -llibassimp -L build/debug -lSOIL


:option
echo ::::::::::::::::::::::::::::::::::::::::::Options:::::::::::::::::::::::::::::::::::
echo Press Following key to select options
echo r=run the program
echo q=quit the batch operation
echo c=compile the code
echo ..............................................................
echo Enter Option?
SET /p var=

IF "%var%"=="r" (
    goto Start
)
IF "%var%"=="c" (
    goto compile
)
goto Quit

:Start
ECHO Going to path build/debug
cd build/debug/
echo Starting
a.exe>>a.txt
cd ../../
goto option


:Quit
ECHO Exiting BATCH file
pause..
goto tempm

:foundtask
echo Program already opened Exiting Program
TASKKILL /IM a.exe /f
goto noprocessrunning

:tempm
