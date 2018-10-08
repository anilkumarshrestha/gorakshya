#include "loadShader.hpp"



GLuint LoadShader(const char * vertexPath,const char * fragmentPath){
	//create vertex shader
	GLuint VertexID = glCreateShader(GL_VERTEX_SHADER);
	//create fragment shader
	GLuint FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string ShaderCode;

}