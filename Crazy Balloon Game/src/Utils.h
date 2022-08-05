#ifndef UNTITLED1_UTILS_H
#define UNTITLED1_UTILS_H
#include <iostream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

// Function for start the grid with 0s for Part1
void initialGrid(int** &grid, int size){

    for(int i=0; i < size ; i++){
        grid[i] = new int[size];
    }

    for(int i=0; i < size ; i++) {
        for (int j = 0; j < size; j++){
            grid[i][j] = 0;

        }
    }
}

// Function for initialize grid for Part2
void initialNewGrid(int** &new_grid, int grid_size, vector<vector<string>> allTokens){

    for(int i=0; i < grid_size ; i++){
        new_grid[i] = new int[grid_size];
    }
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            new_grid[i][j] = stoi(allTokens[i+1][j]);
        }
    }
}

// Function for showing the grid
void show(int** &grid,int size,ofstream& output){

    for(int i=0; i < size ; i++) {
        for (int j = 0; j < size; j++){
            output<<grid[i][j]<<" ";
        }
        output<<endl;
    }

}

// Placing function for each line in input1.txt
void place(int row, int column,int size,int current,int** &grid){

    for(int i=0; i < size ; i++) {
        for (int j = 0; j < size; j++){
            if (grid[i][j]==grid[row][column] && grid[row][column]==0)
                grid[row][column]= current;
        }
    }
}

// Checking function if there is a link in the grid and if there is organise the grid
int check(int row, int column,int size,int current,int count,int** &grid,bool check_up,bool check_left,bool check_down,bool check_right, bool is_link){

    // Checking up
    if ((row>0) &&(grid[row-1][column]==current) &&  (check_up) ){
        count += check(row - 1, column, size, current, count, grid, true, true, false, true, false);
        if (is_link) {
            grid[row - 1][column] = 0;
            check(row - 1, column, size, current, count, grid, true, true, false, true, true);
        }

    // Checking left
    }if ( (column>0)&&(grid[row][column-1]==current) && (check_left)){

        count += check(row, column - 1, size, current, count, grid, true, true, true, false, false);
        if (is_link) {
            grid[row][column - 1] = 0;
            check(row, column - 1, size, current, count, grid, true, true, true, false, true);
        }

    // Checking down
    }if ((row<size-1) && (grid[row+1][column]==current) &&  (check_down) ){

        count += check(row + 1, column, size, current, count, grid, false, true, true, true, false);
        if (is_link) {
            grid[row + 1][column] = 0;
            check(row + 1, column, size, current, count, grid, false, true, true, true, true);
        }

    // Checking right
    }if ((column<size-1) && (grid[row][column+1]==current) && (check_right) ){
        count += check(row, column + 1, size, current, count, grid, true, false, true, true, false);
        if (is_link) {
            grid[row][column + 1] = 0;
            check(row, column + 1, size, current, count, grid, true, false, true, true, true);
        }
    }
    return count;
}

// Recursive function for part1 to check all link in the grid
void recursive(int row, int column,int size,int current,int** &grid){
    int count = check(row,column,size,current,1,grid, true, true, true, true, false);
    // If there is a link
    if (count>=3){
        check(row,column,size,current,1,grid, true, true, true, true, true);
        grid[row][column] = current + 1;
        recursive(row,column,size,current+1,grid);
    }
}

// Function for bomb all the current type of baloon in Part2
void bomb(int row,int column,int current,int grid_size,int &score,string direction,int** &new_grid){

    // Checking up
    if((row > 0) && (direction== "up")){
        if(new_grid[row-1][column] == current){
            new_grid[row-1][column] = 0;
            score += current;
        }
        row= row-1;
        bomb(row,column,current,grid_size,score,"up",new_grid);

    }
    // Checking upper left cross
    else if((row > 0)&& (column>0)&& (direction== "upper left cross")){
        if(new_grid[row-1][column-1] == current){
            new_grid[row-1][column-1] = 0;
            score += current;
        }
        row= row-1;
        column = column-1;
        bomb(row,column,current,grid_size,score,"upper left cross",new_grid);

    }
    // Checking left
    else if((column > 0) && (direction== "left")){
        if(new_grid[row][column-1] == current){
            new_grid[row][column-1] = 0;
            score += current;
        }
        column= column-1;
        bomb(row,column,current,grid_size,score,"left",new_grid);

    }
    // Checking lower left cross
    else if((row < grid_size-1) && ((column>0)) && (direction== "lower left cross")){
        if(new_grid[row+1][column-1] == current){
            new_grid[row+1][column-1] = 0;
            score += current;
        }
        row= row+1;
        column = column - 1 ;
        bomb(row,column,current,grid_size,score,"lower left cross",new_grid);

    }
    // Checking down
    else if((row < grid_size-1) && (direction== "down")){
        if(new_grid[row+1][column] == current){
            new_grid[row+1][column] = 0;
            score += current;
        }
        row= row+1;
        bomb(row,column,current,grid_size,score,"down",new_grid);

    }
    // Checking lower right cross
    else if((row < grid_size-1) && (column < grid_size-1) &&(direction== "lower right cross")){
        if(new_grid[row+1][column+1] == current){
            new_grid[row+1][column+1] = 0;
            score += current;
        }
        row= row+1;
        column = column+1;
        bomb(row,column,current,grid_size,score,"lower right cross",new_grid);

    }
    // Checking right
    else if((column < grid_size-1) && (direction== "right")){
        if(new_grid[row][column+1] == current){
            new_grid[row][column+1] = 0;
            score += current;
        }
        column = column+1;
        bomb(row,column,current,grid_size,score,"right",new_grid);

    }
    // Checking upper right cross
    else if((row >0) && (column < grid_size-1) &&(direction== "upper right cross")){
        if(new_grid[row-1][column+1] == current){
            new_grid[row-1][column+1] = 0;
            score += current;
        }
        row= row-1;
        column= column +1;
        bomb(row,column,current,grid_size,score,"upper right cross",new_grid);

    }
}
#endif //UNTITLED1_UTILS_H
