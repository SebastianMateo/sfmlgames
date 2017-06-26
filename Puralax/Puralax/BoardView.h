#pragma once

#include "Board.h"

class BoardView {
public:

    class TileView 
    {
        public: 
            TileView(Node* node, sf::Font& font, int size)
            {
                //Set the shape
                shape = sf::RectangleShape(sf::Vector2f(size, size));
                shape.setPosition(node->y * size, node->x * size);
                setTileColor(node->getColor());

                //Set the text
                text.setFont(font);
                text.setPosition(node->y * size, node->x * size);
                text.setString(std::to_string(node->getAmount()));
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::Black);

                x = node->x;
                y = node->y;
                mNode = node;
            }

            void draw(sf::RenderWindow& window)
            {
                window.draw(shape);
                window.draw(text);
            }

            void refresh()
            {
                Node::Color color = mNode->getColor();
                setTileColor(color);

                //Update the text
                int amount = mNode->getAmount();
                text.setString(std::to_string(amount));
            }

            void select();
            void unselect();
            void setTileColor(Node::Color color);

            int x, y;
        private:
            Node* mNode;
            sf::Text text;
            sf::RectangleShape shape;
    };
    BoardView(Board& board);
    ~BoardView();

    void refresh();

    TileView* BoardView::getTile(sf::Vector2i pos);

    TileView* getSelectedTile() { return mSelectedTile; }

    void pressTile(sf::Vector2i pos);
    bool hasSelectedTile() { return mSelectedTile != nullptr; }
    void unselectTile();
    void setSelectedTile(sf::Vector2i pos);

    void update(sf::RenderWindow& window);

private:
    Board& board;

    int mTileSize;
    sf::Font font;
    TileView* mSelectedTile = nullptr;
    void BoardView::setTileColor(sf::RectangleShape &tile, Node::Color color);

    std::vector< std::vector <TileView*> > mapTiles;
};
