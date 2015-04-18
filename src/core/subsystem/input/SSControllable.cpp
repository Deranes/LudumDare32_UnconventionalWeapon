#include "SSControllable.h"

#include <SFML/Window/Keyboard.hpp>
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

			if ( this->KeyDown( controllableComp->KeyMoveUp ) )
				velocityComp->Velocity.y = -5.0f;
			else if ( this->KeyDown( controllableComp->KeyMoveDown ) )
				velocityComp->Velocity.y = 5.0f;
			else if ( this->KeyDown( controllableComp->KeyMoveLeft ) )
				velocityComp->Velocity.x = -5.0f;
			else if ( this->KeyDown( controllableComp->KeyMoveRight ) )
				velocityComp->Velocity.x = 5.0f;
		}
		entityID++;
	}
}

bool SSControllable::KeyDown( const Keybinding& key )
{
	return sf::Keyboard::isKeyPressed( key.first ) || sf::Keyboard::isKeyPressed( key.second );
}