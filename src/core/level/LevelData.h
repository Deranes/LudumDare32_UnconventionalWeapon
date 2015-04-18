#pragma once
#include <glm/glm.hpp>

struct LevelData {
	glm::ivec2 Size = glm::ivec2( 8, 8 );
	glm::ivec2 TileSize = glm::ivec2( 32, 32 );
	float BeatInterval = 0.5f;
};

enum ENTITY_TYPE {
	ENITY_TYPE_NONE = 0,
	ENITY_TYPE_WALL,
	ENITY_TYPE_GUARD,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_WINDOW,
	ENTITY_TYPE_DOOR,
};