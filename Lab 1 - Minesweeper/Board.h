/************************************************************************
* CLASS: Board
*
* CONSTRUCTORS:	
*	Board()
*		Default constructor for Board.
*	Board( int rows, int cols, int bombs )
*		This constructor takes 3 arguments and sets up a Board using
*		those arguments.
*	Board( const Board & copy )
*		Copy constructor for Board.
*
* METHODS:
*	Board & operator=( const Board & rhs )
*		Overloads the assignment operator so that two Board objects
*		can be assigned to each other.
*	void SetRows( int rows )
*		This method sets the total number of rows on the Board.
*	void SetCols( int cols )
*		This method sets the total number of columns on the Board.
*	void SetBombs( int bombs )
*		This method sets the total number of bombs that will be placed
*		on the Board.
*	int GetRows()
*		This method returns the total number of rows that the Board
*		currently has.
*	int GetCols()
*		This method returns the total number of columns that the Board
*		currently has.
*	void SetNumber( int r, int c )
*		This method will determine the number of bombs that it has
*		surrounding it.
*	void PlaceBombs()
*		This method will disperse the correct amount of bombs around
*		the board depending on the difficulty.
*	int DisplayBoard()
*		This method will display the current Board according to flags
*		that are set in the Cell objects.
*	bool ProcessCells( const char r, const char c, char action )
*		This method processes the users input as to which Cell they want
*		to modify (uncover or toggle flag) and sets the Cell's flags
*		accordingly.
*	int ConvertCoords( char x )
*		This method converts the coordinate that is passed in from a char
*		to an int.
*	bool CascadeCells( int row, int col )
*		This method reveals all blank Cells around the selected cell if
*		the selected Cell is blank.
*	void UncoverAllCells()
*		This function marks all spaces as uncoverd for when the player
*		losses so that they can see the entire board.
*	bool IsLoss( Cell cell )
*		This method detects whether the Cell that is passed in is a bomb.
*	~Board()
*		This method destructs the class.
*************************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "Array2D.h"
#include "Cell.h"

class Board
{
	public:
		Board();
		Board( int rows, int cols, int bombs );
		Board( const Board & copy );
		Board & operator=( const Board & rhs );
		void SetRows( int rows );
		void SetCols( int cols );
		void SetBombs( int bombs );
		int  GetRows() const;
		int  GetCols();
		void SetNumber( int r, int c );
		void PlaceBombs();
		int  DisplayBoard();
		bool ProcessCells( const char r, const char c, char action );
		int  ConvertCoords( char x );
		void CascadeCells( int row, int col );
		void UncoverAllCells();
		bool IsLoss( Cell cell );
		~Board();

	private:
		Array2D <Cell> m_cells;
		int m_bombs;
};

#endif