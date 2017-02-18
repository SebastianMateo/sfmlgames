#include "stdafx.h"
#include "Ball.h"
#include "GameManager.h"

Ball::Ball()
{
    shape.setPosition(INITIAL_BALL_X, INITIAL_BALL_Y);
    shape.setRadius(BALL_RADIUS);
    shape.setFillColor(sf::Color::Red);
}

void Ball::update(sf::RenderWindow& window)
{
    //Move the ball
    shape.move(speed);

    //If it moves to the sides of the screen, just for now we reset it to the Right
    if (right() < 0)
    {
        //Score the player 2
        shape.setPosition(GameManager::SCREEN_WITDTH / 2, shape.getPosition().y);
        speed.x = -speed.x;
        GameManager::getInstance().score(GameManager::Side::PLAYER_2);
    }
    else if (left() > GameManager::SCREEN_WITDTH)
    {
        //Score de player 1
        shape.setPosition(GameManager::SCREEN_WITDTH / 2, shape.getPosition().y);
        speed.x = -speed.x;
        GameManager::getInstance().score(GameManager::Side::PLAYER_1);
    }

    if (top() < 0 || bottom() > 300)
        speed.y = -speed.y;

    //Draw the ball
    window.draw(shape);
}

void Ball::checkCollision(Entity& paddle)
{
    //Check collision with paddle
    if (intersects(paddle))
        speed.x = -speed.x;
}