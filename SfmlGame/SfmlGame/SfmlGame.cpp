#include <SFML/Graphics.hpp>

int main()
{
    const unsigned int FPS = 60; //The desired FPS. (The number of updates each second).

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sfml Game");
    window.setFramerateLimit(FPS);

    //Main loop event
    sf::Event event;
    while (window.isOpen())
    {
        //Handle events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Draw stuff
        window.clear();

        //Call after everything is drawn
        window.display();
    }
}