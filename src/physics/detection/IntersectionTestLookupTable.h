#pragma once

#include "../volume/Volume.h"
#include "CollisionResult.h"

typedef void (*IntersectionTestFunction)( const Volume* aVolume, const Volume* bVolume, const glm::vec2& aVelocity, const glm::vec2& bVelocity, const float deltaTime, CollisionResult& outResult );

class IntersectionTestLookupTable
{
public:
									IntersectionTestLookupTable();

	IntersectionTestFunction		Fetch( VOLUME_TYPE a, VOLUME_TYPE b );

private:
	static void						NotImplemented( const Volume* aVolume, const Volume* bVolume, const glm::vec2& aVelocity, const glm::vec2& bVelocity, const float deltaTime, CollisionResult& outResult );

	IntersectionTestFunction		m_IntersectionTestFunctions[VOLUME_TYPE_SIZE][VOLUME_TYPE_SIZE];
};