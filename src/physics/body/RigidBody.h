#pragma once

#include "../IRigidBody.h"

#include "../volume/Volume.h"

class RigidBody : public IRigidBody {
public:
								~RigidBody() override;

	void						AddVolume( const Volume* newVolume );
	void						CalculateWorldVolumes();

	const glm::vec2&			GetPosition() const override;
	const glm::vec2&			GetVelocity() const override;

	void						SetPosition( const glm::vec2& newPosition ) override;
	void						SetVelocity( const glm::vec2& newVelocity ) override;

	glm::vec2					Position;
	glm::vec2					Velocity;

private:
	std::vector<const Volume*>	m_LocalVolumes;
	std::vector<Volume*>		m_WorldVolumes;
};