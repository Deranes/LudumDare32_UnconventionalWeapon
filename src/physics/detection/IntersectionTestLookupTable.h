#pragma once

#include "../volume/Volume.h"

typedef bool (*IntersectionTestFunction)( const Volume* aVolume, const Volume* bVolume );

class IntersectionTestLookupTable
{
public:
									IntersectionTestLookupTable();

	IntersectionTestFunction		Fetch( VOLUME_TYPE a, VOLUME_TYPE b );

private:
	static bool						NotImplemented( const Volume* aVolume, const Volume* bVolume );

	IntersectionTestFunction		m_IntersectionTestFunctions[VOLUME_TYPE_SIZE][VOLUME_TYPE_SIZE];
};