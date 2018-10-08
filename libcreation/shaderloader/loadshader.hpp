#ifndef SHADER_DLL_H
#define SHADER_DLL_H

#ifdef BUILDING_SHADER_DLL
#define SHADER_DLL __declspec(dllexport)
#else
#define SHADER_DLL __declspec(dllimport)
#endif
/*
	//loads Shader(GLSL) programs
	//returns program Id
*/
GLuint LoadShader(const char * vertexPath,const char * fragmentPath);

#endif	