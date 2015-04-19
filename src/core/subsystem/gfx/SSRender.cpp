#include "SSRender.h"

#include <glm/geometric.hpp>
#include "datadriven/DenseComponentCollection.h"
#include "datadriven/EntityManager.h"
#include "component/SpriteComponent.h"
#include "component/PlacementComponent.h"

SSRender& SSRender::GetInstance()
{
	static SSRender instance;
	return instance;
}

void SSRender::Startup()
{
	m_ScreenSize = glm::vec2( 32.0f, 18.0f );
}

void SSRender::Shutdown()
{
	
}

void SSRender::Update( const float deltaTime )
{
	EntityMask spriteFlag		= DenseComponentCollection<SpriteComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= spriteFlag | placementFlag;

	glm::vec2 targetPosition = GetDenseComponent<PlacementComponent>( m_TargetEntity )->Position;
	m_PrevTargetPosition = targetPosition;

	m_Position = 0.9f * m_Position + 0.1f * targetPosition;
	m_Position.x = glm::max( m_BoundsMin.x + 0.5f * m_ScreenSize.x, m_Position.x );
	m_Position.y = glm::max( m_BoundsMin.y + 0.5f * m_ScreenSize.y, m_Position.y );
	m_Position.x = glm::min( m_BoundsMax.x - 0.5f * m_ScreenSize.x, m_Position.x );
	m_Position.y = glm::min( m_BoundsMax.y - 0.5f * m_ScreenSize.y, m_Position.y );

	sf::View view(sf::FloatRect(m_Position.x - 0.5f * m_ScreenSize.x, m_Position.y - 0.5f * m_ScreenSize.y, m_ScreenSize.x, m_ScreenSize.y));
	m_Window->setView( view );

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
	m_Window = window;
}

void SSRender::SetTargetEntity( Entity newTargetEntity ) {
	m_TargetEntity = newTargetEntity;
}

void SSRender::SetBounds( const glm::vec2& min, const glm::vec2& max ) {
	m_BoundsMin = min;
	m_BoundsMax = max;
}