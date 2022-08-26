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

bool operator<(const Puzzle& lhs, const Puzzle& rhs) {
    return !(lhs.fscore < rhs.fscore);
}


std::vector<std::vector<int>> readSamples(std::vector<int> &gSVector);
Puzzle aStar(Puzzle puzzle, int numIteration);
void printPath(Puzzle *puzzle);
Puzzle pushUp(Puzzle puzzle);
Puzzle pushDown(Puzzle puzzle);
Puzzle pushLeft(Puzzle puzzle);
Puzzle pushRight(Puzzle puzzle);

int main() {
    std::vector<int> gSVector;
    std::vector<std::vector<int>> allSamplesVector = readSamples(gSVector);

    for(int i = 1; i < allSamplesVector.size(); i++) {
    Puzzle puzzle(allSamplesVector[i], allSamplesVector[0]);
    Puzzle solved = aStar(puzzle, gSVector[i]);
    //printPath(&solved);
    }
}

void printPath(Puzzle *puzzle) {
    if(puzzle->parent == NULL) {
        return;
    }
    else {
        printPath(puzzle->parent);
        puzzle->printBoard();

    }
        
}

Puzzle aStar(Puzzle puzzle, int numIteration) {
    std::set<Puzzle> closedSet;
    std::priority_queue<Puzzle> openSet;
    // Update to unordered map?
    std::set<Puzzle> openSetSet;
    Puzzle current(puzzle); 
    openSet.push(puzzle);
    while(openSet.size() > 0) {
        current = openSet.top();

        if(current.checkWin()) {
            std::cout << "Solution found in : " << current.depth << "\nExpected: " << numIteration << std::endl;
            puzzle = current;
            break;
        }

    openSet.pop();
    if(closedSet.find(current) == closedSet.end())
        closedSet.insert(current);

    Puzzle temp(current);
    std::set<Puzzle>::iterator openIt;
    temp = pushUp(current);
    openIt = openSetSet.find(temp);
    if(closedSet.find(temp) == closedSet.end()) {
        if(openIt == openSetSet.end() || temp.heuristic < openIt->heuristic) {
            temp.parent = new Puzzle(current);
            openSet.push(temp);
            openSetSet.insert(temp);
        }
    }
    temp = pushDown(current);
    openIt = openSetSet.find(temp);
    if(closedSet.find(temp) == closedSet.end()) {
        if(openIt == openSetSet.end() || temp.heuristic < openIt->heuristic) {
            temp.parent = new Puzzle(current);
            openSet.push(temp);
            openSetSet.insert(temp);
        }
    }
    temp = pushLeft(current);
    openIt = openSetSet.find(temp);
    if(closedSet.find(temp) == closedSet.end()) {
        if(openIt == openSetSet.end() || temp.heuristic < openIt->heuristic) {
            temp.parent = new Puzzle(current);
            openSet.push(temp);
            openSetSet.insert(temp);
        }
    }
    temp = pushRight(current);
    openIt = openSetSet.find(temp);
    if(closedSet.find(temp) == closedSet.end()) {
        if(openIt == openSetSet.end() || temp.heuristic < openIt->heuristic) {
            temp.parent = new Puzzle(current);
            openSet.push(temp);
            openSetSet.insert(temp);
        }
    }
    }
    return puzzle; // cannot be reached
}

Puzzle pushUp(Puzzle puzzle) {
    puzzle.up();
    return puzzle;
}

Puzzle pushDown(Puzzle puzzle) {
    puzzle.down();
    return puzzle;
}

Puzzle pushLeft(Puzzle puzzle) {
    puzzle.left();
    return puzzle;
}

Puzzle pushRight(Puzzle puzzle) {
    puzzle.right();
    return puzzle;
}

std::vector<std::vector<int>> readSamples(std::vector<int> &gSVector) {
    std::ifstream sample;
    std::string line;
    sample.open("8puzzle-testsample.txt");
    std::vector<std::vector<int>> allSamplesVector;
    std::vector<int> sampleVector;
    if(sample.is_open()) {
        while(getline(sample, line)) {
            if(line != "") {
                if(sampleVector.size() != 9) {
                    sampleVector.push_back(atoi(&line[0]));
                    sampleVector.push_back(atoi(&line[2]));
                    sampleVector.push_back(atoi(&line[4]));
                }
                else {
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
