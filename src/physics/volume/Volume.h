#pragma once

enum VOLUME_TYPE {
	VOLUME_TYPE_CIRCLE,
	VOLUME_TYPE_OBB,
	VOLUME_TYPE_SIZE
};

class Volume {
public:
	virtual VOLUME_TYPE		GetVolumeType() const = 0;
};