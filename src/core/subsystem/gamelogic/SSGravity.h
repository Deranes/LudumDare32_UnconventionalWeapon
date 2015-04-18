#pragma once

#include "../Subsystem.h"

#include "component/GravityComponent.h"

// Conveniency access function
#define g_SSGravity SSGravity::GetInstance()

class SSGravity : public Subsystem
{
public:
    static SSGravity&	GetInstance		();
    void				Startup			() override;
    void				Shutdown		() override;
    void				Update			( const float deltaTime ) override;

private:
						// No external instancing allowed
						SSGravity	() : Subsystem( "Gravity" ) {}
						SSGravity	( const SSGravity & rhs );
						~SSGravity	() {};
    SSGravity&			operator=		(const SSGravity & rhs);
};