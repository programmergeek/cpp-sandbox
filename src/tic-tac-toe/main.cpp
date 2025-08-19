#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>

using namespace std;
// This is a simple tik tak toe project that works in the terminal.

// Project features:
// 1. Creates the playing board
// 2. Get player input
// 3. Update playing board with player's move
// 4. Detect when the player has lost, won, or draw
// 5. The program should act as player 2 and make its own moves

string rowToString(int inputRow[], int size){
    string row = "";
    for(int r = 0; r < size; r++){
	switch (inputRow[r]) {
	    case 0:
		row += " [ ] ";
	    break;
	    case 1:
		row += " [X] ";
	    break;
	    case 2:
		row += " [O] ";
	    break;
	}
    }
    return row;
}

void drawGrid(int grid[][3]){
    // The playing grid is 3x3 grid represented using an array
    for(int row = 0; row < 3; row++){
	cout << rowToString(grid[row], 3) + "\n";
    }

}

int gameResult(){
    return 0;
}

void systemMove(vector<int>& move){
    bool seeded = false;
    if(!seeded){
	srand(time(0));
	seeded = true;
    }
    int row = rand() % 3;
    int column = rand() % 3;
    move[0] = row;
    move[1] = column;
}

void playerMove(vector<int>& move){
    int row, column;
    std::cout << "Enter row (1 - 3)\n";
    std::cin >> row;
    std::cout << "Enter column (1 - 3)\n";
    std::cin >> column;

    move[0] = row -1;
    move[1] = column -1;
}

bool checkMoveIsValid(vector<int> move, vector<vector<int>>& moves){
    // moves are valid if and only if:
    // 1. square selected has not already played
    // 2. square selected is within the grid

    bool isValid = true;

    // check if move has been played
    for(vector<int> m : moves){
	if(m[0] == move[0] && m[1] == move[1]){
	    isValid = false;
	}
    }

    // check selected square is within the grid
    if((move[0] < 0)  || (move[1] > 3)){
	isValid = false;
    }

    return isValid;
}

string vectorToString(vector<vector<int>>& moves){
    string out = "";
    for(vector<int> move: moves){
	out += "{"+ to_string(move[0]) +", " + to_string(move[1]) + "} ";
    }

    return out;
}

void updateGame(vector<int> move, vector<vector<int>>& moves, int grid[][3], int player){
    // This function is responsible for state management within the game
    
    // adds new move to move history
    moves.push_back(move);

    // update game grid
    grid[move[0]][move[1]] = player;
    cout << "\nmove history: " + vectorToString(moves) << endl;
}

int main(){
    int grid[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    vector<vector<int>> moves;
    vector<int> pMove = {0,0};
    vector<int> sMove = {0,0};

    int count = 0;

    while(count < 5){
	drawGrid(grid);
	playerMove(pMove);

	while(!checkMoveIsValid(pMove, moves)){
	    playerMove(pMove);
	}

	updateGame(pMove,moves, grid, 1);
	systemMove(sMove);

	while (!checkMoveIsValid(sMove, moves)) {
	    systemMove(sMove);
	}
	
	updateGame(sMove,moves, grid, 2);
	count++;
    }

    return 0;
}
