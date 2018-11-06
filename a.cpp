#include <SFML/Graphics.hpp>
#define SFML_STATIC
int main()
{
    sf::RenderWindow win(sf::VideoMode(200, 200), "SFML Test");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
        }

        win.clear();
        win.draw(shape);
        win.display();
    }

    return 0;
}