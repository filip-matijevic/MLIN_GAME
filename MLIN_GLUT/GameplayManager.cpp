#include "GameplayManager.h"
#include "GLUtils.h"

#include <iostream>
GameplayManager::GameplayManager()
{
	placementMovesLeft[0] = 9;
	placementMovesLeft[1] = 9;

	tilesOnBoard[0] = 0;
	tilesOnBoard[1] = 0;

	isGameOver = false;
	playerTurn = 1;

	nextPlayerTurn();
}

void GameplayManager::reset() {
	placementMovesLeft[0] = 9;
	placementMovesLeft[1] = 9;

	tilesOnBoard[0] = 0;
	tilesOnBoard[1] = 0;

	isGameOver = false;
	playerTurn = 1;

	gamePhase = 0;
	moveType = 0;


	nextPlayerTurn();
}


bool GameplayManager::didMoveResultAMill(Tile* completedMove) {
	if (completedMove->checkMill()) {
		printf("********** ********** This is a mill, good job\n");
		return true;
	}
	return false;
}

bool GameplayManager::placePlayerTile(Tile *tile) {
	if (tile->occupation != 0) {

		printf("invalid move\n");
		return false;
	}
	else {
		tile->occupation = playerTurn + 1;
		tilesOnBoard[playerTurn]++;
		placementMovesLeft[playerTurn]--;
		if (tile->checkMill()) {
			printf("Player %d created a mill on tile %d\n", playerTurn + 1, tile->tileIdx);
			setMoveToRemoval();
		}
		else {
			nextPlayerTurn();
		}
	}
}

bool GameplayManager::removePlayerTile(Tile *tile) {
	if (tile->occupation == 0) {

		printf("invalid move\n");
		return false;
	}
	else {
		if (tile->occupation == playerTurn + 1) {
			printf("invalid move\n");
			return false;
		}
		else {
			tile->occupation = 0;

			tilesOnBoard[(playerTurn + 1) % 2]--;
			moveType = 0;
			nextPlayerTurn();
			return true;
		}
	}
}

void GameplayManager::nextPlayerTurn() {
	playerTurn = (playerTurn + 1) % 2;
	//utilPlayerTurn = playerTurn;

	if (placementMovesLeft[playerTurn] == 0 && tilesOnBoard[playerTurn] <= 2) {
		printf("Game is over! Player %d won\n", ((playerTurn + 1) % 2) + 1);
		winningPlayer = ((playerTurn + 1) % 2);
		isGameOver = true;
		return;
	}

	if (placementMovesLeft[playerTurn] > 0) {
		printf("Player [%d] is playing! Number of tiles : %d\n", playerTurn + 1, placementMovesLeft[playerTurn]);
		gamePhase = 0;
	}
	else {
		printf("Player [%d] is out of placement moves. Movement phase begins\n", playerTurn + 1);
		gamePhase = 1;
	}
}

void GameplayManager::pickUpTile(Tile *tile) {

	if (pickedUpTile == nullptr) {
		//nothing picked up yet
		if (tile->occupation == (playerTurn + 1)) {
			//check if tile can be moved at all
			if (canTileBePickedUp(tile)) {
				printf("This tile can be picked up\n");
				pickedUpTile = tile;
			}
			else {

				printf("This tile is stuck, you can not pick it up\n");
			}
		}
	}
	else {
		//try to release tile
		if (tile->occupation == 0) {
			if (pickedUpTile->isNeightborWith(tile)) {
				printf("Do the move\n");
				pickedUpTile->occupation = 0;
				tile->occupation = playerTurn + 1;
				pickedUpTile = nullptr;

				//check if mill was made
				if (tile->checkMill()) {
					printf("THIS IS A MILL! You Get to remove a tile\n");
					setMoveToRemoval();
				}
				else {

					printf("No mill, continue please\n");
					nextPlayerTurn();
				}
			}
		}

	}

}

bool GameplayManager::canTileBePickedUp(Tile *tile) {
	if (tile->leftTile != nullptr) {
		if ((tile->leftTile->occupation == 0) && (tile->leftTile->tileIdx != -1)) {
			return true;
		}
	}

	if (tile->rightTile != nullptr) {
		if ((tile->rightTile->occupation == 0) && (tile->rightTile->tileIdx != -1)) {
			return true;
		}
	}

	if (tile->upTile != nullptr) {
		if ((tile->upTile->occupation == 0) && (tile->upTile->tileIdx != -1)) {
			return true;
		}
	}

	if (tile->downTile != nullptr) {
		if ((tile->downTile->occupation == 0) && (tile->downTile->tileIdx != -1)) {
			return true;
		}
	}
	return false;
}

void GameplayManager::drawGameplayStatus() {

	if (playerTurn == 0) {
		drawCircle(600, 440, 40, 3, 1);
		drawCircle(700, 440, 40, 1, 2);
	}
	else {

		drawCircle(600, 440, 40, 1, 1);
		drawCircle(700, 440, 40, 3, 2);
	}
	RenderString(600, 440, "P1", 1, 1, 1);
	RenderString(700, 440, "P2", 0, 0, 0);
	for (int i = 0; i < placementMovesLeft[0]; i++) {
		drawCircle(600, 390 - i * 20, 40, 1, 1);
	}

	for (int i = 0; i < tilesOnBoard[0]; i++) {
		drawCircle(600, 200 + i * 20, 40, 1, 1);
	}

	for (int i = 0; i < placementMovesLeft[1]; i++) {
		drawCircle(700, 390 - i * 20, 40, 1, 2);
	}

	for (int i = 0; i < tilesOnBoard[1]; i++) {
		drawCircle(700, 200 + i * 20, 40, 1, 2);
	}




	if (isGameOver) {

		RenderString(580, 150, "GAME OVER", 0, 0, 0);
		if (winningPlayer == 0) {

			RenderString(580, 100, "P1 WINS", 0, 0, 0);
		}
		else {

			RenderString(580, 100, "P2 WINS", 0, 0, 0);
		}
		RenderString(580, 50, "R - RESTART", 0, 0, 0);
	}
	else {
		if (playerTurn == 0) {
			RenderString(580, 150, "Player 1 (B )", 0, 0, 0);
		}
		else {

			RenderString(580, 150, "Player 2 (W )", 0, 0, 0);
		}

		if (gamePhase == 0) {

			if (moveType == 0) {
				RenderString(580, 110, "Place tile", 0, 0, 0);
			}

			if (moveType == 1) {
				RenderString(580, 110, "Remove enemy", 0, 0, 0);
				RenderString(580, 90, "tile", 0, 0, 0);
			}
		}
		else if (gamePhase == 1) {
			if (moveType == 0) {

				if (pickedUpTile == nullptr) {
					RenderString(580, 110, "MOVE:pick up", 0, 0, 0);
				}
				else {

					RenderString(580, 110, "MOVE:release", 0, 0, 0);
				}
			}
			if (moveType == 1) {
				RenderString(580, 110, "Remove enemy", 0, 0, 0);
				RenderString(580, 90, "tile", 0, 0, 0);
			}
		}
	}


	
}

void GameplayManager::setMoveToRemoval() {
	moveType = 1;
}