#include "RigidBody.h"

RigidBody::~RigidBody() {
	for ( auto& localVolume : m_LocalVolumes ) {
		delete localVolume;
	}
	m_LocalVolumes.clear();

	for ( auto& worldVolume : m_WorldVolumes ) {
		delete worldVolume;
	}
	m_WorldVolumes.clear();
}

void RigidBody::AddVolume( const Volume* newVolume ) {
	m_LocalVolumes.push_back( newVolume );
	m_WorldVolumes.push_back( newVolume->CalculateWorld( this->Position ) );
}

void RigidBody::CalculateWorldVolumes()
{
	assert( m_LocalVolumes.size() == m_WorldVolumes.size() );

	for ( int i = 0; i < static_cast<int>(m_LocalVolumes.size()); ++i )
	{
		m_LocalVolumes[i]->CalculateWorld( this->Position, m_WorldVolumes[i] );
	}
}

const glm::vec2& RigidBody::GetPosition() const {
	return this->Position;
}

const glm::vec2& RigidBody::GetVelocity() const {
	return this->Velocity;
}

const std::vector<Volume*> RigidBody::GetWorldVolumes() const {
	return m_WorldVolumes;
}

void RigidBody::SetPosition( const glm::vec2& newPosition ) {
	this->Position = newPosition;
}

void RigidBody::SetVelocity( const glm::vec2& newVelocity ) {
	this->Velocity = newVelocity;
}