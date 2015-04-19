#pragma once

#include <glm/vec2.hpp>

struct FollowComponent
{
	Entity			TargetEntity;
	glm::vec2		Offset;
	float			Acceleration;
};