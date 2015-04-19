#pragma once

#include "../Subsystem.h"

#include "component/ControllableComponent.h"

#define CONTROLLABLE_ACCELERATION	30.0f
#define CONTROLLABLE_DEACCELERATION	30.0f
#define CONTROLLABLE_MAX_SPEED		7.0f
#define CONTROLLABLE_JUMP_SPEED		12.0f

// Conveniency access function
#define g_SSControllable SSControllable::GetInstance()

class SSControllable : public Subsystem
{
public:
    static SSControllable&	GetInstance		();
    void					Startup			() override;
    void					Shutdown		() override;
    void					Update			( const float deltaTime ) override;

private:
							// No external instancing allowed
							SSControllable	() : Subsystem( "Controllable" ) {}
							SSControllable	( const SSControllable & rhs );
							~SSControllable	() {};
    SSControllable&			operator=		(const SSControllable & rhs);

	bool					KeyDown			( const Keybinding& key );
};