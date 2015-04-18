#pragma once

#include "../Subsystem.h"

#include "component/ControllableComponent.h"

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