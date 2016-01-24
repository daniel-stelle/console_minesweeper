#include "Minesweeper.h"
#include "Board.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

enum MENU{ BEGINNER = 1, INTERMEDIATE, EXPERT, QUIT };

/***************************************************************
*   Purpose: This constructor instantiates the object.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Minesweeper::Minesweeper()
{ }

/***************************************************************
*   Purpose: This method is what gets input from the user as to 
*			 their choice in the main menu and gets the game going.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
void Minesweeper::StartGame()
{
	Board board;
	int   choice = 0;

	do
	{
		DisplayMenu();

		cout << "\nPlease select an option: ";
		cin  >> choice;
		cin.sync();
		cin.clear();

		ProcessMenuChoice( choice );

	} while( choice != 4 );
}

/***************************************************************
*   Purpose: This method displays the main menu.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
void Minesweeper::DisplayMenu()
{
	system( "cls" );

	cout << "WELCOME TO MINESWEEPER" << endl;

	cout << "\nPlease choose a difficulty:"
		 << "\n\n1) Beginner	(10x10, 10 mines)"
		 << "\n2) Intermediate (16x16, 40 mines)"
		 << "\n3) Expert	(16x30, 100 mines)"
		 << "\n\n4) Quit game" << endl;
}

/***************************************************************
*   Purpose: This method directs the program to the correct
*			 method according to the user's menu choice from
*			 StartGame().
*            
*     Entry: The user's menu choice
*            
*      Exit: None
****************************************************************/
void Minesweeper::ProcessMenuChoice( int choice )
{
	switch( choice )
	{
		case BEGINNER:
		{
			ProcessGame( 10, 10, 10 );
			break;
		}
		case INTERMEDIATE:
		{
			ProcessGame( 16, 16, 40 );
			break;
		}
		case EXPERT:
		{
			ProcessGame( 16, 30, 100 );
			break;
		}
		case QUIT:
		{
			// Do nothing and let program end
			break;
		}
		default:
		{
			cout << "ERROR: Invalid input." << endl;
		}
	}
}

/***************************************************************
*   Purpose: This method processes the game logistics such as
*			 whether or not they have won/lost, the number of
*			 cells and bombs to be placed, etc.
*            
*     Entry: The row, column and the number of bombs to be put
*			 on the board
*            
*      Exit: None
****************************************************************/
void Minesweeper::ProcessGame( int row, int col, int num_bombs )
{
	bool loss = false;
	int  num_covered = 0;

	Board game( row, col, num_bombs );
	game.PlaceBombs();
	game.DisplayBoard();

	while( loss == false && num_covered != num_bombs )
	{
		loss = PlayGame( game );
		num_covered = game.DisplayBoard();
	}

	if( loss == true )
		cout << "\n\nSorry, you have hit a bomb.\n" << endl;

	if( num_covered == num_bombs )
		cout << "\n\nCongratulations! You win!\n" << endl;

	system( "pause" );
}

/***************************************************************
*   Purpose: This method displays the user's options for actually
*			 playing the game such as giving them the option to
*			 flag or uncover a selected space.
*            
*     Entry: A Board object passed by reference.
*            
*      Exit: Returns true of the player has lost and false if
*			 they are still okay.
****************************************************************/
bool Minesweeper::PlayGame( Board & difficulty )
{
	char row = '\0';
	char col = '\0';
	char action = '\0';
	int  convert_col = 0;

	cout << '\n' << endl;

	SelectRow(row, difficulty);
	SelectCol(col, convert_col, difficulty);
	SelectAction(action);

	return difficulty.ProcessCells( row, col, action );
}

/***************************************************************
*   Purpose: Gets the input for the row that the user wants.
*
*     Entry: Row variable, and the board.
*
*      Exit: Sets the row.
****************************************************************/
void Minesweeper::SelectRow(char & row, Board & difficulty)
{
	do
	{
		cout << "Select row: ";
		cin >> row;
		cin.sync();
		cin.clear();

		if ((static_cast<int>(toupper(row)) - 65) < 0 ||
			(static_cast<int>(toupper(row)) - 65) > difficulty.GetRows())
		{
			cout << "ERROR: Invalid input.\n" << endl;
		}

	} while ((static_cast<int>(toupper(row)) - 65) < 0 ||
		(toupper(static_cast<int>(toupper(row)) - 65)) > difficulty.GetRows());
}

/***************************************************************
*   Purpose: Gets the input for the column that the user wants.
*
*     Entry: Column variable, and the board.
*
*      Exit: Sets the column.
****************************************************************/
void Minesweeper::SelectCol(char & col, int & convert_col, Board & difficulty)
{
	do
	{
		cout << "Select column: ";
		cin >> col;
		cin.sync();
		cin.clear();

		if (isalpha(col))
			convert_col = static_cast<int>(toupper(col)) - 65;
		else
			convert_col = static_cast<int>(toupper(col)) - 23;

		if (convert_col < 0 || convert_col > difficulty.GetCols())
			cout << "ERROR: Invalid input.\n" << endl;

	} while (convert_col < 0 || convert_col > difficulty.GetCols());
}

/***************************************************************
*   Purpose: Gets the input for the action that the user wants
*			 to take on their selected cell.
*
*     Entry: Action variable.
*
*      Exit: Sets the action.
****************************************************************/
void Minesweeper::SelectAction(char & action)
{
	do
	{
		cout << "\nACTIONS:"
			<< "\nU) Uncover"
			<< "\nF) Toggle Flag"
			<< "\n\nSelect an action: ";
		cin >> action;
		cin.sync();
		cin.clear();

		if (toupper(action) != 'U' &&
			toupper(action) != 'F')
		{
			cout << "ERROR: Invalid input.\n" << endl;
		}

	} while (toupper(action) != 'U' &&
		toupper(action) != 'F');
}

/***************************************************************
*   Purpose: Destructs the object.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Minesweeper::~Minesweeper()
{

}