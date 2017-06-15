#include <iostream>
#include <thread>
#include "game.hxx"

int main(int argc, char *argv[]) {
    SlideGame game;
    game.initWindow(800, 600, "Slide Game");

    //game.WelcomeScr();
    game.Menu();

    while (true) {
        game.PollEvent();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        game.Loop();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2));
        //show High Score
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        game.Rules();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        {game.End();}


}

/*
    events.join();


	Fnctns_Usd Func;
	initwindow(800,480,"The Slide Game");
	thread t(Show_Watch);
	Func.Wlcm_scr();
	Func.Prsnt_Menu();
	t.join();
*/
	return 0;
}
