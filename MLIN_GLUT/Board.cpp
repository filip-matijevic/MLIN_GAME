#ifndef BOARD_HEADER
#define BOARD_HEADER
#include <iostream> 
#include<GL/glut.h>
#include "Board.h"

Board::Board(int w, int h)
{
	_width = w;
	_height = h;
	//_manager = TileManager(24);
}

void Board::reset() {
	_manager.reset();
}

void Board::drawBoard() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(245.0 / 255.0, 245.0 / 255.0 , 220.0 / 255.0);

	drawLines();
	_manager.drawTiles();

}

void Board::validateHoverInput(int x, int y) {
	_manager.validateHoverInput(x, y);
}

void Board::validatePressInput(int inp) {
	_manager.validatePressInput(inp);
}

void Board::drawLines() {

	glPointSize(6.0);

	//background
	glBegin(GL_POLYGON);
	glVertex2f(640.0 / 2.0 - _width / 2, 480.0 / 2.0 + _width / 2);
	glVertex2f(640.0 / 2.0 + _width / 2, 480.0 / 2.0 + _width / 2);
	glVertex2f(640.0 / 2.0 + _width / 2, 480.0 / 2.0 - _width / 2);
	glVertex2f(640.0 / 2.0 - _width / 2, 480.0 / 2.0 - _width / 2);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	for (int i = 0; i < 3; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(640.0 / 2.0 - _width / 2 + _width / 6 * i, 480.0 / 2.0 + _width / 2 - _width / 6 * i);
		glVertex2f(640.0 / 2.0 + _width / 2 - _width / 6 * i, 480.0 / 2.0 + _width / 2 - _width / 6 * i);
		glVertex2f(640.0 / 2.0 + _width / 2 - _width / 6 * i, 480.0 / 2.0 - _width / 2 + _width / 6 * i);
		glVertex2f(640.0 / 2.0 - _width / 2 + _width / 6 * i, 480.0 / 2.0 - _width / 2 + _width / 6 * i);
		glEnd();
	}
	//lines
	glBegin(GL_LINES);
	glVertex2f(640.0 / 2.0 - _width / 2, 480.0 / 2.0);
	glVertex2f(640.0 / 2.0 - _width / 2 + _width / 6 * 2, 480.0 / 2.0);

	glVertex2f(640.0 / 2.0 + _width / 2, 480.0 / 2.0);
	glVertex2f(640.0 / 2.0 + _width / 2 - _width / 6 * 2, 480.0 / 2.0);

	glVertex2f(640.0 / 2.0, 480.0 / 2.0 + _width / 2);
	glVertex2f(640.0 / 2.0, 480.0 / 2.0 + _width / 2 - _width / 6 * 2);

	glVertex2f(640.0 / 2.0, 480.0 / 2.0 - _width / 2);
	glVertex2f(640.0 / 2.0, 480.0 / 2.0 - _width / 2 + _width / 6 * 2);
	glEnd();
}
#endif