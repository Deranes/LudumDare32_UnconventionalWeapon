#pragma once

#include "../../physics/IRigidBody.h"

enum ENTITY_TYPE {
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_PROJECTILE,
	ENTITY_TYPE_WALL,
	ENTITY_TYPE_SIZE	// Keep this last!
};

struct PhysicsComponent
{
	IRigidBody*		RigidBody;
	ENTITY_TYPE		Group;
};