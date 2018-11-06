#include "config.h"

#include <cstdlib>

#define MAX_BONES 100
#define CO std::cout
int x=1024, y=800;
GLuint programID;

GLuint Matrixbone[MAX_BONES];
void UniformLoaction_Of_Bones(GLuint programId){
    for (int i=0; i<MAX_BONES; i++){
        std::string as = "bones[" + to_string(i) + "]";
        Matrixbone[i] = glGetUniformLocation(programID, as.c_str());
    }
}
void renderingThread(sf::Window* window)
{
    window->setActive(true);


    //GLuint abce = img::loadImageToTexture("a.jpg");
    //CO<<abce<<std::endl;

    programID =  LoadShaders("v.vertexshader","f.fragmentshader");
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    UniformLoaction_Of_Bones(programID);

    GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    GLuint bone_ids = glGetAttribLocation(programID, "bone_ids");
    GLuint weights = glGetAttribLocation(programID, "weights");
    GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");

    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    modelLoader Me;
    Me.loadFile("res/model1.dae");


    int width, height;
    GLuint Texture = img::loadImageToTexture("res/diffuse.png", &width, &height);
    CO<<"Texture Id"<<Texture<<"\t"<<width<<"\t"<<height<<std::endl;

    CO<<"NO OF VERTICES "<<Me.Nodes.at(0).meshes.at(0).vertices.size()<<std::endl;
    GLuint BoneIdBuffer;
    glGenBuffers(1, &BoneIdBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, BoneIdBuffer);
    glBufferData(GL_ARRAY_BUFFER, Me.Nodes.at(0).meshes.at(0).jointId_for_each_Vertex.size() * sizeof(int), &Me.Nodes.at(0).meshes.at(0).jointId_for_each_Vertex[0], GL_STATIC_DRAW);


    GLuint weightsBuffer;
    glGenBuffers(1, &weightsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, weightsBuffer);
    glBufferData(GL_ARRAY_BUFFER, Me.Nodes.at(0).meshes.at(0).weight_of_each_Vertex_with_bone.size() * sizeof(float), &Me.Nodes.at(0).meshes.at(0).weight_of_each_Vertex_with_bone[0], GL_STATIC_DRAW);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, Me.Nodes.at(0).meshes.at(0).vertices.size() * sizeof(glm::vec3), &Me.Nodes.at(0).meshes.at(0).vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, Me.Nodes.at(0).meshes.at(0).texture_coordinate.size() * sizeof(glm::vec2), &Me.Nodes.at(0).meshes.at(0).texture_coordinate[0], GL_STATIC_DRAW);
    

    //glDisable(GL_CULL_FACE);

    // Enable depth test
    //glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    //glDepthFunc(GL_LESS);

    /*glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);*/
    glDisable( GL_CULL_FACE );
    glCullFace ( GL_BACK );
    glFrontFace ( GL_CW );
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    int FPS = 0;
    sf::Clock clock,clock1;

    float abcdef=0.0f;
    //window->setActive();
        //glEnable(GL_DEPTH_TEST);

    while (window->isOpen())
    {
        sf::Time time1 = clock.getElapsedTime();

        

        window->setActive();
        
        glViewport(0,0,x,y);
        glScissor ( 0, 0, x, y );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



        //glDepthFunc(GL_NEVER);

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        //glClearDepth(0.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        

        glUseProgram(programID);
        //glFlush();

        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

        
        //glFrontFace(GL_CCW); 

        //glEnable(GL_DEPTH_TEST);
        //glDepthMask(GL_FALSE); 
        //glDepthFunc(GL_ALWAYS);

            glm::mat4 ProjectionMatrix = glm::perspective(70.0f, 1366.0f / 768.0f, 0.01f, 1000.0f);
            glm::mat4 ViewMatrix       = glm::lookAt(
                                glm::vec3(0,0,10),   
                                glm::vec3(0,0,7), 
                                glm::vec3( 0, 1, 0 )         
                           );
            glm::mat4 ModelMatrix = glm::mat4(1);

            
            ModelMatrix = glm::rotate(ModelMatrix, abcdef, glm::vec3(1.0f, 1.0f, 1.0f));
            abcdef=abcdef+0.07f;

            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f,0.5f,0.5f));
            //ModelMatrix = glm::translate(ModelMatrix, glm::vec3(1.0f,1.0f,0.0f));
            glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;



            glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Texture);
            glUniform1i(TextureID, 0);


            for (unsigned int i=0;i<Me.Nodes.at(0).meshes.at(0).Joints_Information.size();i++){ 

                glm::mat4 BoneMatrix = Me.Nodes.at(0).meshes.at(0).Joints_Information.at(i).matrix_InverseBoneMatrix;
                glUniformMatrix4fv(Matrixbone[i], 1, GL_FALSE, &BoneMatrix[0][0]);
            }



            glEnableVertexAttribArray(bone_ids);
            glBindBuffer(GL_ARRAY_BUFFER, BoneIdBuffer);
            glVertexAttribPointer(
                bone_ids,  
                3,                            
                GL_INT,                     
                GL_FALSE,                     
                0,                            
                (void*)0                      
            );

            glEnableVertexAttribArray(weights);
            glBindBuffer(GL_ARRAY_BUFFER, weightsBuffer);
            glVertexAttribPointer(
                weights,  
                3,                            
                GL_FLOAT,                     
                GL_FALSE,                     
                0,                            
                (void*)0                      
            );
            glEnableVertexAttribArray(vertexUVID);
            glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
            glVertexAttribPointer(
                vertexUVID,
                2,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void*)0
            );

            glEnableVertexAttribArray(vertexPosition_modelspaceID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                vertexPosition_modelspaceID,  
                3,                            
                GL_FLOAT,                     
                GL_FALSE,                     
                0,                            
                (void*)0                      
            ); 

            // Draw the triangles !



            glDrawArrays(GL_TRIANGLES, 0,  Me.Nodes.at(0).meshes.at(0).vertices.size());



            glDisableVertexAttribArray(bone_ids);
            glDisableVertexAttribArray(vertexPosition_modelspaceID);
            glDisableVertexAttribArray(weights);
            glDisableVertexAttribArray(vertexUVID);















        window->display();
        FPS +=1;
        sf::Time timeSec;
        timeSec= sf::seconds(1.0f);
        if (timeSec<=time1){
            std::cout<<"FPS= "<<FPS<<std::endl;
            sf::Time time2 = clock.restart();
            FPS=0;
        }
        sf::Time forFPS = clock1.getElapsedTime();
        
        if (forFPS.asMilliseconds()<TIME_PER_FRAME){
            while (forFPS.asMilliseconds()<TIME_PER_FRAME){forFPS = clock1.getElapsedTime();}

        }
        sf::Time forFPS1 = clock1.restart();
        
    }

    /*if(Texture){//Do when Texture not needed
        glDeleteTextures(1, &Texture);
        Texture = 0;
    }*/

}
#ifdef main
#undef main
#endif
int main(int argc, char** argv)
{

        // Request a 24-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 24;
    contextSettings.sRgbCapable = false;

        // Create the main window
    sf::RenderWindow window(sf::VideoMode(1366, 768),GAME_NAME, 1<<2 , contextSettings);
    window.setVerticalSyncEnabled(true);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
    }
    window.setActive(false);
    std::thread threads (&renderingThread,&window);

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
                x=myCurrentSize.x;y=myCurrentSize.y;
            }
        }
    }
    threads.join();
    glDeleteProgram(programID);
    return EXIT_SUCCESS;
}
