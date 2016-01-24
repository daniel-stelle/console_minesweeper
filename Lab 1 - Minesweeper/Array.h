/************************************************************************
* CLASS: Array
*
* CONSTRUCTORS:	
*	Array()
*		Default constructor for Array. Defaults are 0.
*	Array( int length, int start_index = 0 )
*		Initializes the length and the start index to the ones passed in.
*		Also allocates memory for the array itself.
*	Array( const Array & copy )
*		Copy constructor for Array.
*
* METHODS:
*	Array<T> & operator=( const Array & rhs )
*		Overloads the assignment operator so that two Array objects can
*		be assigned to each other.
*	T &  operator[]( int index )
*		Overloads the subscript operator so that we can manage this
*		object and its exceptions ourselves.
*	const T &  operator[]( int index ) const
*		Overloads the subscript operator so that we can manage CONSTANT
*		objects and their exceptions ourselves.
*	int  getStartIndex() const
*		Gets what the starting index is for the array.
*	void setStartIndex( int start_index )
*		Sets the starting index to something new.
*	int  getLength() const
*		Gets the length of this array.
*	void setLength( int length )
*		Sets the length of the array to something new.
*	~Array()
*		Deallocates the memory given to m_array and sets the length and
*		the starting index to 0.
*************************************************************************/
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include "Exception.h"

using std::cout;
using std::endl;

template<class T>
class Array
{
	public:
		Array();
		Array( int length, int start_index = 0 );
		Array( const Array & copy );
		Array<T> & operator=( const Array & rhs );
		T &  operator[]( int index );
		const T &  operator[]( int index ) const;
		int  getStartIndex() const;
		void setStartIndex( int start_index );
		int  getLength() const;
		void setLength( int length );
		~Array();

	private:
		T * m_array;
		int m_length;
		int m_start_index;
};

/***************************************************************
*   Purpose: Default constructor for Array. Defaults are 0.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Array<T>::Array() : m_array( nullptr ), m_length( 0 ), m_start_index( 0 )
{ }

/***************************************************************
*   Purpose: Initializes the length and the start index to the
*			 ones passed in. Also allocates memory for the array
*			 itself.
*            
*     Entry: The length and the start index.
*            
*      Exit: None
****************************************************************/
template<class T>
Array<T>::Array( int length, int start_index ) : m_array( nullptr ), m_length( length ), m_start_index( start_index )
{
	m_array = new T [m_length];
}

/***************************************************************
*   Purpose: Copy constructor for Array.
*            
*     Entry: The array object to be copied.
*            
*      Exit: None
****************************************************************/
template<class T>
Array<T>::Array( const Array & copy ) : m_array( nullptr ),
										m_length( copy.m_length ),
										m_start_index( copy.m_start_index )
{
	m_array = new T [copy.m_length];

	for( int i = 0; i < ( m_length + m_start_index ); ++i )
		m_array[i] = copy.m_array[i];
}

/***************************************************************
*   Purpose: Overloads the assignment operator so that two Array
*			 objects can be assigned to each other.
*            
*     Entry: The right hand side of the assignment operator by
*			 reference.
*            
*      Exit: Returns the new object by reference.
****************************************************************/
template<class T>
Array<T> & Array<T>::operator=( const Array & rhs )
{
	if( this != &rhs )
	{
		delete [] m_array;
		m_array = new T [rhs.m_length];

		for( int i = 0; i < rhs.m_length; ++i )
			m_array[i] = rhs.m_array[i];

		m_length = rhs.m_length;
		m_start_index = rhs.m_start_index;
	}

	return *this;
}

/***************************************************************
*   Purpose: Overloads the subscript operator so that we can
*			 manage this object and its exceptions ourselves.
*            
*     Entry: The index in the array to be accessed.
*            
*      Exit: Returns the data from the indexed element of the
*			 array, accounting for the start index.
****************************************************************/
template<class T>
T & Array<T>::operator[]( int index )
{
	if( index < m_start_index || index >= ( m_start_index + m_length ) )
		throw Exception( "ERROR: Index is out of bounds" );

	return m_array[index - m_start_index];
}

/***************************************************************
*   Purpose: Overloads the subscript operator so that we can
*			 manage CONSTANT objects and their exceptions ourselves.
*            
*     Entry: The index in the array to be accessed.
*            
*      Exit: Returns the data from the indexed element of the
*			 array, accounting for the start index.
****************************************************************/
template<class T>
const T & Array<T>::operator[]( int index ) const
{
	if( index < m_start_index || index >= ( m_start_index + m_length ) )
		throw Exception( "ERROR: Index is out of bounds" );
		
	return m_array[index - m_start_index];
}

/***************************************************************
*   Purpose: Gets what the starting index is for the array.
*            
*     Entry: None
*            
*      Exit: Returns the starting index.
****************************************************************/
template<class T>
int Array<T>::getStartIndex() const
{
	return m_start_index;
}

/***************************************************************
*   Purpose: Sets the starting index to something new.
*            
*     Entry: The new starting index.
*            
*      Exit: None
****************************************************************/
template<class T>
void Array<T>::setStartIndex( int start_index )
{
	m_start_index = start_index;
}

/***************************************************************
*   Purpose: Gets the length of this array.
*            
*     Entry: None
*            
*      Exit: Returns the lenght of the array.
****************************************************************/
template<class T>
int Array<T>::getLength() const
{
	return m_length;
}

/***************************************************************
*   Purpose: Sets the length of the array to something new.
*            
*     Entry: The new length of the array.
*            
*      Exit: None
****************************************************************/
template<class T>
void Array<T>::setLength( int length )
{
	T * temp;

	if( m_length == 0 )
	{
		temp = new T [length];
		m_length = length;

		delete [] m_array;

		m_array = temp;
	}
	else if( m_length < length )
	{
		temp = new T [m_length + ( length - m_length )];

		for( int i = 0; i < length; ++i )
		{
			temp[i] = m_array[i];
		}

		m_length = length;

		delete [] m_array;
		
		m_array = temp;
	}
	else if( m_length > length && length >= 0 )
	{
		temp = new T [m_length - ( m_length - length )];

		for( int i = 0; i < length; ++i )
			temp[i] = m_array[i];

		m_length = length;

		delete [] m_array;

		m_array = temp;
	}
	else if( length < 0 )
		throw Exception( "ERROR: Cannot make an array with a negative length" );
	else
		cout << "The array is already " << length << " elements big." << endl;
}

/***************************************************************
*   Purpose: Deallocates the memory given to m_array and sets
*			 the length and the starting index to 0.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
template<class T>
Array<T>::~Array()
{
	delete [] m_array;
	m_length = 0;
	m_start_index = 0;
}

#endif