#include "TileManager.h"

class Board
{
public:
	Board(int w, int h);
	void drawBoard();
	void drawLines();

	void validateHoverInput(int x, int y);
	void validatePressInput(int inp);

	void reset();

private:
	int _width;
	int _height;
	TileManager _manager = TileManager(24);
};
