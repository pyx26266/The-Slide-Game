#include "graphics.h"													 //To use the inbuilt graphics function	
#include "Board.h"
#include <iostream>
#include<fstream>
#include<thread>
#include<streambuf>
#include<time.h>														 //To use the clock functions	
#include <thread>														 //To create the timer thread to enable multiprocessing	
using namespace std;

Board Brd1;

//-----------------------------------------------------------Contains the timer related functions-----------------------------------------------------//

class Timer {
	private:
		bool Resetted;
		bool running;
		bool over;
		unsigned long beg;
		unsigned long end;
		
	public:
		int avail_time;
		Timer(); 
		void Start_Timer();
		void Stop_Timer();
		void Reset_Timer();
		bool isRunning();
		unsigned long Elap_Time();
		bool isOver();
		friend void Show_Watch();
}Tym;

//-----------------------------------------------------------Contains the functions used in the game--------------------------------------------------//

class Fnctns_Usd{
					public:
					void Wlcm_scr();
					void Game_Scr();
					void Inst_N_Rules();
					void High_Scores();
					void Prsnt_Menu();
					void Exit_Game();
					void Restart_Level();
					void Pause_N_Play();
};												

//-----------------------------------------------------------Contains the functions for score calculations-------------------------------------------//

class High_Scores{
					public:
					High_Scores();
					void calc_score();
					void give_bonus();
					void High_Score();
					int Total_Score();
					void Disp_High_Score();
					int max_score, total_score, score, bonus, disp_score;
					char Name[30];
					unsigned long disp_time;
}Hi_Scr;

//---------------------------------------------------------------Constructor for the class High Scores-----------------------------------------------//

High_Scores:: High_Scores()
{
	score= 0;
	total_score= 0;	
	max_score= 0;
	bonus= 0;
	disp_score=0;
	disp_time=0;
}

//-------------------------------------------------------------Function for calculating score---------------------------------------------------------//

void High_Scores:: calc_score()
{
	score+= 50;
	give_bonus();
}

//--------------------------------------------------------------Function to give bonus score----------------------------------------------------------//

void High_Scores:: give_bonus()
{
	if(Tym.Elap_Time()<= (5/6)*Tym.avail_time && Tym.Elap_Time()>= (2/3)*Tym.avail_time )
	{
		bonus= score/5;
		total_score= score + bonus;
	}

	else if(Tym.Elap_Time()<= (2/3)*Tym.avail_time && Tym.Elap_Time()>= (1/2)*Tym.avail_time)
	{
		bonus= (2*score)/5;
		total_score= score + bonus;
	}

	else
	{
		bonus= score/2;
		total_score= score + bonus;
	}
}

//-------------------------------------------------------------Function to calculate total score------------------------------------------------------//

int High_Scores:: Total_Score()
{
	calc_score();
	return total_score;
}

//-------------------------------------------------------------Function to calculate High Score-------------------------------------------------------//

void High_Scores:: High_Score()
{
	if(total_score > max_score)
		{
			max_score= total_score;
		}
}

//-------------------------------------------------------------Function to calculate High Score-------------------------------------------------------//

void High_Scores:: Disp_High_Score()
{
		disp_time= Tym.Elap_Time();
		disp_score= Hi_Scr.Total_Score();

		fstream object;
		object.open("TSG_Data");
		
		object.write((char*)&Hi_Scr, sizeof(Hi_Scr));
}

//------------------------------------------------------------------Constructor for the class Timer--------------------------------------------------//

Timer::Timer() 
{
	Resetted = true;
	running = false;
	over= true;
	beg = 0;
	end = 0;
	avail_time=60;
}

//----------------------------------------------------------------Function to Show the watch----------------------------------------------------------//

void Show_Watch()
{
	for(;;)
	{

		if(Tym.isRunning())
		{
			bgiout<<"Time: "<<Tym.Elap_Time()<<" Seconds";
			outstreamxy(265,50);
			
			if(Tym.isOver())
			{
				cleardevice();
				Tym.Stop_Timer();
				Tym.Reset_Timer();
				cleardevice();
				rectangle(210,165,610,290);
				rectangle(225,180,595,275);
				bgiout<<"Ooops Time over.. Better luck next time...";
				outstreamxy(295,220);
				delay(1000);
				bgiout<<"Please wait while exittingg....";
				outstreamxy(295,230);
				delay(3000);
				exit(0);
			}

		}
		Sleep(900);
	}
}

