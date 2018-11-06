#ifndef __LoadShader
#define __LoadShader
#include <GL/glew.h>
#include "../GameEngine.hpp"
#include <fstream>
GLuint LoadShaders(const char * vertexPath,const char * fragmentPath);

#endif