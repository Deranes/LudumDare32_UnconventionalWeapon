#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "datadriven/ComponentTypes.h"

class Game
{
public:
	Game();
	~Game();
	void Initialize(sf::RenderWindow* window);
	void Update(float deltaTime);

private:
	Entity		m_Player;
};