/*
Name: Erick Hambardzumyan
Date: 23 October 2024
Class: CS 4080
Assignment: Homework 2 Question 4
RubiksCube Implementation File
*/


#include "RubiksCube.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>  // For random number generation
using namespace std;

// Constructor that dynamically allocates the 3D array using unique_ptr
RubiksCube::RubiksCube(int size) : size(size), cubeArr(make_unique<unique_ptr<unique_ptr<char[]>[]>[]>(6)) {
    // Allocate the 3D array dynamically
    for (int face = 0; face < 6; ++face) {
        cubeArr[face] = make_unique<unique_ptr<char[]>[]>(size);
        for (int row = 0; row < size; ++row) {
            cubeArr[face][row] = make_unique<char[]>(size);
        }
    }

    // Initialize and randomize the cube with shuffled colors
    randomizeCube();
}

// Constructor that takes a predefined 3D array for testing
RubiksCube::RubiksCube(const vector<vector<vector<char>>>& predefinedCube) {
    size = predefinedCube[0].size();  // Assuming a square face (e.g., 3x3)

    // Allocate memory for the cube
    cubeArr = make_unique<unique_ptr<unique_ptr<char[]>[]>[]>(6);
    for (int face = 0; face < 6; ++face) {
        cubeArr[face] = make_unique<unique_ptr<char[]>[]>(size);
        for (int row = 0; row < size; ++row) {
            cubeArr[face][row] = make_unique<char[]>(size);
        }
    }

    // Set the cube to the predefined state
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                cubeArr[face][row][col] = predefinedCube[face][row][col];
            }
        }
    }
}

// Helper function to randomize the cube
void RubiksCube::randomizeCube() {
    // Create a vector to hold all the cube's tiles
    vector<char> tiles;

    // Fill the tiles with the correct number of each color
    for (int face = 0; face < 6; ++face) {
        for (int i = 0; i < size * size; ++i) {
            tiles.push_back(colors[face]);  // Add the appropriate number of tiles per color
        }
    }

    // Shuffle the tiles to create a random arrangement
    random_device rd;
    mt19937 g(rd());
    shuffle(tiles.begin(), tiles.end(), g);

    // Assign shuffled tiles back to the cube faces
    int tileIndex = 0;
    for (int face = 0; face < 6; ++face) {
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                cubeArr[face][row][col] = tiles[tileIndex++];
            }
        }
    }
}

int RubiksCube::getFaceIndex(char faceInput) {
    switch (faceInput) {
    case 'F': return 0;  // Front Face
    case 'L': return 1;  // Left Face
    case 'R': return 2;  // Right Face
    case 'B': return 3;  // Back Face
    case 'T': return 4;  // Top Face
    case 'M': return 5;  // Bottom Face
    //default: return -1;  // Invalid input
    }
}

// Getter function to return the size of the cube
int RubiksCube::getSize() const {
    return size;
}

