#pragma once
#include <string>
#include "LevelData.h"

#define g_Level Level::GetInstance()

class Level
{
public:
	static Level& GetInstance();

	bool Load( const char * levelPath );

	LevelData& GetLevelData();

	ENTITY_TYPE GetTypeAt( unsigned int x, unsigned int y );

private:
	LevelData m_LevelData;
	int* m_Level = nullptr;

};