#pragma once

#include "IRigidBody.h"

#define g_PhysicsEngine IPhysicsEngine::GetInstance()

class IPhysicsEngine {
public:
	static IPhysicsEngine&	GetInstance();

	virtual void			Shutdown() = 0;

	virtual void			Step( const float deltaTime ) = 0;

	virtual IRigidBody*		CreateRigidBody( MotionType motionType ) = 0;
	virtual void			CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) = 0;
};