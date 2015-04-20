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
	m_WorldVolumes.push_back( newVolume->CalculateWorld( m_Position ) );
}

void RigidBody::CalculateWorldVolumes()
{
	assert( m_LocalVolumes.size() == m_WorldVolumes.size() );

	for ( int i = 0; i < static_cast<int>(m_LocalVolumes.size()); ++i )
	{
		m_LocalVolumes[i]->CalculateWorld( m_Position, m_WorldVolumes[i] );
	}
}

const glm::vec2& RigidBody::GetPosition() const {
	return m_Position;
}

const glm::vec2& RigidBody::GetVelocity() const {
	return m_Velocity;
}

const std::vector<Volume*> RigidBody::GetWorldVolumes() const {
	return m_WorldVolumes;
}

void RigidBody::SetPosition( const glm::vec2& newPosition ) {
	m_Position = newPosition;
}

void RigidBody::SetVelocity( const glm::vec2& newVelocity ) {
	m_Velocity = newVelocity;
}

void RigidBody::SetMotionType( const MotionType newMotionType ) {
	m_MotionType = newMotionType;
}

void RigidBody::SetGroup( int newGroupID ) {
	m_Group = newGroupID;
}

void RigidBody::SetUserData( UserData newUserData ) {
	m_UserData = newUserData;
}