void RubiksCube::rotateFace(int faceIndex, string f_direction) {
    // Rotate the face itself
    unique_ptr<unique_ptr<char[]>[]> temp = make_unique<unique_ptr<char[]>[]>(size);
    for (int i = 0; i < size; ++i) {
        temp[i] = make_unique<char[]>(size);
    }

    if (f_direction == "CW") {
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                temp[col][size - 1 - row] = cubeArr[faceIndex][row][col];
            }
        }
    }
    else if (f_direction == "CCW") {
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                temp[size - 1 - col][row] = cubeArr[faceIndex][row][col];
            }
        }
    }

    // Copy the rotated face back
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            cubeArr[faceIndex][row][col] = temp[row][col];
        }
    }

    // Handle the adjacent faces if rotating the front face (faceIndex == 0)
    if (faceIndex == 0) {
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store Top face's bottom row temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[4][2][col];  // Top face's bottom row
            }

            // 2. Move Left face's right column -> Top face's bottom row
            for (int row = 0; row < size; ++row) {
                cubeArr[4][2][row] = cubeArr[1][size - 1 - row][2];  // Left face's right column -> Top face's bottom row
            }

            // 3. Move Bottom face's top row -> Left face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[1][row][2] = cubeArr[5][0][row];  // Bottom face's top row -> Left face's right column
            }

            // 4. Move Right face's left column -> Bottom face's top row
            for (int row = 0; row < size; ++row) {
                cubeArr[5][0][row] = cubeArr[2][size - 1 - row][0];  // Right face's left column -> Bottom face's top row
            }

            // 5. Move tempRow (Top face's original bottom row) -> Right face's left column 
            for (int row = 0; row < size; ++row) {
                cubeArr[2][row][0] = tempRow[row];  // Top face's bottom row -> Right face's left column 
            }
        }
        else if (f_direction == "CCW") {
            // 1. Store Top face's bottom row temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[4][2][col];  // Top face's bottom row
            }

            // 2. Move Right face's left column -> Top face's bottom row
            for (int row = 0; row < size; ++row) {
                cubeArr[4][2][row] = cubeArr[2][row][0];  // Right face's left column -> Top face's bottom row
            }

            // 3. Move Bottom face's top row -> Right face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[2][row][0] = cubeArr[5][0][size - 1 - row];  // Bottom face's top row -> Right face's left column
            }

            // 4. Move Left face's right column -> Bottom face's top row
            for (int row = 0; row < size; ++row) {
                cubeArr[5][0][row] = cubeArr[1][row][2];  // Left face's right column -> Bottom face's top row
            }

            // 5. Move tempRow (Top face's original bottom row) -> Left face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[1][size - 1 - row][2] = tempRow[row];  // Top face's bottom row -> Left face's right column
            }
        }
    }

    else if (faceIndex == 1) {  // Left face rotation
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store Top face's left column temporarily
            for (int row = 0; row < size; ++row) {
                tempRow[row] = cubeArr[4][row][0];  // Top face's left column
            }

            // 2. Move Back face's right column -> Top face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[4][row][0] = cubeArr[3][size - 1 - row][2];  // Back face's right column -> Top face's left column
            }

            // 3. Move Bottom face's left column -> Back face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[3][size - 1 - row][2] = cubeArr[5][row][0];  // Bottom face's left column -> Back face's right column
            }

            // 4. Move Front face's left column -> Bottom face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[5][row][0] = cubeArr[0][row][0];  // Front face's left column -> Bottom face's left column
            }

            // 5. Move tempRow (Top face's original left column) -> Front face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[0][row][0] = tempRow[row];  // Top face's left column -> Front face's left column
            }
        }
        else if (f_direction == "CCW") {
            // 1. Store Top face's left column temporarily
            for (int row = 0; row < size; ++row) {
                tempRow[row] = cubeArr[4][row][0];  // Top face's left column
            }

            // 2. Move Front face's left column -> Top face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[4][row][0] = cubeArr[0][row][0];  // Front face's left column -> Top face's left column
            }

            // 3. Move Bottom face's left column -> Front face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[0][row][0] = cubeArr[5][row][0];  // Bottom face's left column -> Front face's left column
            }

            // 4. Move Back face's right column -> Bottom face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[5][row][0] = cubeArr[3][size - 1 - row][2];  // Back face's right column -> Bottom face's left column
            }

            // 5. Move tempRow (Top face's original left column) -> Back face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[3][size - 1 - row][2] = tempRow[row];  // Top face's left column -> Back face's right column
            }
        }
    }

    else if (faceIndex == 2) {  // Right face rotation
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store Top face's right column temporarily
            for (int row = 0; row < size; ++row) {
                tempRow[row] = cubeArr[4][row][2];  // Top face's right column
            }

            // 2. Move Front face's right column -> Top face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[4][row][2] = cubeArr[0][row][2];  // Front face's right column -> Top face's right column
            }

            // 3. Move Bottom face's right column -> Front face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[0][row][2] = cubeArr[5][row][2];  // Bottom face's right column -> Front face's right column
            }

            // 4. Move Back face's left column -> Bottom face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[5][row][2] = cubeArr[3][size - 1 - row][0];  // Back face's left column -> Bottom face's right column
            }

            // 5. Move tempRow (Top face's original right column) -> Back face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[3][size - 1 - row][0] = tempRow[row];  // Top face's right column -> Back face's left column
            }
        }
        else if (f_direction == "CCW") {
            // 1. Store Top face's right column temporarily
            for (int row = 0; row < size; ++row) {
                tempRow[row] = cubeArr[4][row][2];  // Top face's right column
            }

            // 2. Move Back face's left column -> Top face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[4][row][2] = cubeArr[3][size - 1 - row][0];  // Back face's left column -> Top face's right column
            }

            // 3. Move Bottom face's right column -> Back face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[3][size - 1 - row][0] = cubeArr[5][row][2];  // Bottom face's right column -> Back face's left column
            }

            // 4. Move Front face's right column -> Bottom face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[5][row][2] = cubeArr[0][row][2];  // Front face's right column -> Bottom face's right column
            }

            // 5. Move tempRow (Top face's original right column) -> Front face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[0][row][2] = tempRow[row];  // Top face's right column -> Front face's right column
            }
        }
    }

    else if (faceIndex == 3) {  // Back face rotation
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store Top face's top row temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[4][0][col];  // Top face's top row
            }

            // 2. Move Right face's right column -> Top face's top row
            for (int row = 0; row < size; ++row) {
                cubeArr[4][0][row] = cubeArr[2][row][2];  // Right face's right column -> Top face's top row
            }

            // 3. Move Bottom face's bottom row -> Right face's right column
            for (int col = 0; col < size; ++col) {
                cubeArr[2][col][2] = cubeArr[5][2][size - 1 - col];  // Bottom face's bottom row -> Right face's right column
            }

            // 4. Move Left face's left column -> Bottom face's bottom row
            for (int row = 0; row < size; ++row) {
                cubeArr[5][2][row] = cubeArr[1][row][0];  // Left face's left column -> Bottom face's bottom row
            }

            // 5. Move tempRow (Top face's original top row) -> Left face's left column
            for (int row = 0; row < size; ++row) {
                cubeArr[1][size - 1 - row][0] = tempRow[row];  // Top face's top row -> Left face's left column
            }
        }

        else if (f_direction == "CCW") {
            // 1. Store Top face's top row temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[4][0][col];  // Top face's top row
            }

            // 2. Move Left face's left column -> Top face's top row
            for (int row = 0; row < size; ++row) {
                cubeArr[4][0][row] = cubeArr[1][size - 1 - row][0];  // Left face's left column -> Top face's top row
            }

            // 3. Move Bottom face's bottom row -> Left face's left column
            for (int col = 0; col < size; ++col) {
                cubeArr[1][col][0] = cubeArr[5][2][col];  // Bottom face's bottom row -> Left face's left column
            }

            // 4. Move Right face's right column -> Bottom face's bottom row
            for (int row = 0; row < size; ++row) {
                cubeArr[5][2][size - 1 - row] = cubeArr[2][row][2];  // Right face's right column -> Bottom face's bottom row
            }

            // 5. Move tempRow (Top face's original top row) -> Right face's right column
            for (int row = 0; row < size; ++row) {
                cubeArr[2][row][2] = tempRow[row];  // Top face's top row -> Right face's right column
            }
        }
    }



    else if (faceIndex == 4) {  // Top face rotation
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store the top row of the Front face temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[0][0][col];  // Front face's top row
            }

            // 2. Move the Right face's top row -> Front face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[0][0][col] = cubeArr[2][0][col];  // Right -> Front
            }

            // 3. Move the Back face's top row (reversed) -> Right face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[2][0][col] = cubeArr[3][0][size - 1 - col];  // Back -> Right
            }

            // 4. Move the Left face's top row -> Back face's top row (reversed)
            for (int col = 0; col < size; ++col) {
                cubeArr[3][0][size - 1 - col] = cubeArr[1][0][col];  // Left -> Back
            }

            // 5. Move tempRow (Front face's original top row) -> Left face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[1][0][col] = tempRow[col];  // Front -> Left
            }
        }

        else if (f_direction == "CCW") {
            // 1. Store the top row of the Front face temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[0][0][col];  // Front face's top row
            }

            // 2. Move the Left face's top row -> Front face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[0][0][col] = cubeArr[1][0][col];  // Left -> Front
            }

            // 3. Move the Back face's top row -> Left face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[1][0][col] = cubeArr[3][0][col];  // Back -> Right
            }

            // 4. Move the Right face's top row -> Back face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[3][0][col] = cubeArr[2][0][col];  // Left -> Back
            }

            // 5. Move tempRow (Front face's original top row) -> Right face's top row
            for (int col = 0; col < size; ++col) {
                cubeArr[2][0][col] = tempRow[col];  // Right -> Left
            }
        }
    }

    else if (faceIndex == 5) {  // Bottom face rotation
        vector<char> tempRow(size);

        if (f_direction == "CW") {
            // 1. Store the bottom row of the Front face temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[0][2][col];  // Front face's bottom row
            }

            // 2. Move the Left face's bottom row -> Front face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[0][2][col] = cubeArr[1][2][col];  // Left -> Front
            }

            // 3. Move the Back face's bottom row (reversed) -> Left face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[1][2][col] = cubeArr[3][2][col];  // Back -> Left
            }

            // 4. Move the Right face's bottom row -> Back face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[3][2][col] = cubeArr[2][2][col];  // Right -> Back
            }

            // 5. Move tempRow (Front face's original bottom row) -> Right face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[2][2][col] = tempRow[col];  // Front -> Right
            }
        }

        else if (f_direction == "CCW") {
            // 1. Store the bottom row of the Front face temporarily
            for (int col = 0; col < size; ++col) {
                tempRow[col] = cubeArr[0][2][col];  // Front face's bottom row
            }

            // 2. Move the Right face's bottom row -> Front face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[0][2][col] = cubeArr[2][2][col];  // Right -> Front
            }

            // 3. Move the Back face's bottom row -> Right face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[2][2][col] = cubeArr[3][2][col];  // Back -> Right
            }

            // 4. Move the Left face's bottom row -> Back face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[3][2][col] = cubeArr[1][2][col];  // Left -> Back 
            }

            // 5. Move tempRow (Front face's original bottom row) -> Left face's bottom row
            for (int col = 0; col < size; ++col) {
                cubeArr[1][2][col] = tempRow[col];  // Front -> Left
            }
        }
    }
}







