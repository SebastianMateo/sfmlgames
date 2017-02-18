#pragma once
#include "Entity.h"
#include "GameManager.h"

class Player : public Entity {
public:

    Player(GameManager::Side side); 

    void update(sf::RenderWindow& window);

protected:

    GameManager::Side side;
    sf::Shape& getShape() { return shape; }

    float x() { return shape.getPosition().x; }
    float y() { return shape.getPosition().y; }
    float top() { return y(); }
    float bottom() { return y() + shape.getSize().y; }

private:
    const int PADDLE_WIDTH = 50.0f;
    const int PADDLE_HEIGHT = 10.0f;
    const int SPEED = 5.0f;

    sf::RectangleShape shape;
};