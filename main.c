// main.c

#pragma warning(disable:4996)

#include <stdio.h>

#define SIZE 100

// Enum declaration
typedef enum {WALL, FOOD, EMPTY} Tile;

// Struct declaration
typedef struct
{
	int nRowIndex;
	int nColIndex;
} Player;

// Function prototypes
void BoardInit(Tile imattBoard[][SIZE + 2]);
void PrintBoard(Tile imattBoard[][SIZE + 2], Player iplBulli, Player iplBear);
int BulliMove(Tile imattBoard[][SIZE + 2], Player *iplBulli,
			  int *opnFood, char *iopcLastMove);
void BearMove(Tile imattBoard[][SIZE + 2], Player iplBulli, Player *iplBear);

//---------------------------------------------------------------------------------------
//                                        Bulliman
//                                       ----------
//
// General : The program simulates a game where the player controls a character named
//			 "Bulli" and must navigate a game board to collect food while avoiding a
//			 bear. The player can input the locations of walls on the board, as well as
//			 the starting positions of Bulli and the bear. The bear will always attempt
//			 to move closer to Bulli, and the game ends when Bulli either collects all
//			 the food or is caught by the bear.
//
// Input   : Location of walls, starting position of Bulli and the bear, and Bulli's
//			 movement.
// 
// Process : Each turn, if the move is allows, Bulli's position is calculated. The bear
//			 always attempts to get closer to Bulli no matter the obsticles. When the food
//			 counter hits 0, Bulli wins. If the bear succeeds in getting to Bulli's
//			 location, Bulli loses.
//
// Output  : The board is printed each turn. Finally, the result of the game is printed.
// 
//---------------------------------------------------------------------------------------
// Programmer : Lahav Gafni
// Student No : 325761880
// Date       : 05.12.2022
//---------------------------------------------------------------------------------------
void main()
{
	// Variable definition
	Tile mattBoard[SIZE + 2][SIZE + 2];
	Player plBulli;
	Player plBear;
	int nRowIndex;
	int nColIndex;
	int nFood;
	char cLastMove;

	// Code section
	
	BoardInit(mattBoard);
	nFood = SIZE * SIZE - 1;
	// Reading all wall positions.
	printf("Enter next wall indexes or 0 0 to complete board.\n");
	scanf("%d%d", &nRowIndex, &nColIndex);
	// Reading all wall locations.
	while (nRowIndex && nColIndex)
	{
		mattBoard[nRowIndex][nColIndex] = WALL;
		nFood--;
		printf("Enter next wall indexes or 0 0 to complete board.\n");
		scanf("%d%d", &nRowIndex, &nColIndex);
	}
	printf("Enter indexes of Bulli.\n");
	scanf("%d%d", &nRowIndex, &nColIndex);
	mattBoard[nRowIndex][nColIndex] = EMPTY;
	plBulli.nRowIndex = nRowIndex;
	plBulli.nColIndex = nColIndex;
	printf("Enter indexes of bear.\n");
	scanf("%d%d", &nRowIndex, &nColIndex);
	plBear.nRowIndex = nRowIndex;
	plBear.nColIndex = nColIndex;
	PrintBoard(mattBoard, plBulli, plBear);
	cLastMove = '1';
	// The game phase
	while (1)
	{
		// Only proceeding if Bulli made their move.
		if (BulliMove(mattBoard, &plBulli, &nFood, &cLastMove))
		{
			// Checking if Bulli won.
			if (!nFood)
			{
				PrintBoard(mattBoard, plBulli, plBear);
				printf("Amazingly, Bulli finishes all the food and lives to see ");
				printf("another day.\n");
				printf("YOU WON!\n");
				break;
			}
			BearMove(mattBoard, plBulli, &plBear);
		}
		else
		{
			PrintBoard(mattBoard, plBulli, plBear);
			printf("Bulli runs into a wall.\n");
			printf("Bear stops for this turn to have a quick laugh.\n");
			continue;
		}
		PrintBoard(mattBoard, plBulli, plBear);
	}
}

