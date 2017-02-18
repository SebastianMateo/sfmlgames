#include "stdafx.h"
#include "Player.h"

Player::Player(GameManager::Side side)
    : shape(sf::Vector2f(PADDLE_HEIGHT, PADDLE_WIDTH))
    , side(side)
{
    if (side == GameManager::Side::PLAYER_1)
        shape.setPosition(0.0f, 0.0f);
    else
        shape.setPosition(GameManager::SCREEN_WITDTH - PADDLE_HEIGHT, GameManager::SCREEN_HEIGHT - PADDLE_WIDTH);
}

void Player::update(sf::RenderWindow& window)
{
    //Left player will move with W and A, right player with UP and DOWN

    //Check for keyboard input
    bool moveUp = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && side == GameManager::Side::PLAYER_1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && side == GameManager::Side::PLAYER_2);
    if (moveUp && top() > 0)
        shape.move(0.0f, -SPEED);

    bool moveDown = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && side == GameManager::Side::PLAYER_1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && side == GameManager::Side::PLAYER_2);
    if (moveDown && bottom() < GameManager::SCREEN_HEIGHT)
        shape.move(0.0f, SPEED);

    //Draw the paddle
    window.draw(shape);
}