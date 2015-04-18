#include "AABBAABB.h"

#include "../volume/AABB.h"

bool IntersectionTest::AABBAABB( const Volume* aVolume, const Volume* bVolume ) {
	const AABB* a = static_cast<const AABB*>( aVolume );
	const AABB* b = static_cast<const AABB*>( bVolume );

	return a->Min.y > 16.0f || b->Min.y > 16.0f;
}