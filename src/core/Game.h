#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class Game
{
public:
	Game();
	~Game();
	void Initialize(sf::RenderWindow* window);
	void Update(sf::Clock& gameTime);
private:
};