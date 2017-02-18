#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

class GameManager
{
public:
    enum class Side {
        PLAYER_1,
        PLAYER_2
    };

    static const int SCREEN_WITDTH = 500;
    static const int SCREEN_HEIGHT = 300;

    inline static GameManager& getInstance() { static GameManager instance; return instance; }

    void update(sf::RenderWindow& window);
    void score(GameManager::Side side);
    void reset();

private:
    int scorePlayer1 = 0;
    int scorePlayer2 = 0;
    sf::Text scorePlayer1Text;
    sf::Text scorePlayer2Text;
    sf::Font font;

    GameManager();

public:
    GameManager(GameManager const&) = delete;
    void operator=(GameManager const&) = delete;
};
