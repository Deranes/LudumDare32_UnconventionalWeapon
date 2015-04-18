#include "SSControllable.h"

#include <SFML/Window/Keyboard.hpp>
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/ControllableComponent.h"
#include "../../component/PlacementComponent.h"

SSControllable& SSControllable::GetInstance()
{
    static SSControllable instance;
    return instance;
}

void SSControllable::Startup()
{
	m_BeatTimer = SS_CONTROLLABLE_TIME_BETWEEN_ACTIONS;

    Subsystem::Startup();
}

void SSControllable::Shutdown()
{
	Subsystem::Shutdown();
}

void SSControllable::Update( const float deltaTime )
{
	m_BeatTimer -= deltaTime;
	if ( m_BeatTimer > 0.0f )
	{
		return;
	}

	m_BeatTimer = SS_CONTROLLABLE_TIME_BETWEEN_ACTIONS;

	EntityMask controllableFlag = DenseComponentCollection<ControllableComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= controllableFlag | placementFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			ControllableComponent*	controllableComp	= GetDenseComponent<ControllableComponent>( entityID );
			PlacementComponent*		placementComp		= GetDenseComponent<PlacementComponent>( entityID );

			if ( this->KeyDown( controllableComp->KeyMoveUp ) )
				placementComp->Position.y--;
			else if ( this->KeyDown( controllableComp->KeyMoveDown ) )
				placementComp->Position.y++;
			else if ( this->KeyDown( controllableComp->KeyMoveLeft ) )
				placementComp->Position.x--;
			else if ( this->KeyDown( controllableComp->KeyMoveRight ) )
				placementComp->Position.x++;
		}
		entityID++;
	}
}

bool SSControllable::KeyDown( const Keybinding& key )
{
	return sf::Keyboard::isKeyPressed( key.first ) || sf::Keyboard::isKeyPressed( key.second );
}