#include "board.hxx"

//--------------------------------------------------------------Constructor for the class Board-------------------------------------------------------//
Board:: Board()
{
    row= 0;
    column= 0;
    emp_row=0;
    emp_column=0;

    for (row = 0; row <= 2; row++)
        for (column = 0; column <= 2; column++)
            board[row][column]= 0;
}

//--------------------------------------------------------Function to initialize the board with values------------------------------------------------//

void Board::InitBoard()
{
    int i = 0;

    for(row= 0; row < 3; row++)
    {
        for(column= 0; column < 3; column++)
        {
            board[row][column] = i;
            solved_board[row][column]= (i+1);
            i++;
        }
    }
    solved_board[2][2]=0;
}

//-------------------------------------------------------------Function to scramble the board---------------------------------------------------------//

void Board::ScrambleBoard() {
    std::vector<int> temp_array(3 * 3);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            temp_array[i*3+j] = board[i][j];

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(temp_array.begin(), temp_array.end(),  std::default_random_engine(seed));

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = temp_array[i*3+j];

    if (isBoardSolved())
        ScrambleBoard();

    for(row= 0; row<=2; row++)
        for(column= 0; column<=2; column++)
            if (board[row][column] == 0) {
                emp_row = row;
                emp_column = column;
            }
}

//--------------------------------------------------------------Function to check for victory---------------------------------------------------------//

bool Board::isBoardSolved() {
    for(row=0; row<=2; row++)
        for(column=0; column<=2; column++)
            if(board[row][column] != solved_board[row][column])
                return false;
    return true;
}

//---------------------------------------------------------Function to check for valid move upwards---------------------------------------------------//

bool Board::CheckUp() {
    if(emp_row == 2)
        return false;
    else
        return true;
}

//--------------------------------------------------------Function to check for valid move downwards--------------------------------------------------//

bool Board::CheckDown() {
    if (emp_row == 0)
        return false;
    else
        return true;
}

//--------------------------------------------------------Function to check for valid move rightwards-------------------------------------------------//

bool Board::CheckRight() {
    if (emp_column == 0)
        return false;
    else
        return true;
}

//--------------------------------------------------------Function to check for valid move leftwards--------------------------------------------------//

bool Board::CheckLeft() {
    if (emp_column == 2)
        return false;
    else
        return true;
}

//-----------------------------------------------------------------Function to move upwards-----------------------------------------------------------//

void Board::MoveUp() {
    if (!CheckUp())
        return;
    int temp = board[emp_row][emp_column];
    board[emp_row][emp_column] = board[emp_row+1][emp_column];
    board[emp_row+1][emp_column] = temp;
    emp_row += 1;

}

//----------------------------------------------------------------Function to move downwards----------------------------------------------------------//

void Board::MoveDown() {
    if (!CheckDown())
        return;
    int temp = board[emp_row][emp_column];
    board[emp_row][emp_column]= board[emp_row-1][emp_column];
    board[emp_row-1][emp_column]= temp;
    emp_row-= 1;
}

//----------------------------------------------------------------Function to move leftwards----------------------------------------------------------//

void Board::MoveLeft() {
    if (!CheckLeft())
        return;
    int temp = board[emp_row][emp_column];
    board[emp_row][emp_column]= board[emp_row][emp_column+1];
    board[emp_row][emp_column+1]= temp;
    emp_column+= 1;
}

//----------------------------------------------------------------Function to move rightwards---------------------------------------------------------//

void Board::MoveRight() {
    if (!CheckRight())
        return;
    int temp = board[emp_row][emp_column];
    board[emp_row][emp_column] = board[emp_row][emp_column-1];
    board[emp_row][emp_column-1] = temp;
    emp_column -= 1;
}

//---------------------------------------------------------------Function to refresh the board--------------------------------------------------------//
/*
void Board::RefreshBoard() {
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
/*
//--------------------------------------------------Function to display the refreshed board everytime-------------------------------------------------//

void Board:: Display_Board() {

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

*/
