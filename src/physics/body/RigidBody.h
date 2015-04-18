#pragma once

#include "../IRigidBody.h"

#include "../volume/Volume.h"

struct Collision {
	Collision( float time, const glm::vec2& normal ) {
		this->Time		= time;
		this->Normal	= normal;
	}

	float		Time;
	glm::vec2	Normal;
};

class RigidBody : public IRigidBody {
public:
								~RigidBody() override;

	void						AddVolume( const Volume* newVolume );
	void						CalculateWorldVolumes();

	const glm::vec2&			GetPosition() const override;
	const glm::vec2&			GetVelocity() const override;
	const std::vector<Volume*>	GetWorldVolumes() const;

	void						SetPosition( const glm::vec2& newPosition ) override;
	void						SetVelocity( const glm::vec2& newVelocity ) override;
	void						SetMotionType( const MotionType newMotionType ) override;

	glm::vec2					m_Position;
	glm::vec2					m_Velocity;
	MotionType					m_MotionType;
	std::vector<Collision>		m_Collisions;

private:
	std::vector<const Volume*>	m_LocalVolumes;
	std::vector<Volume*>		m_WorldVolumes;
};