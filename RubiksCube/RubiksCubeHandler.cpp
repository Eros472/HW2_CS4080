/*
Name: Erick Hambardzumyan
Date: 23 October 2024
Class: CS 4080
Assignment: Homework 2 Question 4
RubiksCube Client File
*/


#include "RubiksCube.h"
#include <iostream>
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // for time()
#include <set>
#include <map>       // For using maps
#include <algorithm> // For the transform function
using namespace std;

int main() {
    int cubeSize, choice, faceIndex, rowIndex, colIndex;
    char faceInput;
    string faceDirection;
    char rowDirection, columnDirection;

    // Define a set of valid face inputs
    set<char> validFaces = { 'F', 'f', 'L', 'l', 'R', 'r', 'B', 'b', 'T', 't', 'M', 'm' };
    set<string> validFaceDirections = { "CW", "CCW" }; // Valid directions for face rotation

    // Map face abbreviations to their full English names
    map<char, string> faceNames = {
        {'F', "Front"},
        {'L', "Left"},
        {'R', "Right"},
        {'B', "Back"},
        {'T', "Top"},
        {'M', "Bottom"}
    };

    // Ask for cube size with validation

    cout << "Enter the size of the Rubik's Cube (e.g., 3 for a 3x3): ";
    cin >> cubeSize;

    cout << endl;

    while (cubeSize < 1) {
            cout << "Invalid cube size. Please enter a cube size greater or equal to 1: ";
            cin >> cubeSize;
            cout << endl;
    }

    // Create a Rubik's Cube object of the given size
    RubiksCube cube(cubeSize);

    cout << "The Rubik's Cube has been scrambled.\n";

    do {
        // Display the menu options
        cout << "\nMENU:\n";
        cout << "1. ROTATE FACE (CLOCKWISE OR COUNTERCLOCKWISE)\n";
        cout << "2. ROTATE ROW\n";
        cout << "3. ROTATE COLUMN\n";
        cout << "4. DISPLAY CUBE\n";
        cout << "5. EXIT\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cout << endl;
        cout << endl;

        if (choice == 1) {
            // Rotate a face
            cout << "Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
            cin >> faceInput;
            cout << endl;

            // Validate the face input using the set
            while (validFaces.find(faceInput) == validFaces.end()) {
                cout << "Invalid face input. Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
                cin >> faceInput;
                cout << endl;
            }

            // Convert faceInput to uppercase for consistency
            faceInput = toupper(faceInput);

            // Get the face index from the user's input
            faceIndex = cube.getFaceIndex(faceInput);

            // Ask for face rotation direction
            cout << "Enter direction to rotate face (CW = Clockwise, CCW = Counterclockwise): ";
            cin >> faceDirection;
            cout << endl;

            // Normalize the direction input to uppercase
            transform(faceDirection.begin(), faceDirection.end(), faceDirection.begin(), ::toupper);

            // Validate the direction input
            while (validFaceDirections.find(faceDirection) == validFaceDirections.end()) {
                cout << "Invalid face direction for rotating. Enter 'CW' for clockwise or 'CCW' for counterclockwise: ";
                cin >> faceDirection;
                cout << endl;

                // Normalize to uppercase again after re-input
                transform(faceDirection.begin(), faceDirection.end(), faceDirection.begin(), ::toupper);
            }

            // Rotate the chosen face
            cube.rotateFace(faceIndex, faceDirection);
            cout << "Rotated " << faceNames[faceInput] << " face " << (faceDirection == "CW" ? "Clockwise" : "Counterclockwise") << ".\n";

        }
        else if (choice == 2) {
            // Rotate a row
            cout << "Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
            cin >> faceInput;
            cout << endl;

            // Validate the face input using the set
            while (validFaces.find(faceInput) == validFaces.end()) {
                cout << "Invalid face input. Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
                cin >> faceInput;
                cout << endl;
            }

            // Convert faceInput to uppercase
            faceInput = toupper(faceInput);

            // Get the face index from the user's input
            faceIndex = cube.getFaceIndex(faceInput);

            // Ask for row index with validation
            cout << "Enter row index (0-" << cube.getSize() - 1 << "): ";
            cin >> rowIndex;
            cout << endl;

            while (rowIndex < 0 || rowIndex >= cube.getSize()) {
                cout << "Invalid row index. Enter a value between 0 and " << cube.getSize() - 1 << ": ";
                cin >> rowIndex;
                cout << endl;
            }

            // Ask for row direction
            cout << "Enter direction ('L' for left, 'R' for right): ";
            cin >> rowDirection;
            cout << endl;

            while (rowDirection != 'l' && rowDirection != 'L' && rowDirection != 'r' && rowDirection != 'R') {
                cout << "Invalid row direction. Enter 'L' for left or 'R' for right: ";
                cin >> rowDirection;
                cout << endl;
            }


            // Normalize direction to lowercase
            rowDirection = toupper(rowDirection);

            // Rotate the chosen row
            cube.rotateRow(rowIndex, rowDirection);
            cout << "Rotated row " << rowIndex << " on " << faceNames[faceInput] << " face to the " << (rowDirection == 'L' ? "left" : "right") << ".\n\n";
        }
        else if (choice == 3) {
            // Rotate a column
            cout << "Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
            cin >> faceInput;
            cout << endl;

            // Validate the face input using the set
            while (validFaces.find(faceInput) == validFaces.end()) {
                cout << "Invalid face input. Enter face (F = Front, L = Left, R = Right, B = Back, T = Top, M = Bottom): ";
                cin >> faceInput;
                cout << endl;
            }

            // Convert faceInput to uppercase
            faceInput = toupper(faceInput);

            // Get the face index from the user's input
            faceIndex = cube.getFaceIndex(faceInput);

            // Ask for column index with validation
            cout << "Enter column index (0-" << cube.getSize() - 1 << "): ";
            cin >> colIndex;
            while (colIndex < 0 || colIndex >= cube.getSize()) {
                cout << "Invalid column index. Enter a value between 0 and " << cube.getSize() - 1 << ": ";
                cin >> colIndex;
                cout << endl;
            }

            // Ask for column direction
            cout << "Enter direction ('U' or 'u' for up, 'D' or 'd' for down): ";
            cin >> columnDirection;
            cout << endl;

            // Validate the column direction input
            while (columnDirection != 'd' && columnDirection != 'D' && columnDirection != 'u' && columnDirection != 'U') {
                cout << "Invalid column direction. Enter 'D' for down or 'U' for up: ";
                cin >> columnDirection;
                cout << endl;
            }

            // Normalize direction to uppercase
            columnDirection = toupper(columnDirection);

            // Rotate the chosen column
            cube.rotateColumn(colIndex, columnDirection);
            cout << "Rotated column " << colIndex << " on " << faceNames[faceInput] << " face " << (columnDirection == 'U' ? "up" : "down") << ".\n";
            cout << endl;
        }
        else if (choice == 4) {
            // Display the current state of the cube
            cube.display();
            cout << endl;
        }
        else if (choice == 5) {
            // Exit the program
            cout << "Exiting the program.\n";
        }
        else {
            cout << "\nInvalid choice. Please enter a number between 1 and 5.\n\n ";
        }
    } while (choice != 5);

    return 0;
}