//---------------------------------------------------------------Function to Start the Timer----------------------------------------------------------//

void Timer::Start_Timer() 
{

	{
		if(!running) 
		{
			if(Resetted)
				beg = (unsigned long) clock();
			else
				beg -= end - (unsigned long) clock();
			running = true;
			Resetted = false;
		}
	}
}

//---------------------------------------------------------------Function to Stop the Timer----------------------------------------------------------//

void Timer::Stop_Timer() 
{
	if(running) 
	{
		end = (unsigned long) clock();
		running = false;
	}
}

//---------------------------------------------------------------Function to Reset the Timer----------------------------------------------------------//

void Timer::Reset_Timer() 
{
	bool wereRunning = running;
	if(wereRunning)
		Stop_Timer();
	Resetted = true;
	beg = 0;
	end = 0;
	if(wereRunning)
		Start_Timer();
}

//--------------------------------------------------------Function to check whether timer is running-------------------------------------------------//

bool Timer::isRunning() 
{
	return running;
}

//-------------------------------------------------------------Function to calculate elapsed time-----------------------------------------------------//

unsigned long Timer::Elap_Time() 
{
	if(running)
		return ((unsigned long) clock() - beg) / CLOCKS_PER_SEC;
	else
		return (end - beg)/CLOCKS_PER_SEC;
}

//----------------------------------------------------------Function to check whether time is over----------------------------------------------------//

bool Timer::isOver() 
{
	if(Tym.Elap_Time()>=60)
		return over;
	else
		return false;
}

//----------------------------------------------------------------Function to restart the level-------------------------------------------------------//

void Fnctns_Usd:: Restart_Level()
{
	Tym.Stop_Timer();
	cleardevice();
	bgiout<<"Hit any key to continue....";
	outstreamxy(200,200);
	getch();
	cleardevice();
	Tym.Reset_Timer();
	Game_Scr();
}

//-----------------------------------------------------------Function to Pause and Replay the game----------------------------------------------------//

void Fnctns_Usd:: Pause_N_Play()
{
	int ch;
	Tym.Stop_Timer();
	
	Label_2:
	ch= getch();

	switch(ch)
	{
	case 49: Restart_Level();
		break;
	case 32: Tym.Start_Timer();
		break;
	case 51: Exit_Game();
		break;
	default: cout<<"\a" ; 
			 goto Label_2;
		break;
	}
	
}

//-----------------------------------------------------------------Function to Exit the Game----------------------------------------------------------//

void Fnctns_Usd:: Exit_Game()
{
	Tym.Stop_Timer();
	Tym.Reset_Timer();
	cleardevice();
	Prsnt_Menu();
}

//------------------------------------------------------------Function to Present the Welcome Screen--------------------------------------------------//

void Fnctns_Usd:: Wlcm_scr()				//Welcome Screen
{
	int i;						//To be used in the loop
	int length;								
	char str[]= "SLIDE GAME!!";
	length= strlen(str);	//To store the length of the string i.e., Slide Game!!
	int j=0;

	for(int i=0;i<29;++i)
	{
		cleardevice();
		settextstyle(1,0,2);
		outtextxy(-70+i*12,85,"WELCOME");
		outtextxy(799-i*12,100,"TO THE");
		delay(50);
	}
	for(i=0; i<=length; i++)
	{
		j+=28;
		settextstyle(10,0,5);
		bgiout<<str[i];
		outstreamxy(230+j,150);
		delay(350);							//To delay printing
	}
	
	delay(2000);
}

//-------------------------------------------------------------Function to Present the Game Screen----------------------------------------------------//

