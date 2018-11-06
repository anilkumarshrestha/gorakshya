//configuration file of game


//#include <SFML/audio.hpp>
#include <GL/glew.h>
#include <GL/glm/glm.hpp>
#include <iostream>
#include <mingw.thread.h>
#include <string>
#include "source/GameEngine/GameEngine.hpp"
#include <GL/glm/gtc/matrix_transform.hpp>
#include <SFML/system/Time.hpp>
#include <SFML/system/Clock.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <vector>

#define Array std::vector

using namespace std;

#ifndef GAME_NAME
#define GAME_NAME "Army Game"
#endif

#ifdef _cplusplus
extern "C"{
#endif


#ifdef _cplusplus
}
#endif

int TIME_PER_FRAME = 34;//17 for 60fps