#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "datadriven/ComponentTypes.h"

#define ENTITY_FACTORY_PLAYER_SIZE	1.0f

class EntityFactory
{
	public:
		static Entity CreatePlayer( const glm::vec2& position, const sf::Color& color );
	private:
};
