#pragma once

#include "Volume.h"

class AABB : public Volume {
public:
	glm::vec2		Min		= glm::vec2( -1.0f );
	glm::vec2		Max		= glm::vec2(  1.0f );

	Volume*			CalculateWorld( const glm::vec2& position ) const override;
	void			CalculateWorld( const glm::vec2& position, Volume* outWorldVolume ) const override;

	VOLUME_TYPE		GetVolumeType() const override;
};