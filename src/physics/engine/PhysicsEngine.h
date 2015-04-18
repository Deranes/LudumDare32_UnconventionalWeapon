#pragma once

#include "../IPhysicsEngine.h"

#include "../body/RigidBody.h"

#include <vector>

class PhysicsEngine : public IPhysicsEngine {
public:
	void					Shutdown() override;

	void					Step( const float deltaTime ) override;

	IRigidBody*				CreateRigidBody() override;

private:
	std::vector<RigidBody*>	m_RigidBodies;
};