#include "SSLevel.h"

#include "../../EntityFactory.h"

#define LEVEL_WALL_COLOR_ROCK	sf::Color::Black

SSLevel& SSLevel::GetInstance( )
{
    static SSLevel instance;
    return instance;
}

void SSLevel::Startup( )
{
	m_ActiveLevelIndex = 0;

	m_LevelFolderPaths.push_back( "asset/level/0" );

	this->LoadLevel( m_ActiveLevelIndex );

    Subsystem::Startup();
}

void SSLevel::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSLevel::Update( const float deltaTime )
{
    
}

void SSLevel::LoadLevel( int levelIndex ) {
	const std::string& levelFolderPath = m_LevelFolderPaths[ levelIndex % m_LevelFolderPaths.size() ];

	sf::Image wallMap;
	wallMap.loadFromFile( levelFolderPath + "/wall.png" );
	m_LevelSize = glm::vec2(wallMap.getSize().x, wallMap.getSize().y);

	
	sf::Color	texelColour;

	for ( unsigned int y = 0; y < m_LevelSize.y; ++y ) {
		for ( unsigned int x = 0; x < m_LevelSize.x; ++x ) {
			texelColour = wallMap.getPixel( x, y );

			if ( texelColour == LEVEL_WALL_COLOR_ROCK ) {
				glm::ivec2 size(1);
				bool freeX = true;
				bool freeY = true;

				while ( freeX || freeY ) {
					if ( freeX ) {
						if ( x + size.x >= m_LevelSize.x ) {
							freeX = false;
						}

						if ( freeX ) {
							for ( unsigned int dy = y; dy <= y + size.y - 1; ++dy ) {
								texelColour = wallMap.getPixel( x + size.x, dy );
								if ( texelColour != LEVEL_WALL_COLOR_ROCK ) {
									freeX = false;
									break;
								}
							}
						}
					}

					if ( freeY ) {
						if ( y + size.y >= m_LevelSize.y ) {
							freeY = false;
						}

						if ( freeY ) {
							for ( unsigned int dx = x; dx <= x + size.x - 1; ++dx ) {
								texelColour = wallMap.getPixel( dx, y + size.y );
								if ( texelColour != LEVEL_WALL_COLOR_ROCK ) {
									freeY = false;
									break;
								}
							}
						}
					}

					if ( freeX && freeY && wallMap.getPixel( x + size.x, y + size.y ) != LEVEL_WALL_COLOR_ROCK ) {
						freeY = false;
						++size.x;
					} else {
						if ( freeX ) {
							++size.x;
						}
						if ( freeY ) {
							++size.y;
						}
					}
				}
				EntityFactory::CreateObstacle( glm::vec2( x, y ), size );
				for ( unsigned int dy = y; dy < y + size.y; ++dy ) {
					for ( unsigned int dx = x; dx < x + size.x; ++dx ) {
						wallMap.setPixel( dx, dy, sf::Color( 255, 255, 255, 0 ) );
					}
				}
			}
		}
	}
}