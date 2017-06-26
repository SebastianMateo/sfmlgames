#pragma once
#include <set>
#include <list>
#include <SFML/Graphics.hpp>

class Board;

class Node {
public:
    enum class Color {
        EMPTY,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        PURPLE
    };

    Node(int x, int y, const char color, int amount, Board* board);
    Node(int x, int y, Color color, int amount, Board* board);

    bool capture(Node *toNode);
    void propagate(Node::Color fromColor, Node::Color toColor, std::set<Node*> propagatedNodes);

    inline const bool operator == (const Node &n) const { return x == n.x && y == n.y; }

    inline int distanceTo(const Node &other) const { return std::abs(other.y - y) + std::abs(other.x - x); }

    inline int getAmount() { return mAmount; }
    int x, y;

    Color getColor() { return mColor; }
    void setColor(Color color) { mColor = color; }

    static Color parseColor(char color);

    friend class Board;
private:

    const bool canMove() { return /*mColor != Color::EMPTY &&*/ mAmount > 0; }
    const bool isNeighbor(int x, int y) { return true; }

    Board* mBoard;
    Color mColor;
    int mAmount;
};

class Board {
public:
    struct Movement 
    {
        Movement(int fromX, int fromY, int toX,  int toY) : fromX(fromX), fromY(fromY), toX(toX), toY(toY) { }
        int fromX;
        int fromY;
        int toX;
        int toY;
    };

    Board(const int size, const std::string level, const char winningColor);
    Board::Board(const std::string level);
    Board::Board(const Board& board);
    Board::~Board();

    Node* getNode(int x, int y) { return map[x][y]; }
    std::vector<Node*> getNeighbors(Node *node);

    std::list<Movement> getAvailableMovements();

    std::string hash();

    bool move(int fromX, int fromY, int toX, int toY);
    bool canMove(int x, int y) { return map[x][y]->canMove(); }

    const int inline getSize() { return mSize; }

    bool didWeWon();
    bool didWeLost();
private:

    int mSize;
    Node::Color mWinningColor;
    std::vector< std::vector <Node*> > map;
};