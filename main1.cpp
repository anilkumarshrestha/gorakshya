#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int *a;
void renderingThread(sf::Window* window)
{
    // activate the window's context
    window->setActive(true);

    // the rendering loop

    while (window->isOpen())
    {
        // handle events
        sf::Event event;

        while (window->pollEvent(event))
        {
        	*a+=1;
        	if (*a==100){
        		*a=0;
        		std::cout<<"bipin"<<std::endl;
        	}
            if (event.type == sf::Event::Closed)
            {
                // end the program
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window->display();
    }
}

int main()
{
	*a = 0;
    // create the window (remember: it's safer to create it in the main thread due to OS limitations)
    sf::Window window(sf::VideoMode(800, 600), "OpenGL");

    // deactivate its OpenGL context
    window.setActive(false);

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();
    // run the main loop
    while (window.isOpen())
    {

    }

    // release resources...

    return 0;
}