#include <SFML/Graphics.hpp>
#include "Game.h"
#include "level/Level.h"
int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "Test window");
	sf::Event event;
	Game game1;
	game1.Initialize(&window);

	sf::Clock gametimer;

	Level level;
	level.Load( "asset/levels/Level1.conga" ); //congainthedark\bin\windows\Release
	
	while (window.isOpen()){
		while (window.pollEvent(event)){ 
			if (event.type == sf::Event::Closed){
				window.close();
			}
		}
		window.clear();
		game1.Update(gametimer);
		window.display();
	}
	return 0;
}