void RubiksCube::rotateRow(int rowIndex, char row_dir) {

    if (rowIndex == 0) {      //row 0 (or first row) is chosen 

        if (row_dir == 'L') {    //if chosen to rotate row 0 left

            this->rotateFace(4, "CW");    //the top face is rotated clockwise
        }

        else if (row_dir == 'R') {  //if chosen to rotate row 0 right

            this->rotateFace(4, "CCW");    //top face is rotated counterclockwise
        }

    }

    else if (rowIndex == 1) {       //row 1 (or second row) is chosen

        if (row_dir == 'L') {  //if chosen to rotate row 1 left

            this->rotateMiddleRowLayer("CW");    //middle row layer of front face is rotated Cw

        }

        else if (row_dir == 'R') {    //if chosen to rotate row 1 right

            this->rotateMiddleRowLayer("CCW"); //middle row layer of front face is rotated CCW
        }
    }

    else if (rowIndex == 2) {    //row 2 (or third row) is chosen

        if (row_dir == 'L') {  //if chosen to rotate row 2 left

            this->rotateFace(5, "CCW");    //rotate bottom face CCW

        }

        else if (row_dir == 'R') {    //if chosen to rotate row 2 right

            this->rotateFace(5, "CW");    //rotate bottom face CW
        }
    }
}


