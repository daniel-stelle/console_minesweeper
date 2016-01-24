/************************************************************************
* CLASS: Row
*
* CONSTRUCTORS:	
*	Row()
*		Default constructor for Row. Defaults are 0.
*	Row( const Array2D<T>& ra, int row )
*		Initializes m_array2D to the passed in array and initializes m_row
*		to the row that was passed in.
*
* METHODS:
*	const T & operator[]( int column ) const
*		Overloads the columns subscript operator so that we can manage
*		CONSTANT objects and their exceptions ourselves.
*	T & operator[]( int column )
*		Overloads the columns subscript operator so that we can manage it
*		and its exceptions ourselves.
*	~Row()
*		Purpose: Destructs the class.
*************************************************************************/
#ifndef  ROW_H
#define  ROW_H
#include "Array2D.h"

template<typename T>
class Array2D;

template<class T>
class Row
{
	public:
		Row();
		Row( const Array2D<T>& ra, int row );
		const T & operator[]( int column ) const;
		T & operator[]( int column );
		~Row();

	private:
		const Array2D<T>& m_array2D;
		int	m_row;
};

/***************************************************************
*   Purpose: Default constructor for Row. Defaults are 0.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Row<T>::Row() : m_array2D( 0 ), m_row( 0 )
{ }

/***************************************************************
*   Purpose: Initializes m_array2D to the passed in array and
*			 initializes m_row to the row that was passed in.
*            
*     Entry: An Array2D object by reference and the rows.
*            
*      Exit: None
****************************************************************/
template<class T>
Row<T>::Row( const Array2D<T> & ra, int row ) : m_array2D( ra ), m_row( row )
{ }

/***************************************************************
*   Purpose: Overloads the columns subscript operator so that
*			 we can manage CONSTANT objects and their exceptions
*			 ourselves.
*            
*     Entry: The index of the column to be accessed.
*            
*      Exit: Returns the data recieved from select.
****************************************************************/
template<class T>
const T & Row<T>::operator[]( int column ) const
{
	if( column < 0 || column > m_array2D.getColumn() )
	{
		throw Exception( "ERROR: Column out of bounds" );
	}

	return m_array2D.Select( m_row, column );
}

/***************************************************************
*   Purpose: Overloads the columns subscript operator so that
*			 we can manage it and its exceptions ourselves.
*            
*     Entry: The index of the column to be accessed.
*            
*      Exit: Returns the data recieved from select.
****************************************************************/
template<class T>
T & Row<T>::operator[]( int column )
{
	if( column < 0 || column > m_array2D.getColumn() )
	{
		throw Exception( "ERROR: Column out of bounds" );
	}

	return const_cast<Array2D<T> &>(m_array2D).Select( m_row, column );
}

/***************************************************************
*   Purpose: Destructs the class.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Row<T>::~Row()
{ }

#endif