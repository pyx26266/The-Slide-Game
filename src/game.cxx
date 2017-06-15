#include "game.hxx"


SlideGame::SlideGame() {
    window.create(sf::VideoMode(800, 600), "Slide Game");
    font.loadFromFile("arial.ttf");
}

SlideGame::~SlideGame() {
    window.close();
}

bool SlideGame::initWindow(int width, int height, char* win_name) {

    window.setSize(sf::Vector2u(width, height));
    window.setTitle(win_name);
    window.setVerticalSyncEnabled(true);

    return window.isOpen();
}

void SlideGame::PollEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void SlideGame::WelcomeScr() {
    int length = 12;
    char str[] = "SLIDE GAME!!";

    sf::Text text(str, font, 20);
    sf::Text text2(str, font, 20);
    text.setString("WELCOME");
    text2.setString("TO THE");
    for (int i = 0; i < 29; ++i) {
        window.clear();

        text.setPosition(sf::Vector2f(-70+i*12,85));

        text2.setPosition(799-i*12, 100);
        window.draw(text);
        window.draw(text2);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    for (int i = 0, j = 0; i < length; ++i, j += 28) {
        text.setString(str[i]);
        text.setPosition(230+j, 150);
        window.draw(text);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(350));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void SlideGame::Rules() {
    window.clear();
    sf::RectangleShape rect(sf::Vector2f(705-95, 405-35));
    rect.setPosition(95, 35);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(10);
    rect.setOutlineColor(sf::Color(250, 150, 100));
    window.draw(rect);

    rect.setSize(sf::Vector2f(685-115, 385-55));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(115, 55);
    window.draw(rect);

    sf::Text text("", font, 20);
    text.setPosition(290, 50);
    text.setString("INSTRUCTIONS AND RULES");
    window.draw(text);

    text.setPosition(200, 90);
    text.setString("1. Use 'W' for up, 'S' for down, 'A' for left and 'D' for right.");
    window.draw(text);

    text.setPosition(200, 115);
    text.setString("2. Arrange the puzzle in proper order within a time limit of 3 minutes.");
    window.draw(text);

    text.setPosition(200, 140);
    text.setString("3. Bonus points for completing the puzzle before the time limit.");
    window.draw(text);

    text.setPosition(200, 165);
    text.setString("4. The time limit for solving puzzle may increase with the level.");
    window.draw(text);

    text.setPosition(200, 300);
    text.setString("PRESS ESCAPE TO GO BACK TO THE MAIN MENU");
    window.draw(text);

    window.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
        //previous menu
}

void SlideGame::Menu() {
    window.clear();

    sf::RectangleShape rect(sf::Vector2f(705-95, 405-35));
    rect.setPosition(95, 35);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(10);
    rect.setOutlineColor(sf::Color(250, 150, 100));
    window.draw(rect);

    sf::Text text("", font, 20);
    text.setPosition(300,50);
    text.setString("MAIN MENU");
    window.draw(text);

    text.setPosition(300,90);
    text.setString("1. New Game");
    window.draw(text);

    text.setPosition(300,100);
    text.setString("2. High Scores");
    window.draw(text);

    text.setPosition(300,130);
    text.setString("3. Instructions & Rules");
    window.draw(text);

    text.setPosition(300,150);
    text.setString("4. Quit");
    window.draw(text);

    text.setPosition(300,190);
    text.setString("Select any option to continue: ");
    window.draw(text);

    window.display();

}


void SlideGame::Loop() {

    clock.StartTimer();
    /*std::thread clock_thread([=]{
        while (clock.isRunning()) {
            if (clock.isOver())
                break;
            char msg = clock.ElapTime() + '0';
            sf::Text tx("     ", font, 20);
            window.draw(tx);
            tx.setString(msg);
            window.draw(tx);
            window.display();
        }
    });*/
    canvas.InitBoard();
    canvas.ScrambleBoard();

    sf::Text timer(char(clock.ElapTime() + '0'), font, 20);
    while (!canvas.isBoardSolved()) {
        PollEvent();
        DrawBoard();
        DrawNum();
        timer.setString(char(clock.ElapTime() + '0'));
        window.draw(timer);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(40));

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up)
                    canvas.MoveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    canvas.MoveDown();
                else if (event.key.code == sf::Keyboard::Left)
                    canvas.MoveLeft();
                else if (event.key.code == sf::Keyboard::Right)
                    canvas.MoveRight();
                else if (event.key.code == sf::Keyboard::Escape)
                    break;
                break;
            default:
                break;
            }
        }



    }



}

void SlideGame::DrawBoard() {
    window.clear();
    sf::RectangleShape rect(sf::Vector2f(705-95, 405-35));
    rect.setPosition(95, 35);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color(250, 150, 100));
    window.draw(rect);

    rect.setSize(sf::Vector2f(695-105, 395-45));
    rect.setFillColor(sf::Color::Transparent);
    rect.setPosition(115, 55);
    window.draw(rect);

    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(525, 45)),
                         sf::Vertex(sf::Vector2f(525, 395))};
    window.draw(line, 2, sf::Lines);

    rect.setSize(sf::Vector2f(377-255, 70-45));
    rect.setPosition(245, 45);
    window.draw(rect);

    rect.setSize(sf::Vector2f(505-125, 385-80));
    rect.setPosition(125, 80);
    window.draw(rect);

    line[0] = sf::Vertex(sf::Vector2f(525, 80));
    line[1] = sf::Vertex(sf::Vector2f(695, 80));
    window.draw(line, 2, sf::Lines);

    sf::Text text("", font, 20);
    text.setString("OPTIONS");
    text.setPosition(580, 55);
    window.draw(text);

    text.setString("1. RESTART LEVEL");
    text.setPosition(555, 109);
    window.draw(text);

    text.setString("2. PAUSE / PLAY");
    text.setPosition(555, 139);
    window.draw(text);

    text.setString("(Press Spacebar)");
    text.setPosition(567, 155);
    window.draw(text);

    text.setString("3. EXIT GAME");
    text.setPosition(555, 185);
    window.draw(text);

    rect.setSize(sf::Vector2f(245-145, 175-85));
    rect.setPosition(145, 85);
    window.draw(rect);

    rect.setSize(sf::Vector2f(365-265, 175-85));
    rect.setPosition(265, 85);
    window.draw(rect);

    rect.setSize(sf::Vector2f(485-385, 175-85));
    rect.setPosition(385, 85);
    window.draw(rect);

    rect.setSize(sf::Vector2f(245-145, 275-185));
    rect.setPosition(145, 185);
    window.draw(rect);

    rect.setSize(sf::Vector2f(365-265, 275-185));
    rect.setPosition(265, 185);
    window.draw(rect);

    rect.setSize(sf::Vector2f(485-385, 275-185));
    rect.setPosition(385, 185);
    window.draw(rect);

    rect.setSize(sf::Vector2f(245-145, 375-285));
    rect.setPosition(145, 285);
    window.draw(rect);

    rect.setSize(sf::Vector2f(365-265, 375-285));
    rect.setPosition(265, 285);
    window.draw(rect);

    rect.setSize(sf::Vector2f(485-385, 375-285));
    rect.setPosition(385, 285);
    window.draw(rect);

    window.display();
}

void SlideGame::DrawNum() {
    int buf[][2] = { {195, 120},
                     {315, 120},
                     {435, 120},
                     {195, 230},
                     {315, 230},
                     {435, 230},
                     {195, 340},
                     {315, 340},
                     {435, 340}
    };
    sf::Text txt("  ", font, 20);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (canvas.board[i][j])
                txt.setString(char(canvas.board[i][j] + '0'));
            else
                txt.setString("  ");
            txt.setPosition(buf[i*3+j][0], buf[i*3+j][1]);
            window.draw(txt);
        }
    }
}

//---------------------------------------------------------------Constructor for the class High Scores-----------------------------------------------//
/*
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
*/