void RubiksCube::rotateMiddleRowLayer(string faceDirection) {
    // Temporary array to store the current state of the Front middle row
    vector<char> tempRow(size);

    if (faceDirection == "CW") {
        // Step 1: Store the middle row of the Front face temporarily
        for (int col = 0; col < size; ++col) {
            tempRow[col] = cubeArr[0][1][col];  // Front face's middle row
        }

        //Step 2: Move the Right Face's middle row --> Front face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[0][1][col] = cubeArr[2][1][col];    //Right -> Front
        }

        // Step 3: Move the Back face's middle row -> Right face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[2][1][col] = cubeArr[3][1][col];  // Back -> Right
        }

        // Step 4: Move the Left face's middle row -> Back face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[3][1][col] = cubeArr[1][1][col];    //Left -> Back
        }

        // Step 5: Move tempRow (Front face's original middle row) -> Left face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[1][1][col] = tempRow[col];  // Front -> Right
        }
    }

    else if (faceDirection == "CCW") {
        // Step 1: Store the middle row of the Front face temporarily
        for (int col = 0; col < size; ++col) {
            tempRow[col] = cubeArr[0][1][col];  // Front face's middle row
        }

        // Step 2: Move the Left Face's middle row --> Front face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[0][1][col] = cubeArr[1][1][col];  // Left -> Front
        }

        // Step 3: Move the Back face's middle row -> Left face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[1][1][col] = cubeArr[3][1][col];  // Back -> Left
        }

        // Step 4: Move the Right face's middle row -> Back face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[3][1][col] = cubeArr[2][1][col];  // Right -> Back
        }

        // Step 5: Move tempRow (Front face's original middle row) -> Right face's middle row
        for (int col = 0; col < size; ++col) {
            cubeArr[2][1][col] = tempRow[col];  // Front -> Right
        }
    }
}


