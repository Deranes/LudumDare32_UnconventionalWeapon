#pragma once

#include "../IPhysicsEngine.h"

#include "../body/RigidBody.h"

#include <vector>

class PhysicsEngine : public IPhysicsEngine {
public:
							~PhysicsEngine();

	void					Shutdown() override;

	void					Step( const float deltaTime ) override;

	IRigidBody*				CreateRigidBody() override;
	void					CreateCollisionVolumeAABB( IRigidBody* rigidBody, const glm::vec2& min, const glm::vec2& max ) override;

private:
	std::vector<RigidBody*>	m_RigidBodies;
};