#pragma once

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "datadriven/ComponentTypes.h"

#define ENTITY_FACTORY_PLAYER_SIZE_X		0.95f
#define ENTITY_FACTORY_PLAYER_SIZE_Y		1.70f
#define ENTITY_FACTORY_WEAPON_SIZE_X		0.50f
#define ENTITY_FACTORY_WEAPON_SIZE_Y		0.50f
#define ENTITY_FACTORY_PROJECTILE_SIZE_X	0.30f
#define ENTITY_FACTORY_PROJECTILE_SIZE_Y	0.30f

class EntityFactory
{
	public:
		static Entity CreatePlayer( const glm::vec2& position, const sf::Color& color );
		static Entity CreateWeapon( Entity owner, const glm::vec2& offset );
		static Entity CreateObstacle( const glm::vec2& position, const glm::vec2& size );
		static Entity CreateProjectile( const glm::vec2& position, const glm::vec2& direction );
	private:
};
