#ifndef TILEMANAGER_HEADER
#define TILEMANAGER_HEADER
#include "TileManager.h"
#include "GLUtils.h"

#include<GL/glut.h>
#include <cstdlib>
#include <iostream>

TileManager::TileManager(int numberOfTiles)
{
	_numberOfTiles = numberOfTiles;
	int tileIndex = 0;

	placeTiles();
}

void TileManager::reset() {
	for (int i = 0; i < _numberOfTiles; i++) {
		tiles[i].occupation = 0;
	}
	gameplayManager.reset();
}

void TileManager::drawTiles() {
	//for (int i = 0; i < _numberOfTiles; i++) {
		//_tiles[i].highlightNeighbors();
	//}

	playerHelper();

	for (int i = 0; i < _numberOfTiles; i++) {
		if (tiles[i]._isHighlighted) {
			tiles[i].draw(gameplayManager.playerTurn);
		}
		else {
			tiles[i].draw();
		}
	}

	gameplayManager.drawGameplayStatus();
}

void TileManager::playerHelper() {

	if (gameplayManager.playerTurn == 0) {
		glColor3f(0.8, 0.8, 0.8);
	}
	else {
		glColor3f(1, 1, 1);
	}
	drawCircle(640 / 2, 480 / 2, 80, 2, gameplayManager.playerTurn + 1);
	if (gameplayManager.gamePhase == 0) {
		//highlight all the available spots
		if (gameplayManager.moveType == 0) {
			for (int i = 0; i < _numberOfTiles; i++) {
				if (tiles[i].occupation == 0) {
					tiles[i]._isHighlighted = true;
				}
				else {
					tiles[i]._isHighlighted = false;
				}
			}
		}

		if (gameplayManager.moveType == 1) {
			if (numberOfNonMillTiles() > 0) {
				//Highlight only NON MILL tiles
				for (int i = 0; i < _numberOfTiles; i++) {
					if (!tiles[i].checkMill() &&
						tiles[i].occupation == ((gameplayManager.playerTurn + 1) % 2 + 1)) {
						tiles[i]._isHighlighted = true;
					}
					else {
						tiles[i]._isHighlighted = false;
					}
				}
			}
			else {
				// highlight other tiles
				for (int i = 0; i < _numberOfTiles; i++) {
					if (tiles[i].occupation == ((gameplayManager.playerTurn + 1) % 2 + 1)) {
						tiles[i]._isHighlighted = true;
					}
					else {
						tiles[i]._isHighlighted = false;
					}
				}
			}
		}

	}

	if (gameplayManager.gamePhase == 1) {
		if (gameplayManager.moveType == 0) {
			//picking up
			if (gameplayManager.pickedUpTile == nullptr) {
				for (int i = 0; i < _numberOfTiles; i++) {
					if (tiles[i].occupation == (gameplayManager.playerTurn + 1)) {
						if (gameplayManager.canTileBePickedUp(&tiles[i])) {
							tiles[i]._isHighlighted = true;
						}
						else {
							tiles[i]._isHighlighted = false;
						}
					}
					else {

						tiles[i]._isHighlighted = false;
					}
				}
			}
			else {
				//highlight only legit moves
				for (int i = 0; i < _numberOfTiles; i++) {
					tiles[i]._isHighlighted = false;
				}

				if (gameplayManager.pickedUpTile->leftTile != nullptr) {
					if (gameplayManager.pickedUpTile->leftTile->occupation == 0) {
						gameplayManager.pickedUpTile->leftTile->_isHighlighted = true;
					}
				}

				if (gameplayManager.pickedUpTile->rightTile != nullptr) {
					if (gameplayManager.pickedUpTile->rightTile->occupation == 0) {
						gameplayManager.pickedUpTile->rightTile->_isHighlighted = true;
					}
				}

				if (gameplayManager.pickedUpTile->upTile != nullptr) {
					if (gameplayManager.pickedUpTile->upTile->occupation == 0) {
						gameplayManager.pickedUpTile->upTile->_isHighlighted = true;
					}
				}

				if (gameplayManager.pickedUpTile->downTile != nullptr) {
					if (gameplayManager.pickedUpTile->downTile->occupation == 0) {
						gameplayManager.pickedUpTile->downTile->_isHighlighted = true;
					}
				}
			}

		}

		if (gameplayManager.moveType == 1) {
			if (numberOfNonMillTiles() > 0) {
				//Highlight only NON MILL tiles
				for (int i = 0; i < _numberOfTiles; i++) {
					if (!tiles[i].checkMill() &&
						tiles[i].occupation == ((gameplayManager.playerTurn + 1) % 2 + 1)) {
						tiles[i]._isHighlighted = true;
					}
					else {
						tiles[i]._isHighlighted = false;
					}
				}
			}
			else {
				// highlight other tiles
				for (int i = 0; i < _numberOfTiles; i++) {
					if (tiles[i].occupation == ((gameplayManager.playerTurn + 1) % 2 + 1)) {
						tiles[i]._isHighlighted = true;
					}
					else {
						tiles[i]._isHighlighted = false;
					}
				}
			}
		}
	}

}

