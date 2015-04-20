#pragma once

#include "../IPhysicsEngine.h"

#include "../body/RigidBody.h"
#include "../detection/IntersectionTestLookupTable.h"

#include <vector>

class PhysicsEngine : public IPhysicsEngine {
public:
										~PhysicsEngine();

	void								Shutdown() override;

	void								Step( const float deltaTime ) override;

	IRigidBody*							CreateRigidBody( MotionType motionType ) override;
	void								CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) override;

	const std::vector<CollisionInfo>&	GetCollisions() override;	

	void								SetNumberOfGroups( int newSize );
	void								SetGroupInteraction( int groupA, int groupB, bool interact );

private:
	std::vector<RigidBody*>				m_RigidBodies;
	IntersectionTestLookupTable			m_TestLookup;
	std::vector<std::vector<bool>>		m_InteractionLookup;
	std::vector<CollisionInfo>			m_Collisions;
};