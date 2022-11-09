/*

Name: Revanth Gundala
Date: 4 November 2022
Description: Path Finder
Usage:

*/

#include <fstream> 
#include <iostream>
#include <string.h>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

// functions
void PrintEnvironment(int**, int, int);

// Prints the entire integer grid
void PrintEnvironment(int** array, int width, int height){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << setw(3) << array[i][j];
        }
        cout << "\n";
    }
}

// main function
int main(int argc, char** argv){

    // intialize variables
    int width, height, impassiblePercent, goalX, goalY, startX, startY;
    int** grid;
    
    // prompt user for input
    cout << "Welcome to Revanth's CSE240 WaveFront Pather\n" << endl;
    cout << "Enter the width (at least 10): " << endl;
    cin >> width;
    cout << "Enter the height (at least 10): " << endl;
    cin >> height;

    // initialize dynamic array
    grid = new int*[height];

    // make each pointer point to a new array
    for(int i = 0; i < height; i++){
        grid[i] = new int[width];
    }

    // set each square to 0
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            grid[i][j] = 0;
        }
    }

    // prompt user for input
    cout << "Enter the percent of impassible terrain (0 - 100): " << endl;
    cin >> impassiblePercent;

    // Condition
    if(impassiblePercent > 35){
        cout << "Having a value greater than 35% might create poor results, do you wish to continue? (y/n): " << endl;
        char ans;
        cin >> ans;
        // exit function if answer is no
        if(ans == 'n'){
            return 0;
        }
    }

    // number of -1's in the grid
    int impassibleNum = (impassiblePercent / 100.0) * height * width;
    
    // Set random squares in the grid to -1
    while(impassibleNum > 0){
        int row = rand() % height;
        int col = rand() % width;
        grid[row][col] = -1;
        impassibleNum--;
    }


    // prints the grid
    PrintEnvironment(grid, width, height);


    // prompt user for input
    cout << "Please enter the Goal Position X: " << endl;
    cin >> goalX;
    cout << "Please enter the Goal Position Y: " << endl;
    cin >> goalY;

    // check boundaries
    if(goalX < 0 || 
        goalX >= width||
        goalY < 0||
        goalY >= height||
        grid[goalY][goalX] == -1){  // y represents the number of rows and x the number of cols
            cout << "Sorry, that position is inside an obstacle\n" << endl;

            cout << "Please enter the Goal Position X: " << endl;
            cin >> goalX;
            cout << "Please enter the Goal Position Y: " << endl;
            cin >> goalY;
        }

    // set goal index to 1
    grid[goalY][goalX] = 1;

    
    //run the wave AKA create grid with initialized values
    queue<int> q_x;     // use queue for x values
    queue<int> q_y;     // use queue for y values
    q_x.push(goalX);
    q_y.push(goalY);

    // use a bfs to run through grid
    while(!q_x.empty() && !q_y.empty()){

        // get the x and y coordinates at the front of the queue
        int currX = q_x.front();
        int currY = q_y.front();

        // pop them out of the queue
        q_x.pop();
        q_y.pop();

        // current number in the grid
        int num = grid[currY][currX];

        // check neighbors of square, and add neighbors to queue if the neigbor is 0
        // add 1 to the current count
        if(currY - 1 >= 0 && grid[currY - 1][currX] == 0){
            grid[currY - 1][currX] = num + 1;
            q_x.push(currX);
            q_y.push(currY - 1);
        }
        if(currX + 1 < width && currY - 1 >= 0 && grid[currY - 1][currX + 1] == 0){
            grid[currY - 1][currX + 1] = num + 1;
            q_x.push(currX + 1);
            q_y.push(currY - 1);
        }
        if(currX + 1 < width && grid[currY][currX + 1] == 0){
            grid[currY][currX + 1] = num + 1;
            q_x.push(currX + 1);
            q_y.push(currY);
        }
        if(currX + 1 < width && currY + 1 < height && grid[currY + 1][currX + 1] == 0){
            grid[currY + 1][currX + 1] = num + 1;
            q_x.push(currX + 1);
            q_y.push(currY + 1);
        }
        if(currY + 1 < height && grid[currY + 1][currX] == 0){
            grid[currY + 1][currX] = num + 1;
            q_x.push(currX);
            q_y.push(currY + 1);
        }
        if(currX - 1 >= 0 && currY + 1 < height && grid[currY + 1][currX - 1] == 0){
            grid[currY + 1][currX - 1] = num + 1;
            q_x.push(currX - 1);
            q_y.push(currY + 1);
        }
        if(currX - 1 >= 0 && grid[currY][currX - 1] == 0){
            grid[currY][currX - 1] = num + 1;
            q_x.push(currX - 1);
            q_y.push(currY);
        }
        if(currX - 1 >= 0 && currY - 1 >= 0 && grid[currY - 1][currX - 1] == 0){
            grid[currY - 1][currX - 1] = num + 1;
            q_x.push(currX - 1);
            q_y.push(currY - 1);
        }
    
    }

    // dynamic character array
    char** charGrid;
    charGrid = new char*[height];
    for(int i = 0; i < height; i++){
        charGrid[i] = new char[width];
    }

    // parallel character array to environment array 
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(grid[i][j] == -1){
                charGrid[i][j] = '#';
            }
            else if (grid[i][j] == grid[goalY][goalX]){
                 charGrid[i][j] = '$';
            }
            else{
                charGrid[i][j] = ' ';
            }
        }
    }
    
    // prompt user for input
    cout << "Please enter the Start Position X: " << endl;
    cin >> startX;
    cout << "Please enter the Start Position Y: " << endl;
    cin >> startY;

    // check bounds
    if(startX < 0 || 
        startX >= width||
        startY < 0||
        startY >= height||
        grid[startY][startX] == -1){
            cout << "Sorry, that position is inside an obstacle\n" << endl;

            cout << "Please enter the Start Position X: " << endl;
            cin >> startX;
            cout << "Please enter the Start Position Y: " << endl;
            cin >> startY;
        }

    // set the starting position in the character grid
    charGrid[startY][startX] = '@';

    // greedy algorithm
    queue<int> queueX;
    queue<int> queueY;

    queueX.push(startX);
    queueY.push(startY);

    // variable to check if we have reached target
    bool found = false;

    while(!queueX.empty() && !queueY.empty()){
        // get the x and y values at front of queue
        int currX = queueX.front();
        int currY = queueY.front();
        queueX.pop();
        queueY.pop();

        // only add to the queue if the current element isn't visited
        if(charGrid[currY][currX] != '*'){

            // if the current grid is $, break the loop
            if(charGrid[currY][currX] == '$'){
                found = true;
                break;
            }

            // only mark it as * if we are not at the starting position
            if(charGrid[currY][currX] != '@' ){
                charGrid[currY][currX] = '*';
            }

            // get the current number in the grid
            int num = grid[currY][currX];

            // check neighbors, and go only to one of the squares that is not -1, and is less than the current number in the square
            if(currY - 1 >= 0 && grid[currY - 1][currX] != -1 && grid[currY - 1][currX] < num){
                queueX.push(currX);
                queueY.push(currY - 1);
            }
            
            else if(currX + 1 < width && currY - 1 >= 0 && grid[currY - 1][currX + 1] != -1 &&  grid[currY - 1][currX + 1] < num){
                queueX.push(currX + 1);
                queueY.push(currY - 1);
            }
            
            else if(currX + 1 < width && grid[currY][currX + 1] != -1 && grid[currY][currX + 1] < num){
                queueX.push(currX + 1);
                queueY.push(currY);
            }
            
            else if(currX + 1 < width && currY + 1 < height && grid[currY + 1][currX + 1] != -1 && grid[currY + 1][currX + 1] < num){
                queueX.push(currX + 1);
                queueY.push(currY + 1);
            }

            else if(currY + 1 < height && grid[currY + 1][currX] != -1 && grid[currY + 1][currX] < num){
                queueX.push(currX);
                queueY.push(currY + 1);
            }
            
            else if(currX - 1 >= 0 && currY + 1 < height && grid[currY + 1][currX - 1] != -1 && grid[currY + 1][currX - 1] < num){
                queueX.push(currX - 1);
                queueY.push(currY + 1);
            }
    
            else if(currX - 1 >= 0 && grid[currY][currX - 1] != -1 && grid[currY][currX - 1] < num){
                queueX.push(currX - 1);
                queueY.push(currY);
            }
            
            else if(currX - 1 >= 0 && currY - 1 >= 0 && grid[currY - 1][currX - 1] != -1 && grid[currY - 1][currX - 1] < num){
                queueX.push(currX - 1);
                queueY.push(currY - 1);
            }
        }
    }

    // if we didn't find the goal, then output no path found
    if(!found){
        cout << "No Path Found" << endl;
    }


    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
             cout << setw(3) << grid[i][j];
        }
        cout << "\n";
    }

    cout << "\n\n";

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            cout << setw(3) << charGrid[i][j];
        }
        cout << "\n";
    }

    // open up the output file, and write the output grid to it
    ofstream oFile; 
    oFile.open("wave.txt");
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
             oFile << setw(3) << grid[i][j];
        }
        oFile << "\n";
    }

    oFile << "\n\n";

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            oFile << setw(3) << charGrid[i][j];
        }
        oFile << "\n";
    }

    // close output file when we are done writing to it
    oFile.close();

    // delete the dynamic arrays to free up memory
    for(int i = 0; i < height; i++){
        delete[] grid[i];
        delete[] charGrid[i];
    }

    delete[] grid;
    delete[] charGrid;
    return 0;
}