void RubiksCube::rotateMiddleColumnLayer(string faceDirection) {
    // Temporary array to store the current state of the Top middle column
    vector<char> tempCol(size);

    if (faceDirection == "CW") {
        // Step 1: Store the middle column of the Top face temporarily
        for (int row = 0; row < size; ++row) {
            tempCol[row] = cubeArr[4][row][1];  // Top face's middle column
        }

        // Step 2: Move the Back face's middle column -> Top face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[4][row][1] = cubeArr[3][size - 1 - row][1];  // Back -> Top
        }

        // Step 3: Move the Bottom face's middle column -> Back face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[3][size - 1 - row][1] = cubeArr[5][row][1];  // Bottom -> Back
        }

        // Step 4: Move the Front face's middle column -> Bottom face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[5][row][1] = cubeArr[0][row][1];  // Front -> Bottom
        }

        // Step 5: Move tempCol (Top face's original middle column) -> Front face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[0][row][1] = tempCol[row];  // Top -> Front
        }
    }

    else if (faceDirection == "CCW") {
        // Step 1: Store the middle column of the Top face temporarily
        for (int row = 0; row < size; ++row) {
            tempCol[row] = cubeArr[4][row][1];  // Top face's middle column
        }

        // Step 2: Move the Front face's middle column -> Top face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[4][row][1] = cubeArr[0][row][1];  // Front -> Top
        }

        // Step 3: Move the Bottom face's middle column -> Front face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[0][row][1] = cubeArr[5][row][1];  // Bottom -> Front
        }

        // Step 4: Move the Back face's middle column -> Bottom face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[5][row][1] = cubeArr[3][size - 1 - row][1];  // Back -> Bottom
        }

        // Step 5: Move tempCol (Top face's original middle column) -> Back face's middle column
        for (int row = 0; row < size; ++row) {
            cubeArr[3][size - 1 - row][1] = tempCol[row];  // Top -> Back (reversed)
        }
    }

   
}



void RubiksCube::rotateColumn(int colIndex, char col_dir) {

    if (colIndex == 0) {      //col 0 (or first column) is chosen 

        if (col_dir == 'U') {    //if chosen to rotate col 0 up

            this->rotateFace(1, "CCW");    //the left face is rotated counterclockwise
        }

        else if (col_dir == 'D') {  //if chosen to rotate col 0 down

            this->rotateFace(1, "CW");    //left face is rotated clockwise
        }

    }

    else if (colIndex == 1) {       //col 1 (or second column) is chosen

        if (col_dir == 'U') {  //if chosen to rotate column 1 up

            this->rotateMiddleColumnLayer("CCW");    //middle column layer of front face is rotated CCW

        }

        else if (col_dir == 'D') {    //if chosen to rotate column 1 down

            this->rotateMiddleColumnLayer("CW"); //middle column layer of front face is rotated CW
        }
    }

    else if (colIndex == 2) {    //col 2 (or third column) is chosen

        if (col_dir == 'U') {  //if chosen to rotate column 2 up

            this->rotateFace(2, "CW");    //rotate right face CW

        }

        else if (col_dir == 'D') {    //if chosen to rotate column 2 down

            this->rotateFace(2, "CCW");    //rotate right face CCW
        }
    }
}



// Display the current state of the cube with face names and colors
void RubiksCube::display() const {
    for (int face = 0; face < 6; ++face) {
        std::cout << faceNames[face] << ":\n";  // Print the face name (e.g., Front Face)
        for (int row = 0; row < size; ++row) {
            for (int col = 0; col < size; ++col) {
                cout << cubeArr[face][row][col] << " ";  // Display cubie colors
            }
            cout << endl;
        }
        cout << endl;
    }

}