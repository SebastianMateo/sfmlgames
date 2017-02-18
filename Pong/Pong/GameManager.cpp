#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
    font.loadFromFile("arial.ttf");

    scorePlayer1Text = sf::Text("0", font, 24);
    scorePlayer1Text.setPosition(SCREEN_WITDTH / 2 - 20, 0);

    scorePlayer2Text = sf::Text("0", font, 24);
    scorePlayer2Text.setPosition(SCREEN_WITDTH / 2 + 20, 0);
}

void GameManager::update(sf::RenderWindow& window)
{
    window.draw(scorePlayer1Text);
    window.draw(scorePlayer2Text);
}

void GameManager::score(GameManager::Side side)
{
    if (side == Side::PLAYER_1)
    {
        scorePlayer1++;
        scorePlayer1Text.setString(std::to_string(scorePlayer1));
    }
    else
    {
        scorePlayer2++;
        scorePlayer2Text.setString(std::to_string(scorePlayer2));
    }
}

void GameManager::reset()
{
    scorePlayer1 = 0;
    scorePlayer2 = 0;
    scorePlayer1Text.setString(std::to_string(0));
    scorePlayer2Text.setString(std::to_string(0));
}