#include <thread>
#include "Game Functions.h"
#include <stdlib.h>                     // Provides exit
#include <math.h>						// Provides toupper
#include <dos.h>						//Provides delay
using namespace std;

int main()
{
	Fnctns_Usd Func;
	initwindow(800,480,"The Slide Game");
	thread t(Show_Watch);
	Func.Wlcm_scr();
	Func.Prsnt_Menu();
	t.join();
	return 0;
}