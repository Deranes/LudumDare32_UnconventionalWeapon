#include "RigidBody.h"

const glm::vec2& RigidBody::GetPosition() const {
	return this->Position;
}

const glm::vec2& RigidBody::GetVelocity() const {
	return this->Velocity;
}

void RigidBody::SetPosition( const glm::vec2& newPosition ) {
	this->Position = newPosition;
}

void RigidBody::SetVelocity( const glm::vec2& newVelocity ) {
	this->Velocity = newVelocity;
}