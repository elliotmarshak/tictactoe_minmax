#include <iostream>
#include <cmath>
#include <vector>

void printBoard(int board[3][3]) {
    for (int row = 0; row < 3; row++) {
        std::string output = "|";
        for (int col = 0; col < 3; col++) {
            std::string slot = ".";
            if (board[row][col] == 1) {slot = "X";}
            else if (board[row][col] == 2) {slot = "O";}
            output += slot + "|";
        }
        std::cout << output << "\n";

    }
}

bool drawCheck(int board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == 0) {return false;}
        }
    }

    return true;
}

bool winCheck(int board[3][3], int player) {
    //horizontal
    if (board[0][0] == player && board[0][1] == player && board[0][2] == player) {
        return true;
    }
    if (board[1][0] == player && board[1][1] == player && board[1][2] == player) {
        return true;
    }
    if (board[2][0] == player && board[2][1] == player && board[2][2] == player) {
        return true;
    }

    //vertical
    if (board[0][0] == player && board[1][0] == player && board[2][0] == player) {
        return true;
    }
    if (board[0][1] == player && board[1][1] == player && board[2][1] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][2] == player && board[2][2] == player) {
        return true;
    }

    //diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player) {
        return true;
    }

    return false;
}

std::pair<int, int> minmax(int board[3][3], bool maximisingPlayer) {
    if (winCheck(board, 1)) {
        return {1, -1};
    }
    if (winCheck(board, 2)) {
        return {-1, -1};
    }
    if (drawCheck(board)) {
        return {0, -1};
    }

    int bestSlot;
    int bestScore;

    if (maximisingPlayer) {
        bestScore = -9999;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == 0) {
                    int newBoard[3][3]; 
                    for (int r = 0; r < 3; r++) {
                        for (int c = 0; c < 3; c++) {
                            newBoard[r][c] = board[r][c];
                        }
                    }

                    newBoard[row][col] = 1; //because we are the maximising player
                    std::pair<int, int> response = minmax(newBoard, false);
                    int score = response.first;
                    int slot = row * 3 + col;

                    if (score > bestScore) {
                        bestScore = score;
                        bestSlot = slot;
                    }
                }
            }
        }

    }
    else {
        bestScore = 9999;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == 0) {
                    int newBoard[3][3]; 
                    for (int r = 0; r < 3; r++) {
                        for (int c = 0; c < 3; c++) {
                            newBoard[r][c] = board[r][c];
                        }
                    }

                    newBoard[row][col] = 2; //because we are the minimising player
                    std::pair<int, int> response = minmax(newBoard, true);
                    int score = response.first;
                    int slot = row * 3 + col;

                    if (score < bestScore) {
                        bestScore = score;
                        bestSlot = slot;
                    }
                }
            }
        }


    }

    return {bestScore, bestSlot};
}

int main() {

    int board[3][3] = {};
    bool game_over = false;
    int winner;
    int current_player = 1;

    while (!game_over) {
        if (current_player == 1) {
            printBoard(board);
        }
        if (current_player == 1) {
            int slot;
            std::cout << "Enter the slot number (1-9): ";
            std::cin >> slot;
            int row = floor((slot-1)/3);
            int col = (slot-1) % 3;

            board[row][col] = current_player;
        }
        else { //current_player is 2
            std::pair<int, int> response = minmax(board, false);
            int score = response.first;
            int slot = response.second;
            std::cout << "Computer move: " << slot+1 << "\n";
            int row = floor((slot)/3);
            int col = (slot) % 3;
            board[row][col] = current_player;

        }
        if (winCheck(board, 1)) {
            game_over = true;
            winner = 1;
        }
        else if (winCheck(board, 2)) {
            game_over = true;
            winner = 2;
        }
        else if (drawCheck(board)) {
            game_over = true;
        }
        current_player = 3 - current_player;

    }

    printBoard(board);

    if (winner==1) {std::cout << "Player 1 wins!";}
    else if (winner==2) {std::cout << "Player 2 wins!";}
    else {std::cout << "The game is a draw!";}

    return 0;
}