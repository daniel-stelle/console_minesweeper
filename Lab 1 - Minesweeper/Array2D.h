/************************************************************************
* CLASS: Array2D
*
* CONSTRUCTORS:	
*	Array2D()
*		Default constructor for Array2D. Defaults are 0.
*	Array2D( int row, int col = 0 )
*		Initializes all of the data members to the rows and
*			 columns that are passed in.
*	Array2D( const Array2D & copy )
*		Copy constructor for Array2D.
*
* METHODS:
*	Array2D & operator=( const Array2D & rhs )
*		Overloads the assignment operator so that two Array2D objects can
*		be assigned to each other.
*	const Row<T> operator[]( int index ) const
*		Overloads the subscript operator so that we can manage the 
*		CONSTANT objects and their exceptions ourselves.
*	Row<T> operator[]( int index )
*		Purpose: Overloads the subscript operator so that we can manage it
*		and its exceptions ourselves.
*	int getRow() const
*		Gets the total number of rows there are.
*	void setRow( int rows )
*		Sets the total number of rows to a new amount.
*	int getColumn() const
*		Gets the total number of columns there are.
*	void setColumn( int columns )
*		Sets the total number of columns to a new amount.
*	const T & Select( int row, int column ) const
*		Gets the data from the 1D array according to the row and column that
*		is passed in. *For CONSTANT objects.
*	T & Select( int row, int column )
*		Gets the data from the 1D array according to the row and column that
*		is passed in.
*	~Array2D()
*		Sets the total columns and rows to 0.
*************************************************************************/
#ifndef  ARRAY2D_H
#define  ARRAY2D_H
#include "Array.h"
#include "Exception.h"
#include "Row.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

template<class T>
class Array2D
{
	public:
		Array2D();
		Array2D( int row, int col = 0 );
		Array2D( const Array2D & copy );
		Array2D & operator=( const Array2D & rhs );
		const Row<T> operator[]( int index ) const;
		Row<T> operator[]( int index );
		int getRow() const;
		void setRow( int rows );
		int getColumn() const;
		void setColumn( int columns );
		const T & Select( int row, int column ) const;
		T & Select( int row, int column );
		~Array2D();

	private:
		Array<T> m_array;
		int		 m_row;
		int		 m_col;
};

/***************************************************************
*   Purpose: Default constructor for Array2D. Defaults are 0.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Array2D<T>::Array2D() : m_array( 0 ), m_row( 0 ), m_col( 0 )
{ }

/***************************************************************
*   Purpose: Initializes all of the data members to the rows and
*			 columns that are passed in.
*            
*     Entry: The total number of rows and columns.
*            
*      Exit: None
****************************************************************/
template<class T>
Array2D<T>::Array2D( int row, int col = 0 ) : m_array( row * col ), m_row( row ), m_col( col )
{ }

/***************************************************************
*   Purpose: Copy constructor for Array2D.
*            
*     Entry: The Array2D object to be copied into this instance.
*            
*      Exit: None
****************************************************************/
template<class T>
Array2D<T>::Array2D( const Array2D & copy ) : m_array( copy.m_array ),
											  m_row( copy.m_row ),
											  m_col( copy.m_col )
{ }

/***************************************************************
*   Purpose: Overloads the assignment operator so that two Array2D
*			 objects can be assigned to each other.
*            
*     Entry: The right hand side of the assignment operator.
*            
*      Exit: Returns a reference to the new Array2D object.
****************************************************************/
template<class T>
Array2D<T> & Array2D<T>::operator=( const Array2D & rhs )
{
	if( this != &rhs )
	{
		m_array = rhs.m_array;
		m_col = rhs.m_col;
		m_row = rhs.m_row;
	}

	return *this;
}

/***************************************************************
*   Purpose: Overloads the subscript operator so that we can
*			 manage the CONSTANT objects and their exceptions
*			 ourselves.
*            
*     Entry: The index of the row to be accessed.
*            
*      Exit: Returns a Row object.
****************************************************************/
template<class T>
const Row<T> Array2D<T>::operator[]( int index ) const
{
	if( index < 0 || index >= m_row )
		throw Exception( "ERROR: Row out of bounds" );

	return Row<T>( *this, index );
}

