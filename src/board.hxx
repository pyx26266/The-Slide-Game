#ifndef BOARD_HXX
#define BOARD_HXX
                                                 //To use the inbuilt graphics function
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

class Board {
  public:
     bool CheckUp();
     bool CheckDown();
     bool CheckLeft();
     bool CheckRight();
     bool isBoardSolved();
     void InitBoard();
     void ScrambleBoard();
     void MoveUp();
     void MoveDown();
     void MoveLeft();
     void MoveRight();
     void DisplayBoard();
     //void RefreshBoard();

     Board();
     int row, column, emp_row, emp_column;
     int board[3][3], solved_board[3][3];
};

#endif
