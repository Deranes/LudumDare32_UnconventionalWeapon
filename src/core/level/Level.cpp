#include "Level.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>


Level& Level::GetInstance()
{
	static Level instance;
	return instance;
}

LevelData& Level::GetLevelData()
{
	return m_LevelData;
}

bool Level::Load( const char * levelPath )
{
	int* level = new int[m_LevelData.Size.x * m_LevelData.Size.y];

	std::ifstream levelFile( levelPath, std::ios::in );
	int x = 0, y = 0;

	int currentVal = 0;
	while ( levelFile >> currentVal ) 
	{
		if( x >= m_LevelData.Size.x ) 
		{
			x = 0;
			y++;
		}

		level[m_LevelData.Size.x*y + x] = currentVal;
		x++;
	}

	for( int y = 0; y < m_LevelData.Size.y; y++ )
	{
		for( int x = 0; x < m_LevelData.Size.x; x++ )
		{
			std::cout << level[m_LevelData.Size.x*y + x] << " ";
		}
		std::cout << std::endl;
	}
	
	delete level;
	return true;
}

ENTITY_TYPE Level::GetTypeAt( unsigned int x, unsigned int y )
{
	if( m_Level && x < m_LevelData.Size.x && y < m_LevelData.Size.y )
	{
		return static_cast<ENTITY_TYPE>( m_Level[m_LevelData.Size.x*y + x] );
	}
	else
		return ENITY_TYPE_NONE;
}