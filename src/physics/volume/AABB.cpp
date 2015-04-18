#include "AABB.h"

Volume* AABB::CalculateWorld( const glm::vec2& position ) const {
	Volume* newVolume = new AABB();
	this->CalculateWorld( position, newVolume );
	return newVolume;
}

void AABB::CalculateWorld( const glm::vec2& position, Volume* outWorldVolume ) const {
	AABB* volume = static_cast<AABB*>( outWorldVolume );

	volume->Min = position + this->Min;
	volume->Max = position + this->Max;
}

VOLUME_TYPE AABB::GetVolumeType() const {
	return VOLUME_TYPE_AABB;
}