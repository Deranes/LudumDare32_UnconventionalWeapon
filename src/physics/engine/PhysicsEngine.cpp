#include "PhysicsEngine.h"

#include "../volume/AABB.h"

PhysicsEngine::~PhysicsEngine() {
	this->Shutdown();
}

void PhysicsEngine::Shutdown() {
	for ( auto& rigidBody : m_RigidBodies ) {
		delete rigidBody;
	}
	m_RigidBodies.clear();
}

void PhysicsEngine::Step( const float deltaTime ) {
	for ( auto& rigidBody : m_RigidBodies ) {
		rigidBody->CalculateWorldVolumes();
		rigidBody->Position += deltaTime * rigidBody->Velocity;
	}
}

IRigidBody* PhysicsEngine::CreateRigidBody() {
	RigidBody* newRigidBody = new RigidBody();
	m_RigidBodies.push_back( newRigidBody );
	return newRigidBody;
}

void PhysicsEngine::CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) {
	AABB* newVolume = new AABB();
	
	newVolume->Min = min;
	newVolume->Max = max;

	static_cast<RigidBody*>( rigidBody )->AddVolume( newVolume );
}