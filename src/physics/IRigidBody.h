#pragma once

#include <glm/vec2.hpp>
#include <vector>

class IRigidBody {
public:
	virtual const glm::vec2&	GetPosition(  ) const = 0;
	virtual const glm::vec2&	GetVelocity(  ) const = 0;

	virtual void				SetPosition( const glm::vec2& newPosition ) = 0;
	virtual void				SetVelocity( const glm::vec2& newVelocity ) = 0;

protected:
	virtual						~IRigidBody() {}
};