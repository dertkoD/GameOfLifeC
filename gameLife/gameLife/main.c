#include <stdio.h>
#include <stdbool.h>
#include <windows.h> 
#include <conio.h>
#include <stdlib.h>
#include "startGame.h"
#include "game.h"

	void setCour(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	int Game() 
	{
		gameInitiation();
		bool game = true;

		while (game) 
		{
			setCour(0, 0);
			game = gameStart();
		}

		return 0;
	}

	int main(int argc, char* argv[])
	{
		Game();

		return 0;
	}
