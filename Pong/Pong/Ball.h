#pragma once
#include "Entity.h"
#include "GameManager.h"

class Ball : public Entity {
public:
    Ball();

    void update(sf::RenderWindow& window);

    void checkCollision(Entity& paddle); 

    sf::Shape& getShape() { return shape; }

private:
    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float left() { return x(); }
    float right() { return x() + shape.getRadius() * 2; }
    float top() { return y(); }
    float bottom() { return y() + shape.getRadius() * 2; }

    const int BALL_RADIUS = 5.0f;
    const int SPEED_X = 5.0f;
    const int SPEED_Y = 4.0f;
    const int INITIAL_BALL_X = GameManager::SCREEN_WITDTH / 2;
    const int INITIAL_BALL_Y = GameManager::SCREEN_HEIGHT / 2;

    sf::CircleShape shape;
    sf::Vector2f speed{ -SPEED_X, -SPEED_Y };
};
