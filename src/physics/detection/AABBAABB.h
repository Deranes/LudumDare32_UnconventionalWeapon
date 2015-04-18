#pragma once

#include "../volume/Volume.h"
#include "CollisionResult.h"

namespace IntersectionTest
{
	void AABBAABB( const Volume* aVolume, const Volume* bVolume, const glm::vec2& aVelocity, const glm::vec2& bVelocity, const float deltaTime, CollisionResult& outResult );
};