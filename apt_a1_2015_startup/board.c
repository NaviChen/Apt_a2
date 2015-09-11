/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Yehui Chen
* Student Number   : s3189978
* Course Code      : COSC1076
* Program Code     : BP232
* Start up code provided by Paul Miller
***********************************************************************/
#include "board.h"
#include "player.h"

void initialise_board(enum cell_contents board[][BOARDWIDTH])
{
	int i, j;

	for(i = 0;i < BOARDHEIGHT;i++)
	{
		for(j = 0; j < BOARDWIDTH; j++)
		{
			board[i][j] = C_EMPTY;
		}
	}

}

void display_board(enum cell_contents board[][BOARDWIDTH])
{
	int i, j, l;
	int h;

/* Display and Format Index */
	for(h = 0; h < BOARDWIDTH; h++)
	{
		printf("%-4s","++++");
	}
	printf("\n");

	for(h = 0; h < BOARDWIDTH; h++)
	{
		printf(" %d |", h+1);
	}
	printf("\n");


	for(h = 0; h < BOARDWIDTH; h++)
	{
		printf("%-3s ","---");
	}
	printf("\n");



/* Display Board */
	for(i = 0; i < BOARDHEIGHT; i++)
	{
		
		for(j = 0; j < BOARDWIDTH; j++)
		{
			
			switch(board[i][j])
			{
				case C_EMPTY: 
					printf(" %-1s |", "");
					break;

				case C_RED: 
					printf(" %-1s |", RED_TOKEN);
					break;

				case C_WHITE: 
					printf(" %-1s |", WHITE_TOKEN);
					break;
			}
		}

		printf("\n");

		for(l = 0; l < BOARDWIDTH; l++)
		{
			printf("%-3s ","---");
		}

		printf("\n");
	}

	printf("\n");
}
 

