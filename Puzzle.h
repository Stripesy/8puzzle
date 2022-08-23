class Puzzle {
    public:
    std::vector<int> boardLayout;
    std::vector<int> goalLayout;
    int rows = 3, cols = 3;
    int playerRow, playerCol, playerPos;
    int depth = 0;
    int fscore;
public:
    int heuristic;
    Puzzle(std::vector<int> sample, std::vector<int> target) {
        boardLayout = sample;
        goalLayout = target;
        heuristic = manDistance();
        fscore = 0;

        for(int i = 0; i < boardLayout.size(); i++) {
            if(boardLayout[i] == 0) {
                playerRow = i/3;
                playerCol = i%3;
                playerPos = i;
            } // Divide by rows to get row, modulo by cols to get col
        }
    }
    Puzzle(const Puzzle& puzzle) {
        boardLayout = puzzle.boardLayout;
        goalLayout = puzzle.goalLayout;
        heuristic = manDistance();
        depth = puzzle.depth;
        fscore = heuristic + depth;

        for(int i = 0; i < boardLayout.size(); i++) {
            if(boardLayout[i] == 0) {
                playerRow = i/3;
                playerCol = i%3;
                playerPos = i;
            } // Divide by rows to get row, modulo by cols to get col
        }
    }
    void printBoard();
    void right();
    void left();
    void up();
    void down();
    bool checkWin();
    int manDistance();
private:
};

void Puzzle::printBoard() {
    for(int i = 0; i < boardLayout.size(); i+=3) {
        std::cout << "   |   |   \n";
        std::cout << " " << boardLayout[i] << " | " << boardLayout[i+1] << " | " 
        << boardLayout[i+2] << "\n";
        if(i != boardLayout.size() - 3)
            std::cout << "___|___|___\n";
        else std::cout << "   |   |   \n\n";
    }
}

int Puzzle::manDistance() {
    int distance = 0;
    int x_val, y_val;
    int x_goal, y_goal;
    // Divide by rows to get row, modulo by cols to get col
    for(int i = 0; i < boardLayout.size(); i++) {
        if(boardLayout[i] == 0) continue;
        x_val = i%cols;
        y_val = i/rows;
        for(int j = 0; j < goalLayout.size(); j++) {
            if(boardLayout[i] == goalLayout[j]) {
                x_goal = j%cols;
                y_goal = j/rows;
                break;
            }
        }
        distance += (abs(x_val - x_goal) + abs(y_val - y_goal));
    }
    return distance;
}

bool Puzzle::checkWin() {
    return boardLayout == goalLayout;
}

void Puzzle::up() {
    if(playerRow != 0) {
        boardLayout[playerPos] = boardLayout[playerPos-rows];
        boardLayout[playerPos-rows] = 0;
        playerPos = playerPos - rows;
        depth+=1;
    }
    heuristic = manDistance();
}

void Puzzle::down() {
    if(playerRow != rows-1) {
        boardLayout[playerPos] = boardLayout[playerPos+rows];
        boardLayout[playerPos+rows] = 0;
        playerPos = playerPos + rows;
        depth+=1;
    }
    heuristic = manDistance();
}

void Puzzle::left() {
    if(playerCol != 0) {
        boardLayout[playerPos] = boardLayout[playerPos-1];
        boardLayout[playerPos-1] = 0;
        playerPos = playerPos - 1;
        depth+=1;
    }
    heuristic = manDistance();
}

void Puzzle::right() {
    if(playerRow != cols-1) {
        boardLayout[playerPos] = boardLayout[playerPos+1];
        boardLayout[playerPos+1] = 0;
        playerPos = playerPos + 1;
        depth+=1;
    }
    heuristic = manDistance();

}