void TileManager::validateHoverInput(int x, int y) {
	for (int i = 0; i < _numberOfTiles; i++) {
		tiles[i].isMouseOver(x, y);
	}
}

int TileManager::numberOfMillTiles() {
	int numberOfMills = 0;
	int turn = (gameplayManager.playerTurn + 1) % 2;
	for (int i = 0; i < _numberOfTiles; i++) {
		if (tiles[i].checkMill() && (tiles[i].occupation == ((turn + 1)))) {
			numberOfMills++;
		}
	}

	printf("There are %d tiles involved in a mill", numberOfMills);

		return numberOfMills;
}

int TileManager::numberOfNonMillTiles() {
	int numberOfNonMills = 0;
	int turn = (gameplayManager.playerTurn + 1) % 2;
	for (int i = 0; i < _numberOfTiles; i++) {
		if (!tiles[i].checkMill() && (tiles[i].occupation == ((turn + 1)))) {
			numberOfNonMills++;
		}
	}
	return numberOfNonMills;
}

void TileManager::validatePressInput(int state) {
	if (!state) {
		//trigger only on release
		return;
	}
	for (int i = 0; i < _numberOfTiles; i++) {
		if (tiles[i].isMouseReleased()) {
			//input completed
			if (gameplayManager.isGameOver) {
				return;
			}

			if (gameplayManager.gamePhase == 0) {
				//phase 1 -> placing tiles
				if (gameplayManager.moveType == 0) {
					gameplayManager.placePlayerTile(&tiles[i]);					
				}

				if (gameplayManager.moveType == 1) {
					//removal of a tile ---> ONLY IF IT IS NOT IN A MILL
					if (numberOfNonMillTiles() > 0) {
						printf("you must not remove a mill tile!\n");
						if (!tiles[i].checkMill()) {
							printf("This one CAN BE removed\n");
							gameplayManager.removePlayerTile(&tiles[i]);
						}
					}
					else {
						printf("This one CAN BE removed\n");
						gameplayManager.removePlayerTile(&tiles[i]);
					}
				}
			}

			if (gameplayManager.gamePhase == 1) {
				//phase 2 -> moving tiles
				if (gameplayManager.moveType == 0) {

					gameplayManager.pickUpTile(&tiles[i]);
				}
				if (gameplayManager.moveType == 1) {
					if (numberOfNonMillTiles() > 0) {
						printf("you must not remove a mill tile!\n");
						if (!tiles[i].checkMill()) {
							printf("This one CAN BE removed\n");
							gameplayManager.removePlayerTile(&tiles[i]);
						}
					}
					else {
						printf("This one CAN BE removed\n");
						gameplayManager.removePlayerTile(&tiles[i]);
					}
				}
			}
		}
	}

	checkEndGame();
}

void TileManager::checkEndGame() {
	if (gameplayManager.gamePhase == 1) {
		int legalMoves = 0;
		int playerTwoLegalMoves = 0;

		for (int i = 0; i < _numberOfTiles; i++) {
			if ((tiles[i].occupation == (gameplayManager.playerTurn + 1)) && gameplayManager.canTileBePickedUp(&tiles[i])) {
				legalMoves++;
			}
		}

		if (legalMoves == 0) {
			gameplayManager.isGameOver = true;
			gameplayManager.winningPlayer = (gameplayManager.playerTurn + 1) % 2;
		}
	}

	
}

