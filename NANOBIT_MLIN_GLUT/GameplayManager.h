#pragma once
#include "Tile.h"

class GameplayManager
{
public:
	GameplayManager();

	int playerTurn  = 0;
	int placementMovesLeft[2];
	int tilesOnBoard[2];

	void displayGameStatus();
	bool placePlayerTile(Tile *tile);
	bool removePlayerTile(Tile *tile);
	bool didMoveResultAMill(Tile *completedMove);

	bool canTileBePickedUp(Tile *tile);

	void nextPlayerTurn();
	void setMoveToRemoval();

	void pickUpTile(Tile *tile);

	void drawGameplayStatus();

	void reset();

	
	bool isGameOver;

	//0 placing tiles
	//1 removing tiles
	//2 moving tiles
	int moveType = 0;
	//0 Phase 1 - Placing tiles
	//1 Phase 2 - Moving tiles
	//2 Phase 3 - Jumping tiles
	int gamePhase = 0;
	int winningPlayer = 0;
	Tile *pickedUpTile;

private:

	

};
