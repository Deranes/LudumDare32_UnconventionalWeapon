#pragma once

#include "../Subsystem.h"
// Conveniency access function
#define g_SSPhysics SSPhysics::GetInstance()

class SSPhysics : public Subsystem
{
public:
    static SSPhysics& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

private:
    // No external instancing allowed
    SSPhysics ( ) : Subsystem( "Physics" ) {}
    SSPhysics ( const SSPhysics & rhs );
    ~SSPhysics ( ) {};
    SSPhysics& operator=(const SSPhysics & rhs);
};