/***************************************************************
*   Purpose: Overloads the subscript operator so that we can
*			 manage it and its exceptions ourselves.
*            
*     Entry: The index of the row to be accessed.
*            
*      Exit: Returns a Row object.
****************************************************************/
template<class T>
Row<T> Array2D<T>::operator[]( int index )
{
	if( index < 0 || index >= m_row )
		throw Exception( "ERROR: Row out of bounds" );

	return Row<T>( *this, index );
}

/***************************************************************
*   Purpose: Gets the total number of rows there are.
*            
*     Entry: None
*            
*      Exit: Returns the total number of rows.
****************************************************************/
template<class T>
int Array2D<T>::getRow() const
{
	return m_row;
}

/***************************************************************
*   Purpose: Sets the total number of rows to a new amount.
*            
*     Entry: The new number of rows desired.
*            
*      Exit: None
****************************************************************/
template<class T>
void Array2D<T>::setRow( int rows )
{
	if( rows < 0 )
		throw Exception( "ERROR: Cannot have negative amount of rows" );

	m_array.setLength( rows * m_col );
	m_row = rows;
}

/***************************************************************
*   Purpose: Gets the total number of columns there are.
*            
*     Entry: None
*            
*      Exit: Returns the total number of columns.
****************************************************************/
template<class T>
int Array2D<T>::getColumn() const
{
	return m_col;
}

/***************************************************************
*   Purpose: Sets the total number of columns to a new amount.
*            
*     Entry: The new number of columns desired.
*            
*      Exit: None
****************************************************************/
template<class T>
void Array2D<T>::setColumn( int columns )
{
	Array<T> temp;
	int temp_indx = 0;
	int old_indx = 0;

	if( columns < 0 )
		throw Exception( "ERROR: Cannot have negative amount of columns" );

	temp.setLength( m_row * columns );

	if( m_col < columns ) // Making columns larger
	{
		for( int i = 0; i < m_row; ++i ) // Loops for however many rows there are
		{
			for( int j = 0; j < m_col; ++j ) // Loops for however many columns per row there are in the old array
			{
				temp[temp_indx] = m_array[old_indx];
				temp_indx++;
				old_indx++;
			}

			temp_indx += ( columns - m_col );
		}

		m_array = temp;
		m_col = columns;
	}
	else if( m_col > columns ) // Making columns smaller
	{
		for( int i = 0; i < m_row; ++i ) // Loops for however many rows there are
		{
			for( int j = 0; j < columns; ++j ) // Loops for however many columns per row there are in the old array
			{
				temp[temp_indx] = m_array[old_indx];
				temp_indx++;
				old_indx++;
			}

			old_indx += ( m_col - columns );
		}

		m_array = temp;
		m_col = columns;
	}
	else
		cout << "The array already has " << columns << " columns." << endl;
}

/***************************************************************
*   Purpose: Gets the data from the 1D array according to the
*			 row and column that is passed in. *For CONSTANT
*			 objects.
*            
*     Entry: The row and column of the desired index.
*            
*      Exit: Returns data at "m_array[row][column]".
****************************************************************/
template<class T>
const T & Array2D<T>::Select( int row, int column ) const
{
	return m_array[( row * m_col ) + column];
}

/***************************************************************
*   Purpose: Gets the data from the 1D array according to the
*			 row and column that is passed in.
*            
*     Entry: The row and column of the desired index.
*            
*      Exit: Returns data at "m_array[row][column]".
****************************************************************/
template<class T>
T & Array2D<T>::Select( int row, int column )
{
	return m_array[( row * m_col ) + column];
}

/***************************************************************
*   Purpose: Sets the total columns and rows to 0.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Array2D<T>::~Array2D()
{
	m_col = 0;
	m_row = 0;
}

#endif