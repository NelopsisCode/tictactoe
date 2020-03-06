#ifndef _MORPION
#define _MORPION

#include <iostream>

using namespace std;

const int TAILLE = 3;
const char HUMAN = 'X';
const char AI = 'O';


struct Move 
{
	unsigned int x = 1;
	unsigned int y = 1;
		
};



class Morpion
{

public:

//Game
	Morpion();

	char * getBoard();

	void printBoard()const;

	void setCase(const unsigned int & x, const unsigned int & y, const char & player,bool & isset);

	bool tie()const;

	bool win(const char & player)const;

	bool gameOver(const char & player)const;

//AI
	Move minimax(char AIboard[3][3])const;

	int maxSearch(char AIboard[3][3])const;

	int minSearch(char AIboard[3][3])const;

//Game loop
	void play();

private:
	
	char board[TAILLE][TAILLE];

};


#endif