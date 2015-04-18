#include "PhysicsEngine.h"

void PhysicsEngine::Shutdown() {
	for ( auto& rigidBody : m_RigidBodies ) {
		delete rigidBody;
	}
	m_RigidBodies.clear();
}

void PhysicsEngine::Step( const float deltaTime ) {
	for ( auto& rigidBody : m_RigidBodies ) {
		rigidBody->Position += deltaTime * rigidBody->Velocity;
	}
}

IRigidBody* PhysicsEngine::CreateRigidBody() {
	RigidBody* newRigidBody = new RigidBody();
	m_RigidBodies.push_back( newRigidBody );
	return newRigidBody;
}