#include <Windows.h>
#include <stdlib.h> // For srand()
#include <time.h>   // For time() to use as a seed for srand()
#include <iostream>
#include "Board.h"

using std::cout;
using std::endl;
using std::cin;

/***************************************************************
*   Purpose: Default constructor for Board.
*            
*     Entry: Initializes m_cells to 0 rows and 0 columns, and
*			 m_bombs to 0;
*            
*      Exit: None
****************************************************************/
Board::Board() : m_cells( 0, 0 ), m_bombs( 0 )
{ }

/***************************************************************
*   Purpose: This constructor takes 3 arguments and sets up a
*			 Board using those arguments.
*            
*     Entry: Initializes m_cells to the rows passed in and the
*			 columns that are passed in, and m_bombs to the number
*			 passed in.
*            
*      Exit: None
****************************************************************/
Board::Board( int rows, int cols, int bombs ) : m_cells( rows, cols ), m_bombs( bombs )
{ }

/***************************************************************
*   Purpose: Copy constructor for Board.
****************************************************************/
Board::Board( const Board & copy ) : m_cells( copy.m_cells ),
									 m_bombs( copy.m_bombs )
{ }

/***************************************************************
*   Purpose: Overloads the assignment operator so that two Board 
*			 objects can be assigned to each other.
****************************************************************/
Board & Board::operator=( const Board & rhs )
{
	if( this != &rhs )
	{
		m_cells = rhs.m_cells;
		m_bombs = rhs.m_bombs;
	}

	return *this;
}

/***************************************************************
*   Purpose: This method sets the total number of rows on the Board.
****************************************************************/
void Board::SetRows( int rows )
{
	m_cells.setRow( rows );
}

/***************************************************************
*   Purpose: This method sets the total number of columns on the Board.
****************************************************************/
void Board::SetCols( int cols )
{
	m_cells.setColumn( cols );
}

/***************************************************************
*   Purpose: This method sets the total number of bombs that will be placed
*			 on the Board.
****************************************************************/
void Board::SetBombs( int bombs )
{
	m_bombs = bombs;
}

/***************************************************************
*   Purpose: This method returns the total number of rows that the Board
*			 currently has.
****************************************************************/
int Board::GetRows() const
{
	return m_cells.getRow();
}

/***************************************************************
*   Purpose: This method returns the total number of columns that the Board
*			 currently has.
****************************************************************/
int Board::GetCols()
{
	return m_cells.getColumn();
}

/***************************************************************
*   Purpose: Increases the bomb count for the cells surrounding
*			 this bomb.
*            
*     Entry: The row and column of the bomb.
*            
*      Exit: All cells surrounding the bomb will have their bomb
*			 count increased by one.
****************************************************************/
void Board::SetNumber( int r, int c )
{
	try
	{
		//right
		if( c < ( m_cells.getColumn() - 1 ) &&
			m_cells[r][c + 1].IsBomb() == false )
		{
			m_cells[r][c + 1].SetNumBombs(m_cells[r][c + 1].GetNumBombs() + 1);
		}

		//top right
		if( r > 0 && c < ( m_cells.getColumn() - 1 ) &&
			m_cells[r - 1][c + 1].IsBomb() == false )
		{
			m_cells[r-1][c+1].SetNumBombs(m_cells[r-1][c+1].GetNumBombs() + 1);
		}

		//top middle
		if( r > 0 && m_cells[r - 1][c].IsBomb() == false )
			m_cells[r - 1][c].SetNumBombs(m_cells[r - 1][c].GetNumBombs() + 1);

		//top left
		if( r > 0 && c > 0 && m_cells[r - 1][c - 1].IsBomb() == false )
			m_cells[r-1][c-1].SetNumBombs(m_cells[r-1][c-1].GetNumBombs() + 1);

		//left
		if( c > 0 && m_cells[r][c - 1].IsBomb() == false )
			m_cells[r][c - 1].SetNumBombs(m_cells[r][c - 1].GetNumBombs() + 1);

		//bottom left
		if(r < ( m_cells.getRow() - 1 ) && c > 0 &&
		   m_cells[r + 1][c - 1].IsBomb() == false )
		{
			m_cells[r+1][c-1].SetNumBombs(m_cells[r+1][c-1].GetNumBombs() + 1);
		}

		//bottom middle
		if( r < ( m_cells.getRow() - 1 ) &&
			m_cells[r + 1][c].IsBomb() == false )
		{
			m_cells[r + 1][c].SetNumBombs(m_cells[r + 1][c].GetNumBombs() + 1);
		}

		//bottom right
		if( r < ( m_cells.getRow() - 1 ) && c < ( m_cells.getColumn() - 1 ) &&
			m_cells[r + 1][c + 1].IsBomb() == false )
		{
			m_cells[r+1][c+1].SetNumBombs(m_cells[r+1][c+1].GetNumBombs() + 1);
		}
	}
	catch( Exception Error )
	{
		cout << Error << endl;
	}
}

/***************************************************************
*   Purpose: This method will disperse the correct amount of bombs around
*			 the board depending on the difficulty.
*            
*     Entry: No bombs are on the board.
*            
*      Exit: Bombs will have been randomly dispersed across the board.
****************************************************************/
void Board::PlaceBombs()
{
	srand( (int)time( NULL ) );

	int rand_num_r = 0;
	int rand_num_c = 0;
	int num = 0;

	try
	{
		for( int i = 0; i < m_bombs; ++i )
		{
			rand_num_r = rand() % m_cells.getRow();
			rand_num_c = rand() % m_cells.getColumn();

			if( m_cells[rand_num_r][rand_num_c].IsBomb() == false )
			{
				m_cells[rand_num_r][rand_num_c].SetBomb();
				SetNumber( rand_num_r, rand_num_c );
			}
			else
				i--;
		}
	}
	catch( Exception Error )
	{
		cout << Error << endl;
	}
}