void Fnctns_Usd::  Game_Scr()			//To present Game Board			
{
	int inpt;							//For accepting the input for exit/restart or pause

	Brd1.Initialize_Board();
	Brd1.Scramble_Board();
	Brd1.Refresh_Board();
	Brd1.Display_Board();

	Tym.Start_Timer();

	do{
			inpt= getch();
			switch(inpt)
			{
			case 49: Restart_Level();
				break;
			case 32: Pause_N_Play();
				break;
			case 87: Brd1.Move_Up((char) inpt);
				break;
			case 119: Brd1.Move_Up((char) inpt);
				break;
			case 83: Brd1.Move_Down((char) inpt);
				break;
			case 115: Brd1.Move_Down((char) inpt);
				break;
			case 65: Brd1.Move_Left((char) inpt);
				break;
			case 97: Brd1.Move_Left((char) inpt);
				break;
			case 68: Brd1.Move_Right((char) inpt);
				break;
			case 100: Brd1.Move_Right((char) inpt);
				break;
			case 51: Exit_Game();
				break;
			default: break;
			}
	
	}while(!Brd1.Is_Board_Solved());
	
	Tym.Stop_Timer();
	
	Sleep(1500);
	cleardevice();

	rectangle(210,165,610,290);
	rectangle(225,180,595,275);
	bgiout<<"Congratzz!! You've won the game...";
	outstreamxy(295,190);

	bgiout<<"You took "<<Tym.Elap_Time()<<" seconds to complete the game..";
	outstreamxy(285,220);

	bgiout<<"Your Score iss  "<<Hi_Scr.Total_Score();
	outstreamxy(355,250);

	cleardevice();
	
	rectangle(210,165,610,290);
	rectangle(225,180,595,275);
	
	bgiout<<"Enter your name: ";
	outstreamxy(295,190);
	cin.getline(Hi_Scr.Name,30);

	Tym.Reset_Timer();
	delay(3000);
	Prsnt_Menu();
}

//-------------------------------------------------------------Function to Show the Inst & Rules------------------------------------------------------//

void Fnctns_Usd::  Inst_N_Rules()	//To present the Instructions and Rules 
{
	int ch;
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
	fillpoly(11,buf);
	rectangle(115,55,685,385);
	settextstyle(10,0,1);
	outtextxy(290,50,"INSTRUCTIONS AND RULES");
	settextstyle(11,0,1);
	outtextxy(200,90,"1. Use 'W' for up, 'S' for down, 'A' for left and 'D' for right.");
	outtextxy(200,115,"2. Arrange the puzzle in proper order within a time limit of 3 minutes.");
	outtextxy(200,140,"3. Bonus points for completing the puzzle before the time limit.");
	outtextxy(200,165,"4. The time limit for solving puzzle may increase with the level.");

	outtextxy(250,300,"PRESS ESCAPE TO GO BACK TO THE MAIN MENU");
	ch= getch();
	if(ch==KEY_ESC)
	{
		Prsnt_Menu();
	}
	else 
	{
		std::cout<<"\a";
		Inst_N_Rules();
	}
}

//--------------------------------------------------------------Function to Show the High Scores------------------------------------------------------//

void Fnctns_Usd::  High_Scores()		//To present the High Scores			
{
	int ch;
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
	fillpoly(11,buf);
	rectangle(115,55,685,385);
	settextstyle(10,0,1);
	outtextxy(340,50,"HIGH SCORES");
	settextstyle(11,0,1);

	outtextxy(140,90,"S. NUM");
	outtextxy(290,90,"NAME");
	outtextxy(450,90,"TIME");
	outtextxy(600,90,"SCORE");
	outtextxy(160,120,"1.");
	outtextxy(160,150,"2.");
	outtextxy(160,180,"3.");
	outtextxy(160,210,"4.");
	outtextxy(160,240,"5.");


	outtextxy(250,300,"PRESS ESCAPE TO GO BACK TO THE MAIN MENU");
	ch= getch();
	if(ch==KEY_ESC)
	{
		Prsnt_Menu();
	}
	else
	{
		std::cout<<"\a"; 
		High_Scores();
	}
}

//-------------------------------------------------------------Function to Present the Main Menu------------------------------------------------------//

void Fnctns_Usd::  Prsnt_Menu()		//To present the menu				
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
	rectangle(115,55,685,385);

	int Opt;					//To get the option from the user.
	fillpoly(11,buf);
	settextstyle(10,0,1);
	outtextxy(350,50,"MAIN MENU");
	settextstyle(11,0,1);
	outtextxy(300,90,"1. New Game");
	outtextxy(300,110,"2. High Scores");
	outtextxy(300,130,"3. Instructions & Rules");
	outtextxy(300,150,"4. Quit");
	outtextxy(300,190,"Select any option to continue: ");


	Opt=getch();


	switch(Opt)
	{
	case 49: Game_Scr();
		break;
	case 50: High_Scores();
		break;
	case 51: Inst_N_Rules();
		break;
	case 52: exit(0);
		break;
	default: Prsnt_Menu();
		break;
	}
}

