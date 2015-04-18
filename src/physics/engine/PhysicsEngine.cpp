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
		rigidBody->Derp = false;
	}

	for ( auto aBody_it = m_RigidBodies.begin(); aBody_it != m_RigidBodies.end(); ++aBody_it ) {
		for ( auto bBody_it = aBody_it + 1; bBody_it != m_RigidBodies.end(); ++bBody_it ) {
			RigidBody* aBody = (*aBody_it);
			RigidBody* bBody = (*bBody_it);

			// TODOOE: Don't assume that there is only one volume for each rigid body.
			if ( aBody->GetWorldVolumes().empty() || bBody->GetWorldVolumes().empty() ) {
				continue;
			}

			Volume* aVolume = aBody->GetWorldVolumes()[0];
			Volume* bVolume = bBody->GetWorldVolumes()[0];

			IntersectionTestFunction intersectionTestFunction = m_TestLookup.Fetch( aVolume->GetVolumeType(), bVolume->GetVolumeType() );
			if ( (*intersectionTestFunction)( aVolume, bVolume ) ) {
				aBody->Derp = true;
				bBody->Derp = true;
			}
		}
	}

	for ( auto& rigidBody : m_RigidBodies ) {
		if ( rigidBody->Derp ) {
			rigidBody->Velocity = glm::vec2( 0.0f );
		}

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