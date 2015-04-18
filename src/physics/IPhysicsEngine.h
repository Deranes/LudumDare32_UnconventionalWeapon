#pragma once

#include "IRigidBody.h"

#define g_PhysicsEngine IPhysicsEngine::GetInstance()

class IPhysicsEngine {
public:
	static IPhysicsEngine&	GetInstance();

	virtual void			Shutdown() = 0;

	virtual void			Step( const float deltaTime ) = 0;

	virtual IRigidBody*		CreateRigidBody() = 0;
};