void TileManager::placeTiles() {

	printf("ASSIGNING TILES\n");
	int tileIndex = 0;
	// layer 0
	tiles[0] = Tile(640 / 2 - 200, 480 / 2 - 200, 0);
	tiles[1] = Tile(640 / 2 - 0, 480 / 2 - 200, 1);
	tiles[2] = Tile(640 / 2 + 200, 480 / 2 - 200, 2);

	tiles[3] = Tile(640 / 2 - 200, 480 / 2, 3);
	tiles[4] = Tile(640 / 2 + 200, 480 / 2, 4);

	tiles[5] = Tile(640 / 2 - 200, 480 / 2 + 200, 5);
	tiles[6] = Tile(640 / 2 - 0, 480 / 2 + 200, 6);
	tiles[7] = Tile(640 / 2 + 200, 480 / 2 + 200, 7);

	//layer 1
	tiles[8] = Tile(640 / 2 - 200 + 200 / 3, 480 / 2 - 200 + 200 / 3, 8);
	tiles[9] = Tile(640 / 2 - 0, 480 / 2 - 200 + 200 / 3, 9);
	tiles[10] = Tile(640 / 2 + 200 - 200 / 3, 480 / 2 - 200 + 200 / 3, 10);

	tiles[11] = Tile(640 / 2 - 200 + 200 / 3, 480 / 2, 11);
	tiles[12] = Tile(640 / 2 + 200 - 200 / 3, 480 / 2, 12);

	tiles[13] = Tile(640 / 2 - 200 + 200 / 3, 480 / 2 + 200 - 200 / 3, 13);
	tiles[14] = Tile(640 / 2 - 0, 480 / 2 + 200 - 200 / 3, 14);
	tiles[15] = Tile(640 / 2 + 200 - 200 / 3, 480 / 2 + 200 - 200 / 3, 15);

	//layer 2
	tiles[16] = Tile(640 / 2 - 200 + 400 / 3, 480 / 2 - 200 + 400 / 3, 16);
	tiles[17] = Tile(640 / 2 - 0, 480 / 2 - 200 + 400 / 3, 17);
	tiles[18] = Tile(640 / 2 + 200 - 400 / 3, 480 / 2 - 200 + 400 / 3, 18);

	tiles[19] = Tile(640 / 2 - 200 + 400 / 3, 480 / 2, 19);
	tiles[20] = Tile(640 / 2 + 200 - 400 / 3, 480 / 2, 20);

	tiles[21] = Tile(640 / 2 - 200 + 400 / 3, 480 / 2 + 200 - 400 / 3, 21);
	tiles[22] = Tile(640 / 2 - 0, 480 / 2 + 200 - 400 / 3, 22);
	tiles[23] = Tile(640 / 2 + 200 - 400 / 3, 480 / 2 + 200 - 400 / 3, 23);


	tiles[24] = Tile(640 / 2, 480 / 2, -1);

	raycastForNeighbors();
	


}

void TileManager::raycastForNeighbors() {
	
	//RAYCAST
	for (int i = 0; i < _numberOfTiles; i++) {
		int step = 10;
		for (int j = 0; j < _numberOfTiles + 1; j++) {
			int raycastLength = 40;
			while (raycastLength < 650) {
				if (tiles[j].isPointInside(tiles[i].posX + raycastLength, tiles[i].posY)) {
					if (tiles[i].rightTile == nullptr) {
						tiles[i].rightTile = &tiles[j];
					}
					else {
						if (abs(tiles[i].posX - tiles[i].rightTile->posX) > abs(tiles[i].posX - tiles[j].posX)) {
							tiles[i].rightTile = &tiles[j];
						}
					}
				}

				if (tiles[j].isPointInside(tiles[i].posX - raycastLength, tiles[i].posY)) {
					if (tiles[i].leftTile == nullptr) {
						tiles[i].leftTile = &tiles[j];
					}
					else {
						if (abs(tiles[i].posX - tiles[i].leftTile->posX) > abs(tiles[i].posX - tiles[j].posX)) {
							tiles[i].leftTile = &tiles[j];
						}
					}
				}

				if (tiles[j].isPointInside(tiles[i].posX, tiles[i].posY - raycastLength)) {
					if (tiles[i].downTile == nullptr) {
						tiles[i].downTile = &tiles[j];
					}
					else {
						if (abs(tiles[i].posY - tiles[i].downTile->posY) > abs(tiles[i].posY - tiles[j].posY)) {
							tiles[i].downTile = &tiles[j];
						}
					}
				}

				if (tiles[j].isPointInside(tiles[i].posX, tiles[i].posY + raycastLength)) {
					
					if (tiles[i].upTile == nullptr) {
						tiles[i].upTile = &tiles[j];
					}
					else {
						if (abs(tiles[i].posY - tiles[i].upTile->posY) > abs(tiles[i].posY - tiles[j].posY)) {

							tiles[i].upTile = &tiles[j];
						}
					}
				}
				raycastLength += step;
			}
		}
	}
}

#endif