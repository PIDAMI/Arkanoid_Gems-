#include "SFML/Graphics.hpp"


using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode(400, 400), "Gems");

	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет окно закрыть?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
		

		

		window.display();
	}
	return 0;
}