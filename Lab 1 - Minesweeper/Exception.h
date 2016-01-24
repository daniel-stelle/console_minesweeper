/************************************************************************
* CLASS: Exception
*
* CONSTRUCTORS:	
*	Exception()
		Default constructor for Exception. Sets msg to nullptr
	Exception( char * msg )
		Sets msg to the message that was passed in.
	Exception( const Exception & copy )
		Copy constructor for Exception.
*
* FRIENDS:
*	ostream & operator<<( ostream & stream, const Exception & except )
		Overloades the output operator so that the Exceptions object can
		just be "cout'ed".
*
* METHODS:
*	Exception & operator=( const Exception & rhs )
		Overloads the assignment operator so that two Exception objects can
*		be assigned to each other.
	char * getMessage() const
		Gets what the message is that was sent into this Exception instance.
	void setMessage( char * msg )
		Sets what the message of this Exception instance is.
	~Exception()
		Deallocates the memory given to Exception's message string.
*************************************************************************/
#ifndef  EXCEPTION_H
#define  EXCEPTION_H
#include <iostream>

using std::ostream;

class Exception
{
		friend ostream & operator<<( ostream & stream, const Exception & except );

	public:
		Exception();
		Exception( char * msg );
		Exception( const Exception & copy );
		Exception & operator=( const Exception & rhs );
		char * getMessage() const;
		void setMessage( char * msg );
		~Exception();

	private:
		char * m_msg;
};

#endif