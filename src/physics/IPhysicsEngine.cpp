#pragma once

#include "IPhysicsEngine.h"
#include "engine/PhysicsEngine.h"

IPhysicsEngine&	IPhysicsEngine::GetInstance() {
	static PhysicsEngine instance;
	return instance;
}