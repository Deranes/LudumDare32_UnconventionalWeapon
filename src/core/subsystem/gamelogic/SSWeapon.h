#pragma once

#include "../Subsystem.h"

#include <glm/vec2.hpp>
#include "../../datadriven/ComponentTypes.h"

// Conveniency access function
#define g_SSWeapon SSWeapon::GetInstance()

class SSWeapon : public Subsystem
{
public:
    static SSWeapon& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

	void	Fire( Entity entity, const glm::vec2& direction );

private:
    // No external instancing allowed
    SSWeapon ( ) : Subsystem( "Weapon" ) {}
    SSWeapon ( const SSWeapon & rhs );
    ~SSWeapon ( ) {};
    SSWeapon& operator=(const SSWeapon & rhs);
};