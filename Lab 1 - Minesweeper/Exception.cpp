#define  _CRT_SECURE_NO_WARNINGS
#include "Exception.h"
#include <iostream>

using std::cout;
using std::endl;

/***************************************************************
*   Purpose: Overloades the output operator so that the Exceptions
*			 object can just be "cout'ed".
*            
*     Entry: The output stream by reference and the message to be
*			 displayed.
*            
*      Exit: Returns the output stream by reference.
****************************************************************/
ostream & operator<<( ostream & stream, const Exception & except )
{
	stream << except.getMessage();

	return stream;
}

/***************************************************************
*   Purpose: Default constructor for Exception. Sets msg to nullptr
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Exception::Exception() : m_msg( nullptr )
{ }

/***************************************************************
*   Purpose: Sets msg to the message that was passed in.
*            
*     Entry: The exception message.
*            
*      Exit: None
****************************************************************/
Exception::Exception( char * msg ) : m_msg( nullptr )
{
	setMessage( msg );
}

/***************************************************************
*   Purpose: Copy constructor for Exception.
*            
*     Entry: The Exception object to be copied.
*            
*      Exit: None
****************************************************************/
Exception::Exception( const Exception & copy )
{
	m_msg = new char [strlen( copy.getMessage() ) + 1];
	strcpy( m_msg, copy.getMessage() );
}

/***************************************************************
*   Purpose: Overloads the assignment operator so that two
*			 Exception objects can be assigned to each other.
*            
*     Entry: The right hand side of the assignment operator.
*            
*      Exit: Returns the new object by reference.
****************************************************************/
Exception & Exception::operator=( const Exception & rhs )
{
	if( m_msg != nullptr )
	{
		delete [] m_msg;
		setMessage( rhs.getMessage() );
	}
	else
		setMessage( rhs.getMessage() );

	return *this;
}

/***************************************************************
*   Purpose: Gets what the message is that was sent into this
*			 Exception instance.
*            
*     Entry: None
*            
*      Exit: Returns the message in this Exception object.
****************************************************************/
char * Exception::getMessage() const
{
	return m_msg;
}

/***************************************************************
*   Purpose: Sets what the message of this Exception instance is.
*            
*     Entry: The message to set msg to.
*            
*      Exit: None
****************************************************************/
void Exception::setMessage( char * msg )
{
	m_msg = new char [strlen( msg ) + 1];
	strcpy( m_msg, msg );
}

/***************************************************************
*   Purpose: Deallocates the memory given to Exception's message
*			 string.
*            
*     Entry: None
*            
*      Exit: None
****************************************************************/
Exception::~Exception()
{
	delete [] m_msg;
}