#pragma once

#include "../IRigidBody.h"

class RigidBody : public IRigidBody {
public:
	const glm::vec2&	GetPosition() const override;
	const glm::vec2&	GetVelocity() const override;

	void				SetPosition( const glm::vec2& newPosition ) override;
	void				SetVelocity( const glm::vec2& newVelocity ) override;

	glm::vec2			Position;
	glm::vec2			Velocity;
};