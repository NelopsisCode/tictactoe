#include <iostream>
#include "morpion.h"

using namespace std;



Morpion::Morpion()
{
	for (unsigned int i=0; i<3 ;i++)
	{
		for(unsigned int j=0; j<3 ;j++)
		{
			board[i][j]='_';
		}
	}

}


void Morpion::printBoard()const
{

	for (unsigned int i=0; i<3 ;i++)
	{
		for(unsigned int j=0; j<3 ;j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}


//isset = true si le pion est placé, false sinon
void Morpion::setCase(const unsigned int & x, 
	const unsigned int & y, 
	const char & player, 
	bool & isset)
{
	//1er cas: les coordonnées sont bonnes
	
	if ((x>=1) && (x<=3) && (y>=1) && (y<=3) && (board[x-1][y-1]=='_'))
	{
		board[x-1][y-1] = player;
		isset = true;
	}

	//2eme cas: les coordonnées ne sont pas bonne, on indique l'erreur.
	else
	{
		if ((x<1) || (x>3) || (y<1) || (y>3))
		{
			cout<<"Votre pion est hors du jeu... Recommencez"<<endl;
			isset = false;
		}
		else if ((board[x-1][y-1]=='X') || (board[x-1][y-1]=='O'))
		{
			cout<<"Un pion se trouve deja sur cette case... Recommencez"<<endl;
			isset = false;
		}
	}

}


bool Morpion::tie()const
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (board[i][0] == '_' || board[i][1] == '_' || board[i][2] == '_')
			return false;
	}
	return true;
}


bool Morpion::win(const char & player)const
{
	if (//Horizontal
		(board[0][0]==player && board[0][1]==player && board[0][2]==player) ||
		(board[1][0]==player && board[1][1]==player && board[1][2]==player) ||
		(board[2][0]==player && board[2][1]==player && board[2][2]==player) ||
        //vertical
		(board[0][0]==player && board[1][0]==player && board[2][0]==player) ||
		(board[0][1]==player && board[1][1]==player && board[2][1]==player) ||
		(board[0][2]==player && board[1][2]==player && board[2][2]==player) ||
        //diagonal
		(board[0][0]==player && board[1][1]==player && board[2][2]==player) ||
		(board[0][2]==player && board[1][1]==player && board[2][0]==player))
	{
		return(true);
	}
	else
	{
		return (false);
	}

}


bool Morpion::gameOver(const char & player)const
{

	if (tie())
	{ 
		cout << "It's a tie" <<endl;
		return true;
	}

	if (win(AI))
	{
		cout << "Computer won" <<endl;
		return true;
	}
	if (win (HUMAN))
	{
		cout << "You won" <<endl;
		return true;
	}

	return false;

}


Move Morpion::minimax(char AIboard[3][3]) const
{

	int bestMoveValue = 100;
	Move bestMove;

	for(unsigned int i = 0; i < 3; i++) 
	{
		for(unsigned int j = 0; j < 3; j++) 
		{
			//Pour chaque case vide, on recupère la valeur du move et on le compare à la meilleure valeur
			if(AIboard[i][j] == '_') 
			{
				AIboard[i][j] = AI;
				int tempMoveValue = maxSearch(AIboard);
				//cout << "value = " << tempMoveValue <<endl;
				if(tempMoveValue <= bestMoveValue) 
				{
					bestMoveValue = tempMoveValue;
					bestMove.x = i+ 1;
					bestMove.y = j+ 1;
				}
				AIboard[i][j] = '_';
			}
		}
	}

	return bestMove;

}


int Morpion::maxSearch(char AIboard[3][3])const
{
	Move bestMove;

	if (win(HUMAN)) { return 10; }
	else if (win(AI)) { return -10; }
	else if (tie()) { return 0; }

	int bestMoveValue = -10000;
	for(unsigned int i = 0; i < 3; i++)
	{
		for(unsigned int j= 0; j < 3; j++)
		{
			if (AIboard[i][j] == '_')
			{
				AIboard[i][j] = HUMAN;
				int tempMoveValue = minSearch(AIboard);
				//cout << "min = " << tempMoveValue <<endl;
				if(tempMoveValue >= bestMoveValue)
				{
					bestMoveValue = tempMoveValue;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '_';
			}

		}
	}
	return bestMoveValue;
}


int Morpion::minSearch(char AIboard[3][3])const 
{
	Move bestMove;

	if (win(HUMAN)) 
	{ 
		return 10; 
	}
	else if (win(AI)) 
	{ 
		return -10; 
	}
	else if (tie()) 
	{ 
		return 0; 
	}


	int bestMoveValue = 10000000; 
	for(unsigned int i = 0; i < 3; i++) 
	{
		for(unsigned int j = 0; j < 3; j++) 
		{
			if(AIboard[i][j] == '_') 
			{
				AIboard[i][j] = AI;
				int tempMove = maxSearch(AIboard);
				//cout << "max = " << bestMoveValue <<endl;
				if(tempMove <= bestMoveValue) 
				{
					bestMoveValue = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '_';
			}
		}
	}

	return bestMoveValue;
}



void Morpion::play()
{
	int tour;

	bool fin;

	tour = 0;
	fin = false;


	printBoard();


	while (fin == false)
	{
        //On regarde qui est le player en fonction du tour
        if (tour % 2 == 0) //humain
        {
        	unsigned int x,y;
        	bool isset;
        	do{
        		cout << "Ligne: " ;
        		cin >> x;
        		cout << "Colonne: " ;
        		cin >> y;
        		setCase(x,y, HUMAN, isset);
        	}while (isset == false);    

        	fin = gameOver(HUMAN);
        }

        else // IA
        {
        	bool isset;
        	Move AImove = minimax(board);
        	//cout << AImove.x <<endl << AImove.y <<endl;
        	setCase(AImove.x,AImove.y, AI ,isset);
        	fin = gameOver(AI);
        }
        

        printBoard();
        tour ++;
    }


}
