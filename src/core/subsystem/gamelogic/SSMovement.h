#pragma once

#include "../Subsystem.h"
// Conveniency access function
#define g_SSMovement SSMovement::GetInstance()

class SSMovement : public Subsystem
{
public:
    static SSMovement& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

private:
    // No external instancing allowed
    SSMovement ( ) : Subsystem( "Movement" ) {}
    SSMovement ( const SSMovement & rhs );
    ~SSMovement ( ) {};
    SSMovement& operator=(const SSMovement & rhs);
};