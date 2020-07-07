#ifndef TILE_HEADER
#define TILE_HEADER
#include "GLUtils.h"
#include<GL/glut.h>

#include <iostream>

void drawCircle(int posX, int posY, int r, int strokeWidth, int occupation) {

	glLineWidth(strokeWidth);

	switch (occupation)
	{
	case 0:
		setBeige();
		break;
	case 1:
		setGray();
		break;
	case 2:
		setWhite();
		break;
	default:
		setBeige();
		break;
	}

	glBegin(GL_POLYGON);

	for (int i = 0; i < 12; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(12);//get the current angle 
		float x = r / 2 * cosf(theta);//calculate the x component 
		float y = r / 2 * sinf(theta);//calculate the y component 
		glVertex2f(x + posX, y + posY);//output vertex 
	}
	glEnd();


	setBlack();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 12; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(12);//get the current angle 
		float x = r/2 * cosf(theta);//calculate the x component 
		float y = r/2 * sinf(theta);//calculate the y component 
		glVertex2f(x + posX, y + posY);//output vertex 
	}
	glEnd();

	glLineWidth(2.0);
}

void drawCircle(int posX, int posY, int radius, int strokeWidth, int occupation, float r, float g, float b) {

	glLineWidth(strokeWidth);

	switch (occupation)
	{
	case 0:
		setBeige();
		break;
	case 1:
		setGray();
		break;
	case 2:
		setWhite();
		break;
	default:
		setBeige();
		break;
	}

	glBegin(GL_POLYGON);

	for (int i = 0; i < 12; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(12);//get the current angle 
		float x = radius / 2 * cosf(theta);//calculate the x component 
		float y = radius / 2 * sinf(theta);//calculate the y component 
		glVertex2f(x + posX, y + posY);//output vertex 
	}
	glEnd();



	glColor3f(r, g, b);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 12; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(12);//get the current angle 
		float x = radius / 2 * cosf(theta);//calculate the x component 
		float y = radius / 2 * sinf(theta);//calculate the y component 
		glVertex2f(x + posX, y + posY);//output vertex 
	}
	glEnd();

	glLineWidth(2.0);
}

void RenderString(float x, float y, const char* string, int r, int g, int b)
{
	glColor3f(r, g, b);
	glRasterPos2f(x - 9, y - 9);

	int charindex = 0;

	while (string[charindex] != '\0') {
		glRasterPos2f(x - 9 + 12 * charindex, y - 7);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[charindex]);
		charindex++;
	}
}

void drawButton(int posX, int posY, int edgeRadius, int r, int g, int b) {

}

void setBeige() {
	glColor3f(245.0 / 255.0, 245.0 / 255.0, 220.0 / 255.0);
}

void setBlack() {
	glColor3f(0, 0, 0);
}

void setGray() {
	glColor3f(0.3, 0.3, 0.3);
}
void setWhite() {
	glColor3f(1, 1, 1);
}
#endif