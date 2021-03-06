#include "IntersectionTestLookupTable.h"

#include "AABBAABB.h"

IntersectionTestLookupTable::IntersectionTestLookupTable()
{
	m_IntersectionTestFunctions[ VOLUME_TYPE_OBB		][ VOLUME_TYPE_OBB			] = &NotImplemented;
	m_IntersectionTestFunctions[ VOLUME_TYPE_OBB		][ VOLUME_TYPE_AABB			] = &NotImplemented;
	m_IntersectionTestFunctions[ VOLUME_TYPE_OBB		][ VOLUME_TYPE_CIRCLE		] = &NotImplemented;
	
	m_IntersectionTestFunctions[ VOLUME_TYPE_AABB		][ VOLUME_TYPE_OBB			] = &NotImplemented;
	m_IntersectionTestFunctions[ VOLUME_TYPE_AABB		][ VOLUME_TYPE_AABB			] = &IntersectionTest::AABBAABB;
	m_IntersectionTestFunctions[ VOLUME_TYPE_AABB		][ VOLUME_TYPE_CIRCLE		] = &NotImplemented;
	
	m_IntersectionTestFunctions[ VOLUME_TYPE_CIRCLE		][ VOLUME_TYPE_OBB			] = &NotImplemented;
	m_IntersectionTestFunctions[ VOLUME_TYPE_CIRCLE		][ VOLUME_TYPE_AABB			] = &NotImplemented;
	m_IntersectionTestFunctions[ VOLUME_TYPE_CIRCLE		][ VOLUME_TYPE_CIRCLE		] = &NotImplemented;
}

IntersectionTestFunction IntersectionTestLookupTable::Fetch( VOLUME_TYPE a, VOLUME_TYPE b )
{
	return m_IntersectionTestFunctions[a][b];
}

void IntersectionTestLookupTable::NotImplemented( const Volume* aVolume, const Volume* bVolume, const glm::vec2& aVelocity, const glm::vec2& bVelocity, const float deltaTime, CollisionResult& outResult )
{
	outResult.Intersection = false;
}