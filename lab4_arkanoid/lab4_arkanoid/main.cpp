#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;


int main() {
	RenderWindow window(sf::VideoMode(600, 400), "Arkanoid");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		

		window.clear(sf::Color::White);


		CircleShape s(200.f);
		
		auto circle_shape = s.getGlobalBounds();
		
		RectangleShape z({ 10,10 });
		auto square_shape = z.getGlobalBounds();
		z.setFillColor(sf::Color::Blue);

		s.setFillColor(sf::Color::Red);
		window.draw(z);
		window.draw(s);
		if (square_shape.intersects(circle_shape)) {
			std::cout << "pog\n";
		}
		window.display();
	}
	return 0;
}



//sf::Text text;

//sf::Font font;
//font.loadFromFile("Thanks Autumn.ttf");
//
//// select the font
//text.setFont(font); // font is a sf::Font
//
//// set the string to display
//text.setString("Points: 321");
//
//// set the character size
//text.setCharacterSize(24); // in pixels, not points!
//
//// set the color
//text.setFillColor(sf::Color::Red);
//
//// set the text style
//text.setStyle(sf::Text::Bold);
//
//auto win_sz = window.getSize().x;
//
//text.setPosition({ 264.f,0 });
//
//// inside the main loop, between window.clear() and window.display()
//window.draw(text);
