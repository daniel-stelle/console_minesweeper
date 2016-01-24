#include <Windows.h>
#include <iostream>
#include "Cell.h"

using std::cout;

/***************************************************************
*   Purpose: Default constructor for Cell.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Cell::Cell() : m_covered( true ), m_bomb( false ), m_num_bombs( 0 ),
			   m_flag( false )
{ }

/***************************************************************
*   Purpose: Copy constructor for Cell
*            
*     Entry: The Cell to be copied to this new instance.
*            
*      Exit: None
****************************************************************/
Cell::Cell( const Cell & copy ) : m_covered( copy.m_covered ),
								  m_bomb( copy.m_bomb ), m_flag( copy.m_flag ),
								  m_num_bombs( copy.m_num_bombs )
{ }

/***************************************************************
*   Purpose: Overloads the assignment operator so that two Cell
*			 objects can be assigned to each other.
*            
*     Entry: The right hand side of the assignment operator.
*            
*      Exit: Returns a reference to the new Cell.
****************************************************************/
Cell & Cell::operator=( const Cell & rhs )
{
	m_covered = rhs.m_covered;
	m_bomb = rhs.m_bomb;
	m_flag = rhs.m_flag;
	m_num_bombs = rhs.m_num_bombs;

	return *this;
}

/***************************************************************
*   Purpose: This method sets whether the Cell has been flagged
*			 or not.
*            
*     Entry: A character representing what to set m_flag to.
*            
*      Exit: None
****************************************************************/
void Cell::SetFlag( char flag )
{
	if( flag == 'T' )
		m_flag = true;
	else
		m_flag = false;
}

/***************************************************************
*   Purpose: This method makes the Cell a bomb Cell.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
void Cell::SetBomb()
{
	m_bomb = true;
}

/***************************************************************
*   Purpose: This method sets the number of bombs that are
*			 adjacent to this Cell according to the number that
*			 is passed in.
*            
*     Entry: The number of bombs that are adjacent to this Cell.
*            
*      Exit: None
****************************************************************/
void Cell::SetNumBombs( int num )
{
	m_num_bombs = num;
}

/***************************************************************
*   Purpose: This method returns the number of bombs that are
*			 adjacent to this Cell.
*            
*     Entry: None
*            
*      Exit: The number of bombs adjacent to this Cell.
****************************************************************/
int Cell::GetNumBombs() const
{
	return m_num_bombs;
}

/***************************************************************
*   Purpose: This method uncovers the Cell.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
void Cell::Uncover()
{
	m_covered = false;
}

/***************************************************************
*   Purpose: This method returns true or false as to whether it
*			 is a bomb Cell or not.
*            
*     Entry: None
*            
*      Exit: Returns true if this Cell is a bomb and false if not.
****************************************************************/
bool Cell::IsBomb()
{
	bool is_bomb = false;

	if( m_bomb == true )
		is_bomb = true;

	return is_bomb;
}

/***************************************************************
*   Purpose: This method returns true or false as to whether it
*			 is a flagged Cell or not.
*            
*     Entry: None
*            
*      Exit: Returns true if this Cell is a bomb and false if not.
****************************************************************/
bool Cell::IsFlagged()
{
	bool is_flagged = false;

	if( m_flag == true )
		is_flagged = true;

	return is_flagged;
}

/***************************************************************
*   Purpose: This method returns true or false as to whether it
*			 is covered or not.
*            
*     Entry: None
*            
*      Exit: Returns true if this Cell is covered and false if not.
****************************************************************/
bool Cell::IsCovered()
{
	bool is_covered = false;

	if( m_covered == true )
		is_covered = true;

	return is_covered;
}

/***************************************************************
*   Purpose: This method displays the correct character depending
*			 on what flags are currently set on.
*            
*     Entry: None
*            
*      Exit: Returns true if the Cell is still technically coverd
*			 and false if not (Flagged is still covered).
****************************************************************/
bool Cell::Display()
{
	HANDLE handle = 0;
	const int DEFAULT = 7;
	const int YELLOW = 14;
	const int GREEN = 10;
	const int RED = 12;
	const int BLUE = 9;
	bool empty = false;

	handle = GetStdHandle( STD_OUTPUT_HANDLE );

	if( m_covered == false )
	{
		if( m_bomb == true )
		{
			SetConsoleTextAttribute( handle, RED );
			cout << "X ";
			SetConsoleTextAttribute( handle, DEFAULT );
		}
		else if( m_num_bombs > 0 )
		{
			SetConsoleTextAttribute( handle, GREEN );
			cout << m_num_bombs << ' ';
			SetConsoleTextAttribute( handle, DEFAULT );
		}
		else
		{
			SetConsoleTextAttribute( handle, BLUE );
			cout << ". ";
			SetConsoleTextAttribute( handle, DEFAULT );
		}
	}
	else if( m_flag == true )
	{
		SetConsoleTextAttribute( handle, YELLOW );
		cout << "F ";
		SetConsoleTextAttribute( handle, DEFAULT );
		empty = true;
	}
	else
	{
		cout << "? ";
		empty = true;
	}

	return empty;
}

/***************************************************************
*   Purpose: This method destructs the class.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Cell::~Cell()
{ }