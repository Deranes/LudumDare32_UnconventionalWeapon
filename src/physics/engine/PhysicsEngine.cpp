#include "PhysicsEngine.h"

#include "../volume/AABB.h"
#include "glm/geometric.hpp"

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
	m_Collisions.clear();

	for ( auto& rigidBody : m_RigidBodies ) {
		rigidBody->CalculateWorldVolumes();
	}

	for ( auto aBody_it = m_RigidBodies.begin(); aBody_it != m_RigidBodies.end(); ++aBody_it ) {
		for ( auto bBody_it = aBody_it + 1; bBody_it != m_RigidBodies.end(); ++bBody_it ) {
			RigidBody* aBody = (*aBody_it);
			RigidBody* bBody = (*bBody_it);

			if ( !m_InteractionLookup[aBody->m_Group][bBody->m_Group] ) {
				continue;
			}

			if ( aBody->m_MotionType != MotionType::PhysicsDriven && bBody->m_MotionType != MotionType::PhysicsDriven ) {
				continue;
			}

			// TODOOE: Don't assume that there is only one volume for each rigid body.
			if ( aBody->GetWorldVolumes().empty() || bBody->GetWorldVolumes().empty() ) {
				continue;
			}

			Volume* aVolume = aBody->GetWorldVolumes()[0];
			Volume* bVolume = bBody->GetWorldVolumes()[0];

			IntersectionTestFunction intersectionTestFunction = m_TestLookup.Fetch( aVolume->GetVolumeType(), bVolume->GetVolumeType() );

			CollisionResult result;
			(*intersectionTestFunction)( aVolume, bVolume, aBody->m_Velocity, bBody->m_Velocity, deltaTime, result );

			if ( result.Intersection ) {
				m_Collisions.push_back( CollisionInfo( aBody->m_UserData, bBody->m_UserData ) );
				aBody->m_Collisions.push_back( Collision( result.Time, result.NormalOne ) );
				bBody->m_Collisions.push_back( Collision( result.Time, result.NormalTwo ) );
			}
		}
	}

	for ( auto& rigidBody : m_RigidBodies ) {
		if ( rigidBody->m_MotionType == MotionType::PhysicsDriven && !rigidBody->m_Collisions.empty() ) {
			float earliestCollisionTime = deltaTime;

			glm::vec2 newVelocity = rigidBody->m_Velocity;

			for ( auto& collision : rigidBody->m_Collisions ) {
				if ( collision.Time < earliestCollisionTime ) {
					earliestCollisionTime = collision.Time;
				}

				float projDist = glm::dot( collision.Normal, newVelocity );
				newVelocity -= projDist * collision.Normal;
				rigidBody->m_Position += 0.01f * collision.Normal;
			}

			rigidBody->m_Position += earliestCollisionTime * rigidBody->m_Velocity;

			rigidBody->m_Velocity	= newVelocity;
			rigidBody->m_Position += (deltaTime - earliestCollisionTime) * newVelocity;
		} else {
			rigidBody->m_Position += deltaTime * rigidBody->m_Velocity;
		}

		rigidBody->m_Collisions.clear();
	}
}

IRigidBody* PhysicsEngine::CreateRigidBody( MotionType motionType ) {
	RigidBody* newRigidBody = new RigidBody();
	newRigidBody->SetMotionType( motionType );
	m_RigidBodies.push_back( newRigidBody );
	return newRigidBody;
}

void PhysicsEngine::CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) {
	AABB* newVolume = new AABB();
	
	newVolume->Min = min;
	newVolume->Max = max;

	static_cast<RigidBody*>( rigidBody )->AddVolume( newVolume );
}

const std::vector<CollisionInfo>& PhysicsEngine::GetCollisions() {
	return m_Collisions;
}

void PhysicsEngine::SetNumberOfGroups( int newSize ) {
	m_InteractionLookup.resize( newSize );
	for ( int y = 0; y < newSize; ++y ) {
		m_InteractionLookup[y].resize( newSize );
	}
}

void PhysicsEngine::SetGroupInteraction( int groupA, int groupB, bool interact ) {
	m_InteractionLookup[groupA][groupB] = interact;
	m_InteractionLookup[groupB][groupA] = interact;
}