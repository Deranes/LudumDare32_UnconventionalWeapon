#include "AABBAABB.h"

#include <glm/vec4.hpp>
#include <glm/common.hpp>
#include <vector>
#include <algorithm>
#include "../volume/AABB.h"

struct Entry {
	Entry( int index, float time ) {
		this->Index	= index;
		this->Time	= time;
	}

	int		Index	= -1;
	float	Time	= -1.0f;
};

void IntersectionTest::AABBAABB( const Volume* aVolume, const Volume* bVolume, const glm::vec2& aVelocity, const glm::vec2& bVelocity, const float deltaTime, CollisionResult& outResult ) {
	const AABB* a = static_cast<const AABB*>( aVolume );
	const AABB* b = static_cast<const AABB*>( bVolume );

	const glm::vec2 relativeVelocity = aVelocity - bVelocity;

	std::vector<Entry> intersectionTimes;
	intersectionTimes.reserve( 4 );
	intersectionTimes.push_back( Entry( 0, relativeVelocity.x == 0.0f ? -1.0f : (b->Min.x - a->Max.x) / relativeVelocity.x ) );
	intersectionTimes.push_back( Entry( 1, relativeVelocity.x == 0.0f ? -1.0f : (b->Max.x - a->Min.x) / relativeVelocity.x ) );
	intersectionTimes.push_back( Entry( 2, relativeVelocity.y == 0.0f ? -1.0f : (b->Min.y - a->Max.y) / relativeVelocity.y ) );
	intersectionTimes.push_back( Entry( 3, relativeVelocity.y == 0.0f ? -1.0f : (b->Max.y - a->Min.y) / relativeVelocity.y ) );

	std::sort( intersectionTimes.begin(), intersectionTimes.end(), [](const Entry& a, const Entry& b) { return a.Time > b.Time; } );
	for ( int i = intersectionTimes.size() - 1; i >= 0; --i ) {
		if ( intersectionTimes[i].Time > 0.0f ) {
			break;
		}

		if ( intersectionTimes[i].Time == 0.0f ) {
			if ( intersectionTimes[i].Index == 0 ) {
				if ( a->Max.x + relativeVelocity.x < b->Min.x ) {
					continue;
				}
			} else if ( intersectionTimes[i].Index == 1 ) {
				if ( a->Min.x + relativeVelocity.x > b->Max.x ) {
					continue;
				}
			} else if ( intersectionTimes[i].Index == 2 ) {
				if ( a->Max.y + relativeVelocity.y < b->Min.y ) {
					continue;
				}
			} else if ( intersectionTimes[i].Index == 3 ) {
				if ( a->Min.y + relativeVelocity.y > b->Max.y ) {
					continue;
				}
			}
		}
		intersectionTimes.erase( intersectionTimes.begin() + i );
	}

	bool intersecting[4];
	intersecting[0] = a->Max.x >= b->Min.x;
	intersecting[1] = a->Min.x <= b->Max.x;
	intersecting[2] = a->Max.y >= b->Min.y;
	intersecting[3] = a->Min.y <= b->Max.y;

	bool fullIntersection = true;
	for ( int i = 0; i < 4; ++i ) {
		if ( !intersecting[i] ) {
			fullIntersection = false;
			break;
		}
	}

	outResult.Time = 0.0f;
	outResult.NormalOne = glm::vec2( 0.0f, 0.0f );

	while ( !fullIntersection && !intersectionTimes.empty() && intersectionTimes.back().Time <= deltaTime ) {
		intersecting[intersectionTimes.back().Index] = !intersecting[intersectionTimes.back().Index];
		outResult.Time = intersectionTimes.back().Time;
		if ( intersectionTimes.back().Index == 0 ) {
			outResult.NormalOne = glm::vec2( -1.0f, 0.0f );
		} else if ( intersectionTimes.back().Index == 1 ) {
			outResult.NormalOne = glm::vec2( 1.0f, 0.0f );
		} else if ( intersectionTimes.back().Index == 2 ) {
			outResult.NormalOne = glm::vec2( 0.0f, -1.0f );
		} else if ( intersectionTimes.back().Index == 3 ) {
			outResult.NormalOne = glm::vec2( 0.0f, 1.0f );
		}
		intersectionTimes.pop_back();

		fullIntersection = true;
		for ( int i = 0; i < 4; ++i ) {
			if ( !intersecting[i] ) {
				fullIntersection = false;
				break;
			}
		}
	}

	outResult.Intersection	= fullIntersection;
	outResult.NormalTwo		= -outResult.NormalOne;
}