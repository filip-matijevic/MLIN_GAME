//#include "Tile.h"
#include "GameplayManager.h"

class TileManager
{
public:
	TileManager(int numberOfTiles);
	void drawTiles();
	void placeTiles();
	void validateHoverInput(int x, int y);
	void validatePressInput(int state);

	

	void reset();

private:
	Tile tiles[49];
	int _numberOfTiles;

	void raycastForNeighbors();

	int numberOfMillTiles();
	int numberOfNonMillTiles();

	void playerHelper();
	void checkEndGame();
	GameplayManager gameplayManager;
};