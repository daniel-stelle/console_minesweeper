/************************************************************************
* CLASS: Minesweeper
*
* CONSTRUCTORS:	
*	Minesweeper()
*		This constructor instantiates the object.
*
* METHODS:
*	void StartGame()
*		This method is what gets input from the user as to their choice in
*		the main menu and gets the game going.
*	void DisplayMenu()
*		This method displays the main menu.
*	void ProcessMenuChoice( int choice )
*		This method directs the program to the correct method according to
*		the user's menu choice from StartGame().
*	void ProcessGame( int row, int col, int num_bombs )
*		This method processes the game logistics such as whether or not
*		they have won/lost, the number of cells and bombs to be placed, etc.
*	bool PlayGame( Board & difficulty );
*		This method displays the user's options for actually playing the game
*		such as giving them the option to flag or uncover a selected space.
*	~Minesweeper();
*		Destructs the object.
*************************************************************************/
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include "Board.h"

using std::cout;
using std::endl;
using std::cin;

class Minesweeper
{
	public:
		Minesweeper();
		void StartGame();
		void DisplayMenu();
		void ProcessMenuChoice( int choice );
		void ProcessGame( int row, int col, int num_bombs );
		bool PlayGame( Board & difficulty );
		void SelectRow(char & row, Board & difficulty);
		void SelectCol(char & col, int & convert_col, Board & difficulty);
		void SelectAction(char & action);
		~Minesweeper();
};

#endif