//---------------------------------------------------------------------------------------
//                                     Board Initialize
//                                    ------------------
//
// General      : The procedure initializes the board. The board's limits are initialized
//				  and food is scattered in every available tile.
//
// Parameters   : 
//      imattBoard - Board (In)
//
// Return Value : None (procedure)
// 
//---------------------------------------------------------------------------------------
void BoardInit(Tile imattBoard[][SIZE + 2])
{
	// Variable definition
	int nRowIndex, nColIndex;
	
	// Code section

	// Creating board frame.
	for (nRowIndex = 0; nRowIndex < SIZE + 2; nRowIndex++)
	{
		imattBoard[nRowIndex][0] = WALL;
		imattBoard[nRowIndex][SIZE + 1] = WALL;
	}
	for (nColIndex = 1; nColIndex < SIZE + 1; nColIndex++)
	{
		imattBoard[0][nColIndex] = WALL;
		imattBoard[SIZE + 1][nColIndex] = WALL;
	}
	// Iterating through every tile in board to insert food.
	for (nRowIndex = 1; nRowIndex < SIZE + 1; nRowIndex++)
	{
		for (nColIndex = 1; nColIndex < SIZE + 1; nColIndex++)
		{
			imattBoard[nRowIndex][nColIndex] = FOOD;
		}
	}
}

//---------------------------------------------------------------------------------------
//                                       Print Board
//                                      -------------
//
// General      : The procedure prints the current state of the board.
//
// Parameters   : 
//      imattBoard - Board (In)
//		iplBulli   - Bulli (In)
//		iplBear    - Bear (In)
//
// Return Value : None (procedure)
// 
//---------------------------------------------------------------------------------------
void PrintBoard(Tile imattBoard[][SIZE + 2], Player iplBulli, Player iplBear)
{
	// Variable definition
	int nRowIndex;
	int nColIndex;

	// Code section
	
	printf("\n");
	// Iterating through every tile in board.
	for (nRowIndex = 0; nRowIndex < SIZE + 2; nRowIndex++)
	{
		for (nColIndex = 0; nColIndex < SIZE + 2; nColIndex++)
		{
			// Checking if bear stands on iterated tile.
			if (iplBear.nRowIndex == nRowIndex && iplBear.nColIndex == nColIndex)
			{
				printf("D ");
				continue;
			}
			// Checking if Bulli stands on iterated tile.
			if (iplBulli.nRowIndex == nRowIndex && iplBulli.nColIndex == nColIndex)
			{
				printf("B ");
				continue;
			}
			// Printing correct tile.
			switch (imattBoard[nRowIndex][nColIndex])
			{
			case WALL:
				printf("* ");
				break;
			case FOOD:
				printf(". ");
				break;
			default:
				printf("  ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

//---------------------------------------------------------------------------------------
//                                      Bulli Move
//                                     ------------
//
// General      : The function reads the user's instruction for Bulli and executes it.
//
// Parameters   : 
//      imattBoard - Board (In)
//		iopplBulli   - Bulli (In)
//		opnFood    - Food counter (Out)
//		iopcLastMove   - Last move of Bulli (In)
//
// Return Value : The function returns 1 if the move was executed succefully, 0 if Bulli
//				  was obstructed.
// 
//---------------------------------------------------------------------------------------
int BulliMove(Tile imattBoard[][SIZE + 2], Player* iopplBulli,
			  int* opnFood, char *iopcLastMove)
{
	// Variable definition
	char cCommand;

	// Code section

	printf("Enter command.\n");
	printf("1 or r for right movement, 2 or l for left movement,\n");
	printf("3 or u for up movement, 4 or d for down movement,\n");
	printf("0 for same direction movement.\n");
	scanf("\n%c", &cCommand);
	// Repeating last move.
	if (cCommand == '0')
	{
		cCommand = *iopcLastMove;
	}
	// Executing move in correct direction.
	switch (cCommand)
	{
	case '1':
	case 'r':
		*iopcLastMove = cCommand;
		// Checking if Bulli is obstructed.
		if (!imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex + 1])
		{
			return(0);
		}
		(*iopplBulli).nColIndex++;
		// Eating food.
		if (imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] == FOOD)
		{
			imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] = EMPTY;
			--* opnFood;
		}
		break;
	case '2':
	case 'l':
		*iopcLastMove = cCommand;
		// Checking if Bulli is obstructed.
		if (!imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex - 1])
		{
			return(0);
		}
		(*iopplBulli).nColIndex--;
		// Eating food.
		if (imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] == FOOD)
		{
			imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] = EMPTY;
			--* opnFood;
		}
		break;
	case '3':
	case 'u':
		*iopcLastMove = cCommand;
		// Checking if Bulli is obstructed.
		if (!imattBoard[(*iopplBulli).nRowIndex - 1][(*iopplBulli).nColIndex])
		{
			return(0);
		}
		(*iopplBulli).nRowIndex--;
		// Eating food.
		if (imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] == FOOD)
		{
			imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] = EMPTY;
			--* opnFood;
		}
		break;
	case '4':
	case 'd':
		*iopcLastMove = cCommand;
		// Checking if Bulli is obstructed.
		if (!imattBoard[(*iopplBulli).nRowIndex + 1][(*iopplBulli).nColIndex])
		{
			return(0);
		}
		(*iopplBulli).nRowIndex++;
		// Eating food.
		if (imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] == FOOD)
		{
			imattBoard[(*iopplBulli).nRowIndex][(*iopplBulli).nColIndex] = EMPTY;
			--* opnFood;
		}
		break;
	default:
		break;
	}
	return (1);
}

