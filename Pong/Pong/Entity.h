#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    bool intersects(Entity &other);

protected:
    virtual sf::Shape& getShape() = 0;
};