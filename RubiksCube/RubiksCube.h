/*
Name: Erick Hambardzumyan
Date: 23 October 2024
Class: CS 4080
Assignment: Homework 2 Question 4
RubiksCube Class Declaration
*/


#ifndef RUBIKSCUBE_H
#define RUBIKSCUBE_H

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class RubiksCube {
private:
    unique_ptr<unique_ptr<unique_ptr<char[]>[]>[]> cubeArr;  // Dynamic 3D array using unique_ptr
    // Define the const array for face colors
    const char colors[6] = { 'R', 'G', 'Y', 'O', 'W', 'B' };  // Red, Green, Yellow, Orange, White, Blue  // Colors for the faces (R, G, etc.)

    // Define the const array for face names
    const string faceNames[6] = { "Front Face", "Left Face", "Right Face", "Back Face", "Top Face", "Bottom Face" };
    
    int size;  // Cube size, dynamically set at runtime

    // Helper method to randomize the cube
    void randomizeCube();


public:
    // Constructor that takes a cube size (e.g., 3 for a 3x3 cube)
    RubiksCube(int size);

    RubiksCube(const std::vector<vector<vector<char>>>&);

    // Function to return the size of the cube
    int getSize() const;

    // Function to rotate a specific face
    void rotateFace(int faceIndex, string direction);

    // Function to rotate a specific row or column
    void rotateRow(/*int faceIndex,*/ int rowIndex, char r_dir);
    void rotateColumn(/*int faceIndex, */int colIndex, char c_dir);

    void rotateMiddleRowLayer(string faceDir);
    void rotateMiddleColumnLayer(string faceColDir);

    // Helper method to map face input to index
    int getFaceIndex(char faceInput);

    // Method to display the current state of the cube
    void display() const;
};

#endif // RUBIKSCUBE_H
