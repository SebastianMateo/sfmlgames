#include "Board.h"
#include <list>
#include <iostream>

bool doMovement(Board board, Board::Movement movement, std::set<std::string> *boardHash)
{
    //First we do the movement
    board.move(movement.fromX, movement.fromY, movement.toX, movement.toY);
    //std::cout << movement.fromX + 1 << "," << movement.fromY + 1 << "->" << movement.toX + 1 << "," << movement.toY + 1 << std::endl;

    //If we won we can return
    if (board.didWeWon())
    {
        return true;
    }
    else if (board.didWeLost())
    {
        return false;
    }
    else
    {
        //Then we check if we were already on this position
        //If we find it, it means we were already in this position, so we can discard this
        std::string hash = board.hash();
        if (boardHash->find(hash) != boardHash->end())
        {
            return false;
        }

        //Else we get the new movements for this position and iterate
        auto availableMovements = board.getAvailableMovements();
        for (auto m : availableMovements)
        {
            //If we already won on this movement, we should be returning it
            if (doMovement(board, m, boardHash))
            {
                std::cout << m.fromX + 1 << "," << m.fromY + 1 << "->" << m.toX + 1 << "," << m.toY + 1 << std::endl;
                return true;
            }
        }
        return false;
    }
}

bool findSolution(Board board)
{
    //First we find all available movements
    auto availableMovements = board.getAvailableMovements();

    std::set<std::string> boardHash;

    //Board - Available Movements
    //Those momvements are going to be on a particular board
    for (auto m : availableMovements)
    {
        if (doMovement(board, m, &boardHash))
        {
            std::cout << m.fromX + 1 << "," << m.fromY + 1 << "->" << m.toX + 1 << "," << m.toY + 1 << std::endl;
            std::cout << "Solution found" << std::endl;
            return true;
        }
    }

    std::cout << "No solution found" << std::endl;
    return false;
}