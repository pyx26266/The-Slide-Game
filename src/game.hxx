#ifndef GAME_HXX
#define GAME_HXX

#include <iostream>													 //To use the clock functions
#include <thread>														 //To create the timer thread to enable multiprocessing	
#include <chrono>
#include <SFML/Graphics.hpp>
#include "board.hxx"
#include "timer.hxx"


//-----------------------------------------------------------Contains the functions used in the game--------------------------------------------------//
/*
class Game {
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
*/
//-----------------------------------------------------------Contains the functions for score calculations-------------------------------------------//
/*
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
*/
class SlideGame {
private:
    sf::Font font;
    sf::RenderWindow window;
    Board canvas;
    Timer clock;
public:
    SlideGame();
    ~SlideGame();
    bool initWindow(int width, int height, char* win_name);
    void PollEvent();
    void WelcomeScr();
    void Rules();
    void Menu();
    void Loop();
    void DrawBoard();
    void DrawNum();
    void End() {window.close();}
};

#endif