/***************************************************************
*   Purpose: This method will display the current Board according to flags
*			 that are set in the Cell objects.
*            
*     Entry: None.
*            
*      Exit: Board is displayed to the console.
****************************************************************/
int Board::DisplayBoard()
{
	system( "cls" );

	HANDLE handle = 0;
	const int DEFAULT = 7;
	const int LIGHT_BLUE = 3;
	int  num_covered = 0;

	handle = GetStdHandle( STD_OUTPUT_HANDLE );

	cout << "   ";

	for (int i = 0; i < m_cells.getColumn(); i++)
	{
		if( ( 65 + i ) < 91 )
		{
			SetConsoleTextAttribute( handle, LIGHT_BLUE );
			cout << static_cast<char>( 65 + i ) << ' ';
			SetConsoleTextAttribute( handle, DEFAULT );
		}
		else
		{
			SetConsoleTextAttribute( handle, LIGHT_BLUE );
			cout << ( i - 25 ) << ' ';
			SetConsoleTextAttribute( handle, DEFAULT );
		}
	}

	cout << endl;

	for (int r = 0; r < m_cells.getRow(); r++)
	{
		SetConsoleTextAttribute( handle, LIGHT_BLUE );
		cout << '\n' << static_cast<char>( 65 + r ) << "  ";
		SetConsoleTextAttribute( handle, DEFAULT );

		for( int c = 0; c < m_cells.getColumn(); c++ )
		{
			if( m_cells[r][c].Display() )
				num_covered++;
		}
	}

	cout << "\n\nNumber still covered: " << num_covered << endl;

	return num_covered;
}

/***************************************************************
*   Purpose: This method processes the users input as to which Cell they want
*			 to modify (uncover or toggle flag) and sets the Cell's flags
*			 accordingly.
*            
*     Entry: User's row and column information, as well as the
*			 action they would like to take with that cell.
*            
*      Exit: Cell is uncovered or flagged.
****************************************************************/
bool Board::ProcessCells( const char r, const char c, char action )
{
	int row = 0;
	int col = 0;

	row = ConvertCoords( toupper( r ) );
	col = ConvertCoords( toupper( c ) );

	try
	{
		if( toupper( action ) == 'U' )
			CascadeCells( row, col );
		else
		{
			if( m_cells[row][col].IsFlagged() )
				m_cells[row][col].SetFlag( 'F' );
			else
				m_cells[row][col].SetFlag( 'T' );
		}
	}
	catch( Exception Error )
	{
		cout << Error << endl;
	}

	if( IsLoss( m_cells[row][col] ) )
		UncoverAllCells();

	return IsLoss( m_cells[row][col] );
}

/***************************************************************
*   Purpose: This method converts the coordinate that is passed in from a char
*			 to an int.
*            
*     Entry: Character.
*            
*      Exit: Integer.
****************************************************************/
int Board::ConvertCoords( char x )
{
	int num = 0;

	if( isalpha( x ) )
		num = static_cast<int>( x ) - 65;
	else
		num = static_cast<int>( x ) - 23;

	return num;
}

/***************************************************************
*   Purpose: This method reveals all blank Cells around the selected cell if
*			 the selected Cell is blank.
*            
*     Entry: Cells are covered.
*            
*      Exit: All adjacent blank cells are uncovered.
****************************************************************/
void Board::CascadeCells( int row, int col )
{
	if( m_cells[row][col].IsCovered() )
	{
		if( m_cells[row][col].GetNumBombs() > 0 )
			m_cells[row][col].Uncover();
		else if( m_cells[row][col].GetNumBombs() == 0 )
		{
			m_cells[row][col].Uncover();

			if( row > 0 ) // top middle
				CascadeCells( row - 1, col );
		
			if( row > 0 && col < ( m_cells.getColumn() - 1 ) ) // top right
				CascadeCells( row - 1, col + 1 );

			if( col < ( m_cells.getColumn() ) - 1 ) // right
				CascadeCells( row, col + 1 );

			if( row < ( m_cells.getRow() - 1 ) && col < ( m_cells.getColumn() - 1 ) ) // bottom right
				CascadeCells( row + 1, col + 1 );

			if( row < ( m_cells.getRow() - 1 ) ) // bottom middle
				CascadeCells( row + 1, col );

			if( row < ( m_cells.getRow() - 1 ) && col > 0 ) // bottom left
				CascadeCells( row + 1, col - 1 );

			if( col > 0 ) // left
				CascadeCells( row, col - 1 );

			if( col > 0 && row > 0 ) // top left
				CascadeCells( row - 1, col - 1 );
		}
	}
}

/***************************************************************
*   Purpose: Uncovers every cell on the board, reguardless of
*			 cell status.
*
*     Entry: Cells are covered.
*
*      Exit: All cells are uncovered.
****************************************************************/
void Board::UncoverAllCells()
{
	for (int i = 0; i < m_cells.getRow(); i++)
	{
		for (int j = 0; j < m_cells.getColumn(); j++)
		{
			m_cells[i][j].Uncover();
		}
	}
}

/***************************************************************
*   Purpose: This method detects whether the Cell that is passed in is a bomb.
*            
*     Entry: The cell in question.
*            
*      Exit: True or false depending on if the cell is a bomb or not.
****************************************************************/
bool Board::IsLoss( Cell cell )
{
	bool lose = false;

	if( cell.IsBomb() && cell.IsCovered() == false )
		lose = true;
		
	return lose;
}

/***************************************************************
*   Purpose: Destructor.
****************************************************************/
Board::~Board()
{
	
}