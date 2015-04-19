#include "SSControllable.h"

#include <SFML/Window/Keyboard.hpp>
#include <glm/common.hpp>
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/ControllableComponent.h"
#include "../../component/VelocityComponent.h"

SSControllable& SSControllable::GetInstance()
{
    static SSControllable instance;
    return instance;
}

void SSControllable::Startup()
{
    Subsystem::Startup();
}

void SSControllable::Shutdown()
{
	Subsystem::Shutdown();
}

void SSControllable::Update( const float deltaTime )
{
	EntityMask controllableFlag = DenseComponentCollection<ControllableComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= controllableFlag | velocityFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			ControllableComponent*	controllableComp	= GetDenseComponent<ControllableComponent>( entityID );
			VelocityComponent*		velocityComp		= GetDenseComponent<VelocityComponent>( entityID );

			if ( this->KeyDown( controllableComp->KeyMoveRight ) && velocityComp->Velocity.x < CONTROLLABLE_MAX_SPEED ) {
				velocityComp->Velocity.x = glm::min( CONTROLLABLE_MAX_SPEED, velocityComp->Velocity.x + deltaTime * CONTROLLABLE_ACCELERATION );
				velocityComp->Velocity.x = glm::max( 0.0f, velocityComp->Velocity.x );
			} else if ( this->KeyDown( controllableComp->KeyMoveLeft ) && velocityComp->Velocity.x > -CONTROLLABLE_MAX_SPEED ) {
				velocityComp->Velocity.x = glm::max( -CONTROLLABLE_MAX_SPEED, velocityComp->Velocity.x - deltaTime * CONTROLLABLE_ACCELERATION );
				velocityComp->Velocity.x = glm::min( 0.0f, velocityComp->Velocity.x );
			} else {
				float length = glm::abs( velocityComp->Velocity.x );
				if ( length < deltaTime * CONTROLLABLE_DEACCELERATION ) {
					velocityComp->Velocity.x = 0.0f;
				} else {
					velocityComp->Velocity.x -= glm::sign( velocityComp->Velocity.x ) * deltaTime * CONTROLLABLE_DEACCELERATION;
				}
			}
			
			if ( this->KeyDown( controllableComp->KeyJump ) || this->KeyDown( controllableComp->KeyJumpSecond ) ) {
				velocityComp->Velocity.y = -CONTROLLABLE_JUMP_SPEED;
			}
		}
		entityID++;
	}
}

bool SSControllable::KeyDown( const Keybinding& key )
{
	return sf::Keyboard::isKeyPressed( key.first ) || sf::Keyboard::isKeyPressed( key.second );
}