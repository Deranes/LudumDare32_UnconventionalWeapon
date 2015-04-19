#pragma once

#include "../Subsystem.h"

#include <glm/vec2.hpp>

// Conveniency access function
#define g_SSLevel SSLevel::GetInstance()

class SSLevel : public Subsystem
{
public:
    static SSLevel& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

private:
    // No external instancing allowed
    SSLevel ( ) : Subsystem( "Level" ) {}
    SSLevel ( const SSLevel & rhs );
    ~SSLevel ( ) {};
    SSLevel& operator=(const SSLevel & rhs);

	void						LoadLevel( int levelIndex );

	int							m_ActiveLevelIndex;
	std::vector<std::string>	m_LevelFolderPaths;
	glm::vec2					m_LevelSize;
};