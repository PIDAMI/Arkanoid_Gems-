#include "SFML/Graphics.hpp"
#include <iostream>
#include "Game.h"

using namespace sf;


int main() {
	srand((unsigned)time(0));
	Game GameLoop;
	GameLoop.Start();


	return 0;
}


