#pragma once

#include "IRigidBody.h"

#define g_PhysicsEngine IPhysicsEngine::GetInstance()

struct CollisionInfo {
	CollisionInfo( UserData aUserData, UserData bUserData ) {
		A_UserData = aUserData;
		B_UserData = bUserData;
	}

	UserData	A_UserData;
	UserData	B_UserData;
};

class IPhysicsEngine {
public:
	static IPhysicsEngine&						GetInstance();

	virtual void								Shutdown() = 0;

	virtual void								Step( const float deltaTime ) = 0;

	virtual IRigidBody*							CreateRigidBody( MotionType motionType ) = 0;
	virtual void								CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) = 0;

	virtual const std::vector<CollisionInfo>&	GetCollisions() = 0;

	virtual void								SetNumberOfGroups( int newSize ) = 0;
	virtual void								SetGroupInteraction( int groupA, int groupB, bool interact ) = 0;
};