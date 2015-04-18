#pragma once

#include <glm/vec2.hpp>

enum VOLUME_TYPE {
	VOLUME_TYPE_CIRCLE,
	VOLUME_TYPE_AABB,
	VOLUME_TYPE_OBB,
	VOLUME_TYPE_SIZE
};

class Volume {
public:
	virtual VOLUME_TYPE	GetVolumeType() const = 0;

	virtual Volume*		CalculateWorld( const glm::vec2& position ) const = 0;
	virtual void		CalculateWorld( const glm::vec2& position, Volume* outWorldVolume ) const = 0;
};