#include "BoardView.h"
#include "Constants.h"

void BoardView::TileView::select()
{
    auto color = shape.getFillColor();
    shape.setFillColor(color - sf::Color(0, 0, 0, 125));
}

void BoardView::TileView::unselect()
{
    auto color = shape.getFillColor();
    shape.setFillColor(color + sf::Color(0, 0, 0, 125));
}

void BoardView::TileView::setTileColor(Node::Color color)
{
    switch (color)
    {
    case Node::Color::EMPTY:
        shape.setFillColor(sf::Color::White);
        break;
    case Node::Color::RED:
        shape.setFillColor(sf::Color::Red);
        break;
    case Node::Color::GREEN:
        shape.setFillColor(sf::Color::Green);
        break;
    case Node::Color::YELLOW:
        shape.setFillColor(sf::Color::Yellow);
        break;
    case Node::Color::PURPLE:
        shape.setFillColor(sf::Color::Magenta);
        break;
    case Node::Color::BLUE:
        shape.setFillColor(sf::Color::Blue);
        break;
    }
}

BoardView::BoardView(Board& board) : board(board), mapTiles(board.getSize(), std::vector<TileView*>(board.getSize()))
{
    mTileSize = SCREEN_WITDTH / board.getSize();

    font.loadFromFile("arial.ttf");

    //Set the tiles state
    for (int i = 0; i < board.getSize() ; i++)
    {
        for (int j = 0; j < board.getSize(); j++)
        {
            //Set the node
            Node* node = board.getNode(i, j);
            mapTiles[i][j] = new TileView(node, font, mTileSize);
        }
    }
}
BoardView::~BoardView()
{
    for (auto column : mapTiles)
    {
        for (auto tile : column)
        {
            delete tile;
        }
    }
}

BoardView::TileView* BoardView::getTile(sf::Vector2i pos)
{
    int j = static_cast<int>(pos.x / mTileSize);
    int i = static_cast<int>(pos.y / mTileSize);

    return mapTiles[i][j];
}

void BoardView::unselectTile()
{
    mSelectedTile->unselect();
    mSelectedTile = nullptr;
}

void BoardView::pressTile(sf::Vector2i position)
{
    auto newTile = getTile(position);

    //If we already had a tile selected, we try to move
    if (hasSelectedTile())
    {
        auto fromTile = getSelectedTile();

        if (fromTile != newTile)
        {
            if (board.move(fromTile->x, fromTile->y, newTile->x, newTile->y))
            {
                unselectTile();
                refresh();
            }
        }
        else
        {
            unselectTile();
        }
    }
    //Else, if the tile is movable we select it
    else
    {
        if (board.canMove(newTile->x, newTile->y))
        {
            setSelectedTile(position);
        }
    }
}

void BoardView::setSelectedTile(sf::Vector2i pos)
{
    auto tile = getTile(pos);
    tile->select();
    mSelectedTile = tile;
}

void BoardView::update(sf::RenderWindow& window)
{
    for (auto &row : mapTiles)
    {
        for (auto &col : row)
        {
            col->draw(window);
        }
    }
}

void BoardView::refresh()
{
    for (int i = 0; i < board.getSize(); i++)
    {
        for (int j = 0; j < board.getSize(); j++)
        {
            mapTiles[i][j]->refresh();
        }
    }
}