/***********************************************************
* Author:					Daniel Stelle
* Date Created:				1/13/14
* Last Modification Date:	1/17/14
* Lab Number:				Lab 1 - Minesweeper
* Filename:					Lab 1.cpp
*
* OVERVIEW:
*	This program is the game of Minesweeper. It will allow
*	the user to choose from 3 different difficulties: Beginner,
*	intermediate and expert.
*
* INPUT:
*	The Minesweeper class will take the coordinates and menu
*	options
*
* OUPUT:
*	The output is the game board for Minesweeper and is
*	displayed in the format:
*
*			A B C D E F G...
*		 A  ? ? ? ? ? ? ?...
*		 B  ? F ? ? X 2 ?...
*		 C  1 ? ? ? ? 1 ?...
*				 ...
************************************************************/
#include <crtdbg.h> 
#define  _CRTDBG_MAP_ALLOC
#include "Minesweeper.h"

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Minesweeper game;

	game.StartGame();
	
	return 0;
}