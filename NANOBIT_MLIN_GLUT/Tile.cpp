#ifndef TILE_HEADER
#define TILE_HEADER
#include "Tile.h"
#include "GLUtils.h"

#include<GL/glut.h>
#include <cstdlib>
#include <iostream>
Tile::Tile(int x, int y, int idX)
{
	posX = x;
	posY = y;

	_width = 40;

	_isPressed = false;
	_isHighlighted = false;
	_isMouseOver = false;

	rightTile = nullptr;
	leftTile = nullptr;
	downTile = nullptr;
	upTile = nullptr;
	occupation = 0;

	tileIdx = idX;
}

Tile::Tile()
{
	tileIdx = -1;
}

bool Tile::isMouseOver(int x, int y) {

	if ((abs(x - posX) < _width / 2) && (abs(y - posY) < _width / 2)) {
		_isMouseOver = true;
	}
	else {
		_isMouseOver = false;
	}

	_isHighlighted = false;
	return true;
}

bool Tile::isPointInside(int x, int y) {
	if ((abs(x - posX) < _width / 2) && (abs(y - posY) < _width / 2)) {

		return true;
	}
	else {
		return false;
	}
}

void Tile::highlightNeighbors() {

	if (_isMouseOver) {

		if (rightTile != nullptr) {
			rightTile->highlightOther(0);
		}

		if (leftTile != nullptr) {
			leftTile->highlightOther(1);
		}

		if (upTile != nullptr) {
			upTile->highlightOther(2);
		}

		if (downTile != nullptr) {
			downTile->highlightOther(3);
		}
	}
}

//0 - RIGHT
//1 - LEFT
//2 - UP
//3 - DOWN
void Tile::highlightOther(int  side) {

	if (tileIdx == -1) {
		return;
	}
	_isHighlighted = true;
	switch (side)
	{
	case 0:
		if (rightTile != nullptr) {
			rightTile->highlightOther(side);
		}
		break;
	case 1:
		if (leftTile != nullptr) {
			leftTile->highlightOther(side);
		}
		break;
	case 2:
		if (upTile != nullptr) {
			upTile->highlightOther(side);
		}
		break;

	case 3:
		if (downTile != nullptr) {
			downTile->highlightOther(side);
		}
		break;
	}

}

bool Tile::isPressed(int state, int playerID) {
	_isPressed = !state;

	if (_isMouseOver) {
		if (state) {

			if (occupation == 0) {
				occupation = playerID;
				printf("Tile %d set to player occupation %d\n", tileIdx, occupation);
				//checkMill();

				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool Tile::isMouseReleased() {
	if (_isMouseOver) {
		return true;
	}
	else {
		return false;
	}
}



bool Tile::removeEnemyTile(int playerTile) {
	if (occupation == 0 || occupation == (1 + (playerTile + 1) % 2)) {
		return false;
	}
	else {
		occupation = 0;
		return true;
	}
}

bool Tile::checkMill() {
	if (occupation != 0) {
		int millCount = horizontalMillCount(occupation);
		if (millCount == 3) {
			return true;
		}
	}
	return false;
}

int Tile::horizontalMillCount(int currentMill) {
	if (leftTile == nullptr) {
		// i am far right
		if (occupation == currentMill && rightTile->occupation == currentMill && rightTile->rightTile->occupation == currentMill) {
			return 3;
		}
	}
	else if (leftTile->tileIdx == -1) {
		if (occupation == currentMill && rightTile->occupation == currentMill && rightTile->rightTile->occupation == currentMill) {
			return 3;
		}
	}

	//look for right mill
	if (rightTile == nullptr) {
		// i am far right
		if (occupation == currentMill && leftTile->occupation == currentMill && leftTile->leftTile->occupation == currentMill) {
			return 3;
		}
	} 
	else if (rightTile->tileIdx == -1) {
		if (occupation == currentMill && leftTile->occupation == currentMill && leftTile->leftTile->occupation == currentMill) {
			return 3;
		}
	}
	if (rightTile != nullptr && leftTile != nullptr) {
		// i am middle
		if (occupation == currentMill && leftTile->occupation == currentMill && rightTile->occupation == currentMill) {
			return 3;
		}
	}
	if (upTile == nullptr) {
		// i am far right
		if (occupation == currentMill && downTile->occupation == currentMill && downTile->downTile->occupation == currentMill) {
			return 3;
		}
	}
	else if (upTile->tileIdx == -1) {
		if (occupation == currentMill && downTile->occupation == currentMill && downTile->downTile->occupation == currentMill) {
			return 3;
		}
	}
	if (downTile == nullptr) {
		// i am far right
		if (occupation == currentMill && upTile->occupation == currentMill && upTile->upTile->occupation == currentMill) {
			return 3;
		}
	}
	else if (downTile->tileIdx == -1) {
		if (occupation == currentMill && upTile->occupation == currentMill && upTile->upTile->occupation == currentMill) {
			return 3;
		}
	}


	if (upTile != nullptr && downTile != nullptr) {
		// i am far right
		if (occupation == currentMill && downTile->occupation == currentMill && upTile->occupation == currentMill) {
			return 3;
		}
	}

	return 0;
}

bool Tile::isNeightborWith(Tile *tile) {
	if (leftTile != nullptr) {
		if (leftTile == tile) {
			printf("this is a neightbor\n");
			return true;
		}
	}

	if (rightTile != nullptr) {
		if (rightTile == tile) {
			printf("this is a neightbor\n");
			return true;
		}
	}

	if (upTile != nullptr) {
		if (upTile == tile) {
			printf("this is a neightbor\n");
			return true;
		}
	}

	if (downTile != nullptr) {
		if (downTile == tile) {
			printf("this is a neightbor\n");
			return true;
		}
	}

	printf("this is NOT a neightbor\n");
	return false;
}


void Tile::draw() {

	int strokeWidth = 0;
	if (_isMouseOver) {
		strokeWidth = 0;		
	}
	else if (_isHighlighted){
		strokeWidth = 3;
	}
	else {
		strokeWidth = 0;
	}
	drawCircle(posX, posY, _width, strokeWidth, occupation, 0.0, 0.0, 0.0);
	glLineWidth(2.0);
}

void Tile::draw(int playerTurn) {

	int strokeWidth = 0;
	if (_isMouseOver) {
		strokeWidth = 0;
	}
	else if (_isHighlighted) {
		strokeWidth = 3;
	}
	else {
		strokeWidth = 0;
	}

	if (playerTurn == 1) {
		drawCircle(posX, posY, _width, strokeWidth, occupation, 0.5, 0.9, 0.5);
	}
	else {
		drawCircle(posX, posY, _width, strokeWidth, occupation, 0.5, 0.9, 0.5);
	}

	glLineWidth(2.0);

}

int Tile::getID() {
	return tileIdx;
}
#endif