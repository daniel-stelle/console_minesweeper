/************************************************************************
* CLASS: Cell
*
* CONSTRUCTORS:	
*	Cell()
*		Default constructor for Cell.
*	Cell( const Cell & copy )
*		Copy constructor for Cell.
*
* METHODS:
*	Cell & operator=( const Cell & rhs )
*		Overloads the assignment operator so that two Cell objects can be
*		assigned to each other.
*	void SetFlag( char flag )
*		This method sets whether the Cell has been flagged or not.
*	void SetCover()
*		This method uncovers the Cell.
*	void SetBomb()
*		This method makes the Cell a bomb Cell.
*	void SetNumBombs( int num )
*		This method sets the number of bombs that are adjacent to this Cell
*		according to the number that is passed in.
*	int GetNumBombs() const
*		This method returns the number of bombs that are adjacent to this
*		Cell.
*	bool IsBomb()
*		This method returns true or false as to whether it is a bomb Cell
*		or not.
*	bool IsFlagged()
*		This method returns true or false as to whether it is a flagged
*		Cell or not.
*	bool IsCovered()
*		This method returns true or false as to whether it is covered or
*		not.
*	void Display()
*		This method displays the correct character depending on what flags
*		are currently set on.
*	~Cell()
*		This method destructs the class.
*************************************************************************/
#ifndef CELL_H
#define CELL_H

class Cell
{
	public:
		Cell();
		Cell( const Cell & copy );
		Cell & operator=( const Cell & rhs );
		void SetFlag( char flag );
		void SetBomb();
		void SetNumBombs( int num );
		int  GetNumBombs() const;
		void Uncover();
		bool IsBomb();
		bool IsFlagged();
		bool IsCovered();
		bool Display();
		~Cell();

	private:
		bool m_covered;
		bool m_bomb;
		bool m_flag;
		int  m_num_bombs;
};

#endif