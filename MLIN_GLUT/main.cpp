#include<GL/glut.h>

#include <iostream> 
#include "Board.h"
const float WINDOW_WIDTH = 740;
const float WINDOW_HEIGHT = 480.0;

Board myBoard(400, 400);

void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	myBoard.drawBoard();
	glFlush();
}

void postRender(int x) {
	glutPostRedisplay();
	glutTimerFunc(100, postRender, 0);
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);

}

void mouseInput(int button, int state, int x, int y) {
	myBoard.validatePressInput(state);
}

void mouseHoverInput(int x, int y) {
	myBoard.validateHoverInput(x, WINDOW_HEIGHT - y);
}

void keyRelease(unsigned char key, int x, int y) {
	if (key == 'r' || key == 'R') {
		myBoard.reset();
	}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Mlin game");

	glutMouseFunc(mouseInput);
	glutPassiveMotionFunc(mouseHoverInput);
	glutDisplayFunc(render);
	glutKeyboardUpFunc(keyRelease);


	myinit();

	glutTimerFunc(100, postRender, 2);
	glutMainLoop();
}