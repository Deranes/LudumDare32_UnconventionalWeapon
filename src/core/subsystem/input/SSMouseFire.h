#pragma once

#include "../Subsystem.h"
// Conveniency access function
#define g_SSMouseFire SSMouseFire::GetInstance()

class SSMouseFire : public Subsystem
{
public:
    static SSMouseFire& GetInstance();
    void Startup( ) override;
    void Shutdown( ) override;
    void Update( const float deltaTime ) override;

private:
    // No external instancing allowed
    SSMouseFire ( ) : Subsystem( "MouseFire" ) {}
    SSMouseFire ( const SSMouseFire & rhs );
    ~SSMouseFire ( ) {};
    SSMouseFire& operator=(const SSMouseFire & rhs);
};