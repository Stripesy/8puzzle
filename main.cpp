/*
Nicholas Vecchio - 20061890
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

#include "Puzzle.h"

/*

https://tristanpenman.com/demos/n-puzzle/

*/

struct cmp
{
    bool operator()(const Puzzle &lhs, const Puzzle &rhs) const
    {
        return lhs.boardLayout < rhs.boardLayout;
    }
};

bool operator<(const Puzzle &lhs, const Puzzle &rhs)
{
    if (lhs.fscore != rhs.fscore)
        return (lhs.fscore < rhs.fscore);
    else
        return (lhs.boardLayout < rhs.boardLayout);
}

void printPath(Puzzle *puzzle);
std::vector<std::vector<int>> readSamples(std::vector<int> &gSVector);
Puzzle aStar(Puzzle puzzle, int numIteration);
Puzzle pushUp(Puzzle puzzle);
Puzzle pushDown(Puzzle puzzle);
Puzzle pushLeft(Puzzle puzzle);
Puzzle pushRight(Puzzle puzzle);

int main()
{
    std::vector<int> gSVector;
    std::vector<std::vector<int>> allSamplesVector = readSamples(gSVector);

    for (int i = 1; i < allSamplesVector.size(); i++)
    {
        Puzzle puzzle(allSamplesVector[i], allSamplesVector[0]);
        Puzzle solved = aStar(puzzle, gSVector[i]);
        printPath(&solved);
    }
}

void printPath(Puzzle *puzzle)
{
    if (puzzle->parent == NULL)
    {
        return;
    }
    else
    {
        printPath(puzzle->parent);
        puzzle->printBoard();
    }
}

Puzzle aStar(Puzzle puzzle, int numIteration)
{
    std::set<Puzzle> openSet;
    std::set<Puzzle> closedSet;

    Puzzle current = puzzle;
    openSet.insert(current);
    while (!openSet.empty())
    {
        current = *openSet.begin();
        openSet.erase(openSet.begin());
        if (current.boardLayout == current.goalLayout)
        {
            std::cout << "Solution found in : " << current.depth << "\nExpected: " << numIteration << std::endl;
            return current;
        }

        Puzzle temp(current);

        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                temp = pushUp(current);
                break;
            case 1:
                temp = pushDown(current);
                break;
            case 2:
                temp = pushLeft(current);
                break;
            case 3:
                temp = pushRight(current);
                break;
            }
            if ((openSet.find(temp) != openSet.end()) || (openSet.find(temp) != openSet.end() && (openSet.find(temp)->fscore < temp.fscore)))
            {
                // check if temp is in open set or better fscore
                continue;
            }
            else if ((closedSet.find(temp) != closedSet.end()) || (closedSet.find(temp) != closedSet.end() && (closedSet.find(temp)->fscore < temp.fscore)))
            {
                // check if in closed set or better fscore
                continue;
            }
            else
            {
                temp.parent = new Puzzle(current);
                openSet.insert(temp);
            }
            closedSet.insert(current);
        }
    }
    return puzzle; // search failed
}

Puzzle pushUp(Puzzle puzzle)
{
    puzzle.up();
    return puzzle;
}

Puzzle pushDown(Puzzle puzzle)
{
    puzzle.down();
    return puzzle;
}

Puzzle pushLeft(Puzzle puzzle)
{
    puzzle.left();
    return puzzle;
}

Puzzle pushRight(Puzzle puzzle)
{
    puzzle.right();
    return puzzle;
}

std::vector<std::vector<int>> readSamples(std::vector<int> &gSVector)
{
    std::ifstream sample;
    std::string line;
    sample.open("8puzzle-testsample.txt");
    std::vector<std::vector<int>> allSamplesVector;
    std::vector<int> sampleVector;
    if (sample.is_open())
    {
        while (getline(sample, line))
        {
            if (line != "")
            {
                if (sampleVector.size() != 9)
                {
                    sampleVector.push_back(atoi(&line[0]));
                    sampleVector.push_back(atoi(&line[2]));
                    sampleVector.push_back(atoi(&line[4]));
                }
                else
                {
                    allSamplesVector.push_back(sampleVector);
                    sampleVector.clear();
                    gSVector.push_back(atoi(&line[0]));
                }
            }
        }
    }
    sample.close();
    return allSamplesVector;
}