//---------------------------------------------------------------------------------------
//                                        Bear Move
//                                       -----------
//
// General      : The procedure executes the bear's move.
//
// Parameters   : 
//      imattBoard - Board (In)
//		iplBulli   - Bulli (In)
//		iopplBear   - Bear (In/Out)
//
// Return Value : None (procedure)
// 
//---------------------------------------------------------------------------------------
void BearMove(Tile imattBoard[][SIZE + 2], Player iplBulli, Player *iopplBear)
{
	// Checking if Bulli stepped into bear's tile.
	if (iplBulli.nRowIndex == (*iopplBear).nRowIndex &&
		iplBulli.nColIndex == (*iopplBear).nColIndex)
	{
		PrintBoard(imattBoard, iplBulli, *iopplBear);
		printf("WASTED!\n");
		printf("The bear enjoys its meal.\n");
		exit(0);
	}
	// Trying to move towards Bulli.
	else if (iplBulli.nRowIndex < (*iopplBear).nRowIndex &&
			 iplBulli.nColIndex < (*iopplBear).nColIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex - 1][(*iopplBear).nColIndex - 1])
		{
			(*iopplBear).nRowIndex--;
			(*iopplBear).nColIndex--;
		}
	}
	else if (iplBulli.nRowIndex < (*iopplBear).nRowIndex &&
			 iplBulli.nColIndex > (*iopplBear).nColIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex - 1][(*iopplBear).nColIndex + 1])
		{
			(*iopplBear).nRowIndex--;
			(*iopplBear).nColIndex++;
		}
	}
	else if (iplBulli.nRowIndex < (*iopplBear).nRowIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex - 1][(*iopplBear).nColIndex])
		{
			(*iopplBear).nRowIndex--;
		}
	}
	else if (iplBulli.nRowIndex > (*iopplBear).nRowIndex &&
			 iplBulli.nColIndex < (*iopplBear).nColIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex - 1][(*iopplBear).nColIndex + 1])
		{
			(*iopplBear).nRowIndex++;
			(*iopplBear).nColIndex--;
		}
	}
	else if (iplBulli.nRowIndex > (*iopplBear).nRowIndex &&
			 iplBulli.nColIndex > (*iopplBear).nColIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex + 1][(*iopplBear).nColIndex + 1])
		{
			(*iopplBear).nRowIndex++;
			(*iopplBear).nColIndex++;
		}
	}
	else if (iplBulli.nRowIndex > (*iopplBear).nRowIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex + 1][(*iopplBear).nColIndex])
		{
			(*iopplBear).nRowIndex++;
		}
	}
	else if (iplBulli.nColIndex < (*iopplBear).nColIndex)
	{
		if (imattBoard[(*iopplBear).nRowIndex][(*iopplBear).nColIndex - 1])
		{
			(*iopplBear).nColIndex--;
		}
	}
	else
	{
		if (imattBoard[(*iopplBear).nRowIndex][(*iopplBear).nColIndex + 1])
		{
			(*iopplBear).nColIndex++;
		}
	}
	// Checking if Bulli was caught.
	if (iplBulli.nRowIndex == (*iopplBear).nRowIndex &&
		iplBulli.nColIndex == (*iopplBear).nColIndex)
	{
		PrintBoard(imattBoard, iplBulli, *iopplBear);
		printf("WASTED!\n");
		printf("The bear enjoys its meal.\n");
		exit(0);
	}
}