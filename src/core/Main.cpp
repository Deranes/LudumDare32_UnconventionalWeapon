#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "Test window");
	sf::Event event;
	Game game1;
	game1.Initialize(&window);

	sf::Clock gametimer;

	
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