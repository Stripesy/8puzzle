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
    if(lhs.fscore != rhs.fscore)
        return !(lhs.fscore < rhs.fscore);
    else return !(lhs.depth < rhs.depth);
}


std::vector<std::vector<int>> readSamples(std::vector<int> &gSVector);
void aStar(Puzzle puzzle);
Puzzle pushUp(Puzzle puzzle);
Puzzle pushDown(Puzzle puzzle);
Puzzle pushLeft(Puzzle puzzle);
Puzzle pushRight(Puzzle puzzle);

void aStar();

int main() {
    std::vector<int> gSVector;
    std::vector<std::vector<int>> allSamplesVector = readSamples(gSVector);

    for(int i = 1; i < allSamplesVector.size(); i++) {
    Puzzle puzzle(allSamplesVector[i], allSamplesVector[0]);
    aStar(puzzle);
    }
}

void aStar(Puzzle puzzle) {
    std::set<Puzzle, cmp> closedSet;
    std::priority_queue<Puzzle> openSet;
    // Update to unordered map?
    std::set<Puzzle, cmp> openSetSet;
    Puzzle current(puzzle);
    openSet.push(puzzle);
    while(openSet.size() > 0) {
        current = openSet.top();

        if(current.checkWin()) {
            std::cout << "Solution found in : " << current.depth << std::endl;
            break;
        }

    openSet.pop();
    if(closedSet.find(current) == closedSet.end())
        closedSet.insert(current);

    if(closedSet.find(pushUp(current)) == closedSet.end()) {
        if(openSetSet.find(pushUp(current)) == openSetSet.end()) {
            openSet.push(pushUp(current));
            openSetSet.insert(pushUp(current));
        }
    }
    if(closedSet.find(pushDown(current)) == closedSet.end()) {
        if(openSetSet.find(pushDown(current)) == openSetSet.end()) {
            openSet.push(pushDown(current));
            openSetSet.insert(pushDown(current));
        }
    }
    if(closedSet.find(pushLeft(current)) == closedSet.end()) {
        if(openSetSet.find(pushLeft(current)) == openSetSet.end()) {
            openSet.push(pushLeft(current));
            openSetSet.insert(pushLeft(current));
        }
    }
    if(closedSet.find(pushRight(current)) == closedSet.end()) {
        if(openSetSet.find(pushRight(current)) == openSetSet.end()) {
            openSet.push(pushRight(current));
            openSetSet.insert(pushRight(current));
        }
    }
    }
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
