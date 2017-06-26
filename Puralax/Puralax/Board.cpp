#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Util.h"
#include <cmath>
#include <iostream>

void Node::propagate(Node::Color capturedColor, Node::Color propagatedColor, std::set<Node*> propagatedNodes)
{
    //First we add to the set of propagated nodes
    propagatedNodes.insert(this);

    //Unless the color is the one of the captured, we stop
    if (mColor != capturedColor)
        return;

    //We change the color and propagate to neighbor nodes
    mColor = propagatedColor;

    auto neighbors = mBoard->getNeighbors(this);
    for (auto neighbor : neighbors)
    {
        if (propagatedNodes.find(neighbor) == propagatedNodes.end())
        {
            neighbor->propagate(capturedColor, propagatedColor, propagatedNodes);
        }
    }
}

bool Node::capture(Node *toNode)
{
    if (toNode->getColor() == this->getColor())
        return false;

    if (toNode->getColor() == Node::Color::EMPTY)
    {
        //And we set as the current color the toNode
        toNode->setColor(this->getColor());

        //Then we set as empty the fromNode
        this->setColor(Node::Color::EMPTY);

        //We increase the amount of movements of the targeted node to the origin - 1 and the origin to 0
        toNode->mAmount = mAmount - 1;
        mAmount = 0;
    }
    else
    {
        //We need to know what the captured color was
        auto capturedColor = toNode->getColor();
        auto propagatedColor = this->getColor();

        //And we set as the current color the toNode
        toNode->setColor(propagatedColor);

        //Create a set of all propagated nodes and add the toNode and fromNode
        std::set<Node*> propagatedNodes;
        propagatedNodes.insert(this);
        propagatedNodes.insert(toNode);

        //Check all neighbors that are the same color
        auto neighbors = mBoard->getNeighbors(toNode);
        for (auto neighbor : neighbors)
        {
            //If we didn't propated here, we propagate
            if (propagatedNodes.find(neighbor) == propagatedNodes.end())
            {
                neighbor->propagate(capturedColor, propagatedColor, propagatedNodes);
            }
        }

        //Decrease the number of movements
        mAmount--;
    }

    return true;
}

Node::Color Node::parseColor(char color)
{
    switch (color)
    {
    case 'E':
        return Color::EMPTY;
    case 'R':
        return Color::RED;
    case 'G':
        return Color::GREEN;
    case 'Y':
        return Color::YELLOW;
    case 'B':
        return Color::BLUE;
    case 'P':
        return Color::PURPLE;
    }
}

Node::Node(int x, int y, const char color, int amount, Board* board) : x(x), y(y), mAmount(amount), mBoard(board)
{
    mColor = Node::parseColor(color);
}

Node::Node(int x, int y, Color color, int amount, Board* board) : x(x), y(y), mAmount(amount), mColor(color), mBoard(board) { }

//Level in format A,3A,B,C;D,A,C
/* Level Format
E: Empty
R: Red
G: Green
Y: Yellow
B: Blue
P: Purple
Example: "E,E,E;E,R3,E;E,G,E"
*/
Board::Board(const int size, const std::string level, const char winningColor) : mSize(size), map(size, std::vector<Node*>(size))
{
    auto rows = Util::split(level, ";");
    int i = 0;
    for (std::string row : rows)
    {
        int j = 0;
        auto tiles = Util::split(row, ",");

        for (std::string tile : tiles)
        {
            int amount = 0;
            if (tile.size() > 1)
            {
                amount = tile.at(1) - '0';
            }
            map[i][j] = new Node(i, j, tile.at(0), amount, this);
            j++;
        }
        i++;
    }

    mWinningColor = Node::parseColor(winningColor);
}

Board::Board(const std::string fullLevel)
{
    auto level = Util::split(fullLevel, "|");

    auto rows = Util::split(level[1], ";");
    int i = 0;
    for (std::string row : rows)
    {
        int j = 0;
        map.push_back(std::vector<Node*>());

        auto tiles = Util::split(row, ",");

        for (std::string tile : tiles)
        {
            int amount = 0;
            if (tile.size() > 1)
            {
                amount = tile.at(1) - '0';
            }
            map[i].push_back(new Node(i, j, tile.at(0), amount, this));
            j++;
        }
        i++;
    }

    mSize = rows.size();
    mWinningColor = Node::parseColor(level[2].at(0));
}

Board::Board(const Board& board)
{
    mSize = board.mSize;
    mWinningColor = board.mWinningColor;

    int i = 0;
    for (auto row : board.map)
    {
        map.push_back(std::vector<Node*>());

        for (auto node : row)
        {
            map[i].push_back(new Node(node->x, node->y, node->mColor, node->mAmount, this));
        }
        i++;
    }
}

std::string Board::hash()
{
    std::string hashString;

    for (auto row : map)
    {
        for (auto node : row)
        {
            hashString.append(std::to_string(static_cast<int>(node->getColor())));
            hashString.append(std::to_string(node->getAmount()));
        }
    }

    return hashString;
}

std::list<Board::Movement> Board::getAvailableMovements()
{
    std::list <Movement> availableMovements;

    for (auto column : map)
    {
        for (auto node : column)
        {
            if (node->canMove())
            {
                //Check neighbors
                auto neighbors = getNeighbors(node);
                auto color = node->getColor();
                for (auto neighbor : neighbors)
                {
                    if (neighbor->getColor() != color)
                    {
                        availableMovements.push_back(Movement(node->x, node->y, neighbor->x, neighbor->y));
                    }
                }
            }
        }
    }

    return availableMovements;
}

Board::~Board()
{
    for (auto col : map)
    {
        for (auto cel : col)
        {
            delete cel;
        }
    }
}

bool Board::didWeWon()
{
    for (auto col : map)
    {
        for (auto node : col)
        {
            //If the non empty are the same as the winning color
            if (node->getColor() != mWinningColor && node->getColor() != Node::Color::EMPTY)
                return false;
        }
    }

    return true;
}

bool Board::didWeLost()
{
    //We lost if we don't have at least one color of the winning color with movements
    for (auto row : map)
    {
        for (auto node : row)
        {
            //If we have at least one with the winning color with movements, we haven't lost yet
            if (node->getColor() == mWinningColor && node->getAmount() > 0)
                return false;
        }
    }

    return true;
}

bool Board::move(int fromX, int fromY, int toX, int toY)
{
    //Check if the From node can move
    Node *fromNode = map[fromX][fromY];

    if (fromNode->canMove())
    {
        //Check that the other node is adjacent
        if ( (abs(fromX - toX) == 1 && fromY - toY == 0 ) || (fromX - toX == 0 && abs(fromY - toY) == 1) )
        {
            //Capture the other node
            Node *toNode = map[toX][toY];
            return fromNode->capture(toNode);
        }
    }

    return false;
}

std::vector<Node*> Board::getNeighbors(Node *node)
{
    std::vector<Node*> neighbors;

    if (node->x > 0)
        neighbors.push_back(map[node->x - 1][node->y]);

    if (node->y > 0)
        neighbors.push_back(map[node->x][node->y - 1]);

    if (node->x < mSize - 1)
        neighbors.push_back(map[node->x + 1][node->y]);

    if (node->y < mSize - 1)
        neighbors.push_back(map[node->x][node->y + 1]);

    return neighbors;
}