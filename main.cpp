#include "config.h"


GLuint programID;
/*void OpenGlStufs(){


}*/

#ifdef main
#undef main
#endif
int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(800, 600), GAME_NAME); //GAME_NAME linked to config.h and reflects the name of the window
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Hand))
        window.setMouseCursor(cursor);
    glEnable(GL_TEXTURE_3D);

        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
            getchar();
        }
            programID =  LoadShaders("v.vertexshader","f.fragmentshader");
            GLuint MatrixID = glGetUniformLocation(programID, "MVP");
            GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
            //GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
            
           //GLuint Texture = loadDDS("uvmap.DDS");
            //sf::Texture Texture;
            //Texture.loadFromFile("grass.jpg");
            //Texture.setRepeated(true);

            //GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");


            Array<unsigned short> indices;
            Array<glm::vec3> vertices;
            Array<glm::vec2> uvs;
            Array<glm::vec3> normals;
            std::cout<<"No of vertices"<<vertices.size()<<std::endl;
            std::cout<<"No of normals"<<normals.size()<<std::endl;
            bool res = loadAssImp("cube.obj", indices, vertices, uvs, normals);
            std::cout<<"Loaded"<<res<<std::endl;
            std::cout<<"No of vertices"<<vertices.size()<<std::endl;
            std::cout<<"No of normals"<<normals.size()<<std::endl;

            GLuint vertexbuffer;
            glGenBuffers(1, &vertexbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            /*GLuint uvbuffer;
            glGenBuffers(1, &uvbuffer);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);*/


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                sf::Vector2u myCurrentSize = window.getSize();
                std::cout<<myCurrentSize.x<<myCurrentSize.y<<std::endl;
            }
        }
        
        window.clear();
        window.setActive();
        //window.draw();




        
        glUseProgram(programID);
        //glViewport(0,0,1024,1024);

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glm::mat4 ProjectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
            glm::mat4 ViewMatrix       = glm::lookAt(
                                glm::vec3(0,0,10),           // Camera is here
                                glm::vec3( 0, 0, -4), // and looks here : at the same position, plus "direction"
                                glm::vec3( 0, 10, 0 )                  // Head is up (set to 0,-1,0 to look upside-down)
                           );
            glm::mat4 ModelMatrix = glm::mat4(0.1f);
            ModelMatrix = glm::rotate(ModelMatrix, 1.3f, glm::vec3(0.0f, 1.0f, 1.0f));
            glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

            /*glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Texture);
            // Set our "myTextureSampler" sampler to user Texture Unit 0
            glUniform1i(TextureID, 0);*/

            glEnableVertexAttribArray(vertexPosition_modelspaceID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                vertexPosition_modelspaceID,  // The attribute we want to configure
                3,                            // size
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*)0                      // array buffer offset
            );

            // 2nd attribute buffer : UVs
            /*glEnableVertexAttribArray(vertexUVID);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                vertexUVID,                   // The attribute we want to configure
                2,                            // size : U+V => 2
                GL_FLOAT,                     // type
                GL_FALSE,                     // normalized?
                0,                            // stride
                (void*)0                      // array buffer offset
            );*/

            // Draw the triangles !
            glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

            glDisableVertexAttribArray(vertexPosition_modelspaceID);
            //glDisableVertexAttribArray(vertexUVID);
    /*glBegin(GL_TRIANGLES);
        glVertex3f(0.5f,1.0f,0.6f);
        glVertex3f(0.0f,1.0f,0.6f);
        glVertex3f(1.0f,0.0f,0.6f);
    glEnd();*/














        window.display();
    }
    return EXIT_SUCCESS;
}
