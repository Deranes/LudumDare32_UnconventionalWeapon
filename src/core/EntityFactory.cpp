#include "EntityFactory.h"
#include <bitset>
#include "datadriven/DenseComponentCollection.h"
#include "datadriven/EntityManager.h"
#include "component/PlacementComponent.h"
#include "component/SpriteComponent.h"
#include "component/ControllableComponent.h"
#include "component/GravityComponent.h"
#include "component/VelocityComponent.h"
#include "component/PhysicsComponent.h"
#include "../gfx/TextureBank.h"
#include "../physics/IPhysicsEngine.h"


Entity EntityFactory::CreatePlayer( const glm::vec2& position, const sf::Color& color ) {
	Entity entity = g_EntityManager.CreateEntity();
	
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PlacementComponent	>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< SpriteComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< ControllableComponent	>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< GravityComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< VelocityComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PhysicsComponent		>() );

	PlacementComponent* placementComp = GetDenseComponent<PlacementComponent>(entity);
	placementComp->Position	= position;

	SpriteComponent* spriteComp = GetDenseComponent<SpriteComponent>(entity);
	spriteComp->Sprite.setTexture( g_TextureBank.GetTexture(TEXTURE_HANDLE_PLAYER) );
	spriteComp->Sprite.setColor(color);

	sf::Vector2u spriteSize = spriteComp->Sprite.getTexture()->getSize();
	spriteComp->Sprite.setScale( sf::Vector2f( ENTITY_FACTORY_PLAYER_SIZE / spriteSize.x, ENTITY_FACTORY_PLAYER_SIZE / spriteSize.y ) );
	spriteComp->Sprite.setOrigin( sf::Vector2f( 0.5f * spriteSize.x, 0.5f * spriteSize.y ) );

	PhysicsComponent* physicsComp = GetDenseComponent<PhysicsComponent>(entity);
	physicsComp->RigidBody	= g_PhysicsEngine.CreateRigidBody();
	g_PhysicsEngine.CreateCollisionVolumeAABB( physicsComp->RigidBody, -glm::vec2( 0.5f * ENTITY_FACTORY_PLAYER_SIZE ), glm::vec2( 0.5f * ENTITY_FACTORY_PLAYER_SIZE ) );

	return entity;
}

Entity EntityFactory::CreateObstacle( const glm::vec2& position, const glm::vec2& size ) {
	Entity entity = g_EntityManager.CreateEntity();
	
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PlacementComponent	>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< SpriteComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PhysicsComponent		>() );

	PlacementComponent* placementComp = GetDenseComponent<PlacementComponent>(entity);
	placementComp->Position	= position;

	SpriteComponent* spriteComp = GetDenseComponent<SpriteComponent>(entity);
	spriteComp->Sprite.setTexture( g_TextureBank.GetTexture(TEXTURE_HANDLE_WALL) );

	sf::Vector2u spriteSize = spriteComp->Sprite.getTexture()->getSize();
	spriteComp->Sprite.setScale( sf::Vector2f( size.x / spriteSize.x, size.y / spriteSize.y ) );

	PhysicsComponent* physicsComp = GetDenseComponent<PhysicsComponent>(entity);
	physicsComp->RigidBody	= g_PhysicsEngine.CreateRigidBody();
	g_PhysicsEngine.CreateCollisionVolumeAABB( physicsComp->RigidBody, glm::vec2( 0.0f ), size );

	return entity;
}