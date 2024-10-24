/*
Name: Erick Hambardzumyan
Date: 10-20-2024
Class: CS 4080
Assignment: Homework 2 Question 3
*/

#include <iostream>
#include <vector>
using namespace std;

void solveSudoku(vector<vector<char>>& board);
bool solvePuzzle(vector<vector<char>>& board);
bool isValid(vector<vector<char>>& board, int row, int col, char num);

void solveSudoku(vector<vector<char>>& board) { //Function that is used to solve a given sudoku puzzle board
    solvePuzzle(board);
}

bool solvePuzzle(vector<vector<char>>& board) {     //Function that is used to solve the sudoku puzzle and fill in the empty cells of the incomplete board
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') { // Empty cell found
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;  // Place number
                        if (solvePuzzle(board)) {  // Recur for next empty cell
                            return true;
                        }
                        board[row][col] = '.';  // Backtrack
                    }
                }
                return false;  // If no number is valid, return false
            }
        }
    }
    return true;  // If no empty cell is found, puzzle is solved
}

bool isValid(vector<vector<char>>& board, int row, int col, char num) {     //Function that is used to check if it is possible to place a number in a specific location of the sudoku puzzle board
    // Check if 'num' is not already placed in the current row, column, and 3x3 subgrid
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;  // Check row
        if (board[i][col] == num) return false;  // Check column
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) return false;  // Check 3x3 subgrid
    }
    return true;
}

void printSudoku(const vector<vector<char>>& board) {       //Function that displays the sudoku board with grids
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0) {
            // Print horizontal grid line every 3 rows
            cout << "-----------------------\n";
        }
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0) {
                // Print vertical grid line every 3 columns
                cout << " | ";
            }
            cout << board[row][col];
            if (col != 8) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    solveSudoku(board);

    cout << "Solved Sudoku Board:\n\n";
    printSudoku(board);

    return 0;
}


