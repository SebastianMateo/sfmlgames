#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameManager.h"
#include "Player.h"
#include "Ball.h"

int main()
{
    const unsigned int FPS = 60; //The desired FPS. (The number of updates each second).

    sf::RenderWindow window(sf::VideoMode(GameManager::SCREEN_WITDTH, GameManager::SCREEN_HEIGHT), "Basic Poing");
    window.setFramerateLimit(FPS);

    //Create the paddle and the ball
    Player player1(GameManager::Side::PLAYER_1);
    Player player2(GameManager::Side::PLAYER_2);
    Ball ball;

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

        //Check collisions
        ball.checkCollision(player1);
        ball.checkCollision(player2);

        //Draw stuff
        player1.update(window);
        player2.update(window);
        ball.update(window);
        GameManager::getInstance().update(window);

        //Call after everything is drawn
        window.display();
    }
}