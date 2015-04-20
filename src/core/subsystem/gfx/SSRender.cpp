#include "SSRender.h"

#include <glm/geometric.hpp>
#include "datadriven/DenseComponentCollection.h"
#include "datadriven/EntityManager.h"
#include "component/SpriteComponent.h"
#include "component/PlacementComponent.h"
#include "../../../gfx/TextureBank.h"

SSRender& SSRender::GetInstance()
{
	static SSRender instance;
	return instance;
}

void SSRender::Startup()
{
	m_ScreenSize = glm::vec2( 32.0f, 18.0f );

	m_Crosshair.setTexture( g_TextureBank.GetTexture( TEXTURE_HANDLE_CROSSHAIR ) );
	m_Crosshair.setOrigin( sf::Vector2f( 0.5f * m_Crosshair.getTexture()->getSize().x, 0.5f * m_Crosshair.getTexture()->getSize().y ) );
	m_Crosshair.setScale( RENDER_CROSSHAIR_SIZE / m_Crosshair.getTexture()->getSize().x, RENDER_CROSSHAIR_SIZE / m_Crosshair.getTexture()->getSize().y );
	m_Crosshair.setColor( sf::Color::Red );
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
			glm::ivec2 spriteSize( spriteComp->Sprite.getTexture()->getSize().x, spriteComp->Sprite.getTexture()->getSize().y );
			if ( glm::abs( placementComp->Rotation ) < 90.0f ) {
				spriteComp->Sprite.setTextureRect( sf::IntRect( 0, 0, spriteSize.x, spriteSize.y ) );
				spriteComp->Sprite.setRotation( placementComp->Rotation );
			} else {
				spriteComp->Sprite.setTextureRect( sf::IntRect( spriteSize.x, 0, -spriteSize.x, spriteSize.y ) );
				spriteComp->Sprite.setRotation( 180.0f + placementComp->Rotation );
			}
			m_Window->draw(spriteComp->Sprite);
		}
		entityID++;
	}

	glm::vec2 mouseWorldPos = this->CalculateWorldMousePos();
	m_Crosshair.setPosition( sf::Vector2f( mouseWorldPos.x, mouseWorldPos.y ) );
	m_Window->draw( m_Crosshair );
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

glm::vec2 SSRender::CalculateWorldMousePos() {
	sf::Vector2i mouseScreenPos = sf::Mouse::getPosition( *static_cast<sf::Window*>(m_Window) );
	return (m_Position - 0.5f * m_ScreenSize) + glm::vec2( ( mouseScreenPos.x * m_ScreenSize.x ) / m_Window->getSize().x, ( mouseScreenPos.y * m_ScreenSize.y ) / m_Window->getSize().y );
}