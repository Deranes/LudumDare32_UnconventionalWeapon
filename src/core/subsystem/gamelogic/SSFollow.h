#pragma once

#include "../Subsystem.h"
// Conveniency access function
#define g_SSFollow SSFollow::GetInstance()

class SSFollow : public Subsystem
{
public:
    static SSFollow& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

private:
    // No external instancing allowed
    SSFollow ( ) : Subsystem( "Follow" ) {}
    SSFollow ( const SSFollow & rhs );
    ~SSFollow ( ) {};
    SSFollow& operator=(const SSFollow & rhs);
};