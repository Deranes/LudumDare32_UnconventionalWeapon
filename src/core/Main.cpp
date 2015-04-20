#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1280, 720), "Test window");
	sf::Event event;
	Game game1;
	game1.Initialize(&window);

	sf::Clock gametimer;
	window.setMouseCursorVisible( false );

	bool paused = false;
	
	while (window.isOpen()){
		while (window.pollEvent(event)){ 
			if (event.type == sf::Event::Closed){
				window.close();
			}

			if ( event.type == sf::Event::LostFocus ) {
				paused = true;
			}

			if ( event.type == sf::Event::GainedFocus ) {
				paused = false;
			}
		}

		float dt = glm::min( 0.033f, gametimer.restart().asSeconds() );
		if ( !paused ) {
			window.clear();
			game1.Update(dt);
			window.display();
		}
	}
	return 0;
}