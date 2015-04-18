#include "SSRender.h"

#include "datadriven/DenseComponentCollection.h"
#include "datadriven/EntityManager.h"
#include "component/SpriteComponent.h"
#include "component/PlacementComponent.h"
#include "level/LevelData.h"

SSRender& SSRender::GetInstance()
{
	static SSRender instance;
	return instance;
}

void SSRender::Startup()
{
	
}

void SSRender::Shutdown()
{
	
}

void SSRender::Update( const float deltaTime )
{
	EntityMask spriteFlag		= DenseComponentCollection<SpriteComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= spriteFlag | placementFlag;

	int entityID = 0;
	for (auto& entityMask : EntityManager::GetInstance().GetEntityMasks())
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			SpriteComponent*	spriteComp		= GetDenseComponent<SpriteComponent>( entityID );
			PlacementComponent* placementComp	= GetDenseComponent<PlacementComponent>( entityID );

			spriteComp->Sprite.setPosition( sf::Vector2f( placementComp->Position.x, placementComp->Position.y ) );

			m_Window->draw(spriteComp->Sprite);
		}
		entityID++;
	}
}

void SSRender::SetWindow(sf::RenderWindow* window)
{
	sf::View view(sf::FloatRect(0.0f, 0.0f, 8.0f, 8.0f));	// TODOOE: Get width and height from level.
	window->setView( view );

	m_Window = window;
}