#pragma once

#include <glm/vec2.hpp>

struct CollisionResult {
	bool		Intersection	= false;
	float		Time			= 0.0f;
	glm::vec2	NormalOne		= glm::vec2( 0.0f, 1.0f );
	glm::vec2	NormalTwo		= glm::vec2( 0.0f, 1.0f );
};