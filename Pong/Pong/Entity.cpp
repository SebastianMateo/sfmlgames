#include "stdafx.h"
#include "Entity.h"

bool Entity::intersects(Entity &other)
{
    sf::FloatRect rect = this->getShape().getGlobalBounds();
    sf::FloatRect otherRect = other.getShape().getGlobalBounds();
    return (rect.intersects(otherRect));
}