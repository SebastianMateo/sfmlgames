#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "BoardView.h"
#include "Constants.h"
#include "Util.h"
#include "Solver.h"
#include <cassert>

std::string levels[] =
{
    "3|E,E,E;E,R1,G;E,E,E|R", //0
    "3|E,E,E;E,R1,G;E,E,E|R", //1
    "3|E,E,E;R2,E,G;E,E,E|R", //2
    "3|E,E,P;Y2,E,P;E,E,P|Y", //3
    "3|E,E,E;R3,E,Y;E,G,E|R", //4
    "3|E,Y,Y;G3,E,P;E,E,P|G", //5
    "3|E,E,E;R1,E,Y1;E,G1,E|Y", //6
    "3|E,G,G1;R2,E,Y;E,E,Y|R", //7
    "4|P,P,G,G1;R1,E,E,R;R,E,E,R1;Y1,Y,B1,B|G", //8
    "4|P,P1,G,G1;R,E,E,R;R,E,E,R2;Y1,Y1,B,E|P", //9
    "4|R,R,G,G;R,B,B1,G;E,Y,Y,E;E,Y3,Y3,E|B", //10
    "4|B,Y,E,Y;R,Y,G2,Y;R,E,G2,E;B1,E,E,E|G", //11
    "5|B,B2,E,P,P;B,E,E,E,P2;E,E,Y2,E,E;R2,E,E,E,G;R,R,E,G2,G|Y", //12
    "5|P,Y1,E,Y1,P;Y1,E,R1,E,Y1;E,R1,G3,R1,E;Y1,E,R1,E,Y1;P,Y1,E,Y1,P|G", //13
    "5|R,G1,E,G1,R;G1,E,Y1,E,G1;E,Y1,P1,Y1,E;G1,E,P,E,G1;R,G1,E,G2,R|P", //14 TODO Can't beat
    "5|R,G1,E,G1,R;G1,E,Y1,E,G1;E,Y1,P1,Y1,E;G1,E,P,E,G1;R,G1,E,G2,R|P", //15 TODO 
    "4|R,R1,E,R;E,G1,E,G;E,G,E,G;B1,G,B3,G|B", //16
    "5|R,R2,E,G,G;R,E,E,E,G2;E,E,P1,E,E;Y2,E,E,E,B;Y,Y,E,B2,B|B", //17
    "5|Y2,Y1,Y1,Y1,Y1;E,E,E,E,E;G,G,G,G,G2;E,E,E,E,E;R2,R1,R1,R1,R1|G", //18
    "5|G,Y1,Y2,E,G;E,E,E,E,G;R3,P2,G,Y,G1;E,E,E,E,G;B,B,B2,E,G|B", //19
};

int main()
{
    const unsigned int FPS = 60; //The desired FPS. (The number of updates each second).

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITDTH, SCREEN_HEIGHT), "Puralax");
    window.setFramerateLimit(FPS);

    sf::Clock clock; // starts the clock

    /*// Run all levels
    for (int i = 1; i <= 13; i++)
    {
        Board board(levels[i]);
        std::cout << "Level " << i << std::endl;
        bool found = findSolution(board);
        assert(found == true);
    }
    */

    sf::Time elapsed = clock.getElapsedTime();
    std::cout << "Time: " << elapsed.asSeconds() << std::endl;

    Board board(levels[1]);
    BoardView boardView(board);

    sf::Event event;

    bool buttonPressed = false;
    while (window.isOpen())
    {
        //Handle events
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //Calculates the Path
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
            {
                auto movements = board.getAvailableMovements();
                std::for_each(movements.begin(), movements.end(), [](Board::Movement &m) { std::cout << m.fromX + 1 << "," << m.fromY + 1<< "->" << m.toX + 1 << "," << m.toY + 1 << std::endl; });
            }

            //Find the solution
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                findSolution(board);
            }

            //Handle mouse press
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!buttonPressed)
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    if (localPosition.x > 0 && localPosition.x < SCREEN_WITDTH && localPosition.y > 0 && localPosition.y < SCREEN_HEIGHT)
                    {
                        boardView.pressTile(localPosition);
                        buttonPressed = true;
                    }
                }
            }
            else 
            {
                buttonPressed = false;
            }
        }

        // Draw stuff
        window.clear();

        //Draw stuff
        boardView.update(window);

        //Call after everything is drawn
        window.display();
    }
}