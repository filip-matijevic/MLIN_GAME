class Tile
{
public:
	Tile(int x, int y, int tileIdx);
	Tile();
	bool isMouseOver(int x, int y);
	bool isPressed(int state, int playerID);
	void draw();
	void draw(int playerTurn);

	void highlightNeighbors();
	void highlightOther(int side);

	bool removeEnemyTile(int playerTile);

	bool isMouseReleased();

	bool isNeightborWith(Tile * tile);
	

	int getID();

	bool isPointInside(int x, int y);

	Tile *rightTile;
	Tile *leftTile;
	Tile *upTile;
	Tile *downTile;


	int posX;
	int posY;
	int tileIdx;

	//0 - unoccupied
	//1 - player 1
	//2 - player 2
	int occupation;


	bool _isHighlighted;


	bool checkMill();

private:

	int _width;
	bool _isOccupied;
	bool _isInteractable;
	bool _isMouseOver;
	bool _isPressed;

	int horizontalMillCount(int currentMill);

};