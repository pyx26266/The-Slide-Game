#include "graphics.h"													 //To use the inbuilt graphics function	
#include <iostream>
#include<thread>
#include<time.h>
#include<stdlib.h>

using namespace std;

class Board{
			 public:
			 bool Check_Up(char);
			 bool Check_Down(char);
			 bool Check_Left(char);
			 bool Check_Right(char);
			 bool Is_Board_Solved();
			 void Initialize_Board();
			 void Scramble_Board();
			 void Move_Up(char move);
			 void Move_Down(char move);
			 void Move_Left(char move);
			 void Move_Right(char move);
			 void Display_Board();
			 void Refresh_Board();
			
			 Board();
			 char move;
			 bool move_up, move_down, move_right, move_left;
			 int row, column, emp_row, emp_column;
			 int board[3][3], solved_board[3][3];
			 int counter;
		   }Brd;

//--------------------------------------------------------------Constructor for the class Board-------------------------------------------------------//
Board:: Board()
{
	row= 0;
	column= 0;
	emp_row=0;
	emp_column=0;
	counter= 0;
	move_up= true;
	move_down= true;
	move_left= true;
	move_right= true;
	for(row= 0; row<=2; row++)
	{
		for(column= 0; column<=2; column++)
			board[row][column]= 0;
	}
}

//--------------------------------------------------------Function to initialize the board with values------------------------------------------------//

void Board:: Initialize_Board()
{
	int i=0;
	
	for(row= 0; row<=2; row++)
	{
		for(column= 0; column<=2; column++)
		{
			board[row][column]= i;
			solved_board[row][column]= (i+1);
			i++;
		}
	}
	solved_board[2][2]=0;
}

//-------------------------------------------------------------Function to scramble the board---------------------------------------------------------//

void Board:: Scramble_Board()
{
	time_t t;
	int rnd_num, rnd_num2, temp=0;
	srand((unsigned) time(&t));
	do{
		
		rnd_num= rand()%3;
		rnd_num2=rand()%3;

		for(row=0;row<=2;row++)
		{
			for(column=0;column<=2;column++)
			{
				if(column==rnd_num)
				{
					temp= board[row][column];
					board[row][column]= board[row][rnd_num2];
					board[row][rnd_num2]= temp;
				}
			}
		}

		for(column=0;column<=2;column++)
		{
			for(row=0;row<=2;row++)
			{
				if(row==rnd_num)
				{
					temp= board[row][column];
					board[row][column]= board[rnd_num2][column];
					board[rnd_num2][column]= temp;
				}
			}
		}
	  }while(Is_Board_Solved());
	for(row= 0; row<=2; row++)
	{
		for(column= 0; column<=2; column++)
		{
			if(board[row][column]==0)
			{
				emp_row= row;
				emp_column= column;
			}
		}
	}
}

//--------------------------------------------------------------Function to check for victory---------------------------------------------------------//

bool Board:: Is_Board_Solved()
{
	bool board_solved = false;
	bool flag=FALSE;				//to get game board status.
	for(row=0; row<=2; row++)
	{
		for(column=0; column<=2; column++)
		{
			if(board[row][column]!=solved_board[row][column])
			{flag=TRUE;break;	}
			
		}
		if(flag==TRUE)
			break;
	}
	if(flag==FALSE)
		board_solved=TRUE;
	return board_solved;
}

//---------------------------------------------------------Function to check for valid move upwards---------------------------------------------------//

bool Board:: Check_Up(char move)
{
	if(emp_row==2 && (move== 'w' || move== 'W'))
		move_up= false;
	else
		move_up=true;
	return move_up;
}

//--------------------------------------------------------Function to check for valid move downwards--------------------------------------------------//

bool Board:: Check_Down(char move)
{
	if(emp_row==0 && (move== 's' || move== 'S'))
		move_down= false;
	else
		move_down=true;
	return move_down;
}

//--------------------------------------------------------Function to check for valid move rightwards-------------------------------------------------//

bool Board:: Check_Right(char move)
{
	if(emp_column==0 && (move== 'd' || move== 'D'))
		move_right= false;
	else
		move_right= true;
	return move_right;
}

//--------------------------------------------------------Function to check for valid move leftwards--------------------------------------------------//

bool Board:: Check_Left(char move)
{
	if(emp_column==2 && (move== 'a' || move== 'A'))
		move_left= false;
	else
		move_left= true;
	return move_left;
}

//-----------------------------------------------------------------Function to move upwards-----------------------------------------------------------//

void Board:: Move_Up(char move)
{	
	int temp;
	while (Check_Up(move) && counter<1)
	{
		temp = board[emp_row][emp_column];
		board[emp_row][emp_column]= board[emp_row+1][emp_column];
		board[emp_row+1][emp_column]= temp;
		emp_row+= 1;
		counter++;														//To limit the sliding of the tile to only once
		Display_Board();
	}
	counter=0;
}

//----------------------------------------------------------------Function to move downwards----------------------------------------------------------//

void Board:: Move_Down(char move)
{
	int temp;
	while (Check_Down(move) && counter<1)
	{
		temp = board[emp_row][emp_column];
		board[emp_row][emp_column]= board[emp_row-1][emp_column];
		board[emp_row-1][emp_column]= temp;
		emp_row-= 1;
		counter++;														//To limit the sliding of the tile to only once
		Display_Board();
	}
	counter=0;
}

//----------------------------------------------------------------Function to move leftwards----------------------------------------------------------//

void Board:: Move_Left(char move)
{
	int temp;
	while (Check_Left(move) && counter<1)
	{
		
		temp = board[emp_row][emp_column];
		board[emp_row][emp_column]= board[emp_row][emp_column+1];
		board[emp_row][emp_column+1]= temp;
		emp_column+= 1;
		counter++;															//To limit the sliding of the tile to only once
		Display_Board();
	}
	counter=0;
}

//----------------------------------------------------------------Function to move rightwards---------------------------------------------------------//

void Board:: Move_Right(char move)
{
	int temp;
	while (Check_Right(move) && counter<1)
	{		
		temp = board[emp_row][emp_column];
		board[emp_row][emp_column]= board[emp_row][emp_column-1];
		board[emp_row][emp_column-1]= temp;
		emp_column-= 1;
		counter++;															//To limit the sliding of the tile to only once
		Display_Board();
	}
	counter=0;
}

//---------------------------------------------------------------Function to refresh the board--------------------------------------------------------//

void Board:: Refresh_Board()
{
	cleardevice();
	int buf[]={95,35,
				705,35,
				705,405,
				95,405,
				95,395,
				695,395,
				695,45,
				105,45,
				105,395,
				95,395,
				95,35
	};
	
	rectangle(105,45,695,395);
	line(525,45,525,395);
	rectangle(255,45,377,70);
	//rectangle(370,45,470,70);
	rectangle(125,80,505,385);
	line(525,80,695,80);
	fillpoly(11,buf);
	
	//outtextxy(380,49,"SCORE");
	outtextxy(580,55,"OPTIONS");
	outtextxy(555,109,"1. RESTART LEVEL");
	outtextxy(555,139,"2. PAUSE / PLAY");
	outtextxy(567,155,"(Press Spacebar)");
	outtextxy(555,185,"3. EXIT GAME");

	rectangle(145,85,245,175);
	rectangle(265,85,365,175);
	rectangle(385,85,485,175);
	rectangle(145,185,245,275);
	rectangle(265,185,365,275);
	rectangle(385,185,485,275);
	rectangle(145,285,245,375);
	rectangle(265,285,365,375);
	rectangle(385,285,485,375);
}

//--------------------------------------------------Function to display the refreshed board everytime-------------------------------------------------//

void Board:: Display_Board()
{	

	if(board[0][0]==0)
	{
		bgiout<<"  ";
		outstreamxy(195,120);
	}
	else
	{
		bgiout<<board[0][0];
		outstreamxy(195,120);
	}

	if(board[0][1]==0)
	{
		bgiout<<"  ";
		outstreamxy(315,120);
	}
	else
	{
		bgiout<<board[0][1];
		outstreamxy(315,120);
	}
	
	if(board[0][2]==0)
	{
		bgiout<<"  ";
		outstreamxy(435,120);
	}
	else
	{
		bgiout<<board[0][2];
		outstreamxy(435,120);
	}

	if(board[1][0]==0)
	{
		bgiout<<"  ";
		outstreamxy(195,230);
	}
	else
	{
		bgiout<<board[1][0];
		outstreamxy(195,230);
	}

	if(board[1][1]==0)
	{
		bgiout<<"  ";
		outstreamxy(315,230);
	}
	else
	{
		bgiout<<board[1][1];
		outstreamxy(315,230);
	}

	if(board[1][2]==0)
	{
		bgiout<<"  ";
		outstreamxy(435,230);
	}
	else
	{
		bgiout<<board[1][2];
		outstreamxy(435,230);
	}

	if(board[2][0]==0)
	{
		bgiout<<"  ";
		outstreamxy(195,340);
	}
	else
	{
		bgiout<<board[2][0];
		outstreamxy(195,340);
	}
	
	if(board[2][1]==0)
	{
		bgiout<<"  ";
		outstreamxy(315,340);
	}
	else
	{
	bgiout<<board[2][1];
	outstreamxy(315,340);
	}
	
	if(board[2][2]==0)
	{
		bgiout<<"  ";
		outstreamxy(435,340);
	}
	else
	{
		bgiout<<board[2][2];
		outstreamxy(435,340);
	}
}

