# MLIN_GAME
Nine men mill in openGL (glut)

Nine men mill created in OpenGL using GLUT. This was a fun project to practice C++ skills.
Board generates the playing area and forwards inputs to the Game Manager. Within the board class, there is a simplified raycast component created to help find neighbor tiles for each tile positions.
Game manager validates player input, displays available moves and invokes input functions on tiles or tile positions.
Tiles are connected in a tree which allows every tile to validate if it is in a mill or not.

There are also mouse hovers implemented for suggesting moves.
