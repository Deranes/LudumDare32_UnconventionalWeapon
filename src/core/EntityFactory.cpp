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
#include "component/FollowComponent.h"
#include "component/WeaponComponent.h"
#include "component/AimComponent.h"
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

	//VelocityComponent* velocityComp = GetDenseComponent<VelocityComponent>(entity);
	//velocityComp->Velocity = glm::vec2( 1.0f, 400.0f );

	SpriteComponent* spriteComp = GetDenseComponent<SpriteComponent>(entity);
	spriteComp->Sprite.setTexture( g_TextureBank.GetTexture(TEXTURE_HANDLE_PLAYER) );
	spriteComp->Sprite.setColor(color);

	sf::Vector2u spriteSize = spriteComp->Sprite.getTexture()->getSize();
	spriteComp->Sprite.setScale( sf::Vector2f( ENTITY_FACTORY_PLAYER_SIZE_X / spriteSize.x, ENTITY_FACTORY_PLAYER_SIZE_Y / spriteSize.y ) );
	spriteComp->Sprite.setOrigin( sf::Vector2f( 0.5f * spriteSize.x, 0.5f * spriteSize.y ) );

	ControllableComponent* controllableComp = GetDenseComponent<ControllableComponent>(entity);
	controllableComp->KeyMoveLeft	= Keybinding( sf::Keyboard::Left,	sf::Keyboard::A );
	controllableComp->KeyMoveRight	= Keybinding( sf::Keyboard::Right,	sf::Keyboard::D );
	controllableComp->KeyJump		= Keybinding( sf::Keyboard::Up,		sf::Keyboard::W );
	controllableComp->KeyJumpSecond	= Keybinding( sf::Keyboard::Space,	sf::Keyboard::Z );

	PhysicsComponent* physicsComp = GetDenseComponent<PhysicsComponent>(entity);
	physicsComp->RigidBody	= g_PhysicsEngine.CreateRigidBody( MotionType::PhysicsDriven );
	physicsComp->Group		= ENTITY_TYPE_PLAYER;
	physicsComp->RigidBody->SetUserData( entity );
	glm::vec2 halfSize( 0.5f * ENTITY_FACTORY_PLAYER_SIZE_X, 0.5f * ENTITY_FACTORY_PLAYER_SIZE_Y );
	g_PhysicsEngine.CreateCollisionVolumeAABB( physicsComp->RigidBody, -halfSize, halfSize );

	return entity;
}

Entity EntityFactory::CreateWeapon( Entity owner, const glm::vec2& offset ) {
	Entity entity = g_EntityManager.CreateEntity();
	
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PlacementComponent	>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< SpriteComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< VelocityComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< FollowComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< WeaponComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< AimComponent			>() );

	PlacementComponent* placementComp		= GetDenseComponent<PlacementComponent>(entity);
	PlacementComponent* ownerPlacementComp	= GetDenseComponent<PlacementComponent>(owner);
	placementComp->Position	= ownerPlacementComp->Position + offset;

	SpriteComponent* spriteComp = GetDenseComponent<SpriteComponent>(entity);
	spriteComp->Sprite.setTexture( g_TextureBank.GetTexture(TEXTURE_HANDLE_CREATURE) );

	sf::Vector2u spriteSize = spriteComp->Sprite.getTexture()->getSize();
	spriteComp->Sprite.setScale( sf::Vector2f( ENTITY_FACTORY_WEAPON_SIZE_X / spriteSize.x, ENTITY_FACTORY_WEAPON_SIZE_Y / spriteSize.y ) );
	spriteComp->Sprite.setOrigin( sf::Vector2f( 0.5f * spriteSize.x, 0.5f * spriteSize.y ) );

	FollowComponent* followComp = GetDenseComponent<FollowComponent>(entity);
	followComp->TargetEntity	= owner;
	followComp->Offset			= offset;
	followComp->Acceleration	= 60.0f;

	WeaponComponent* weaponComp	= GetDenseComponent<WeaponComponent>(entity);
	weaponComp->CooldownMax		= 0.2f;
	weaponComp->CooldownCurrent	= 0.0f;
	weaponComp->Recoil			= 10.0f;

	AimComponent* aimComp	= GetDenseComponent<AimComponent>(entity);
	aimComp->FireButton		= sf::Mouse::Button::Left;

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
	physicsComp->RigidBody	= g_PhysicsEngine.CreateRigidBody( MotionType::Fixed );
	physicsComp->Group		= ENTITY_TYPE_WALL;
	physicsComp->RigidBody->SetUserData( entity );
	g_PhysicsEngine.CreateCollisionVolumeAABB( physicsComp->RigidBody, glm::vec2( 0.0f ), size );

	return entity;
}

Entity EntityFactory::CreateProjectile( const glm::vec2& position, const glm::vec2& direction ) {
	Entity entity = g_EntityManager.CreateEntity();
	
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PlacementComponent	>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< SpriteComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< GravityComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< VelocityComponent		>() );
	g_EntityManager.AddComponent( entity, GetDenseComponentTypeIndex< PhysicsComponent		>() );

	PlacementComponent* placementComp = GetDenseComponent<PlacementComponent>(entity);
	placementComp->Position	= position;
	placementComp->Rotation = glm::atan( direction.y, direction.x ) * 180.0f / 3.1416f;

	SpriteComponent* spriteComp = GetDenseComponent<SpriteComponent>(entity);
	spriteComp->Sprite.setTexture( g_TextureBank.GetTexture(TEXTURE_HANDLE_PROJECTILE) );

	sf::Vector2u spriteSize = spriteComp->Sprite.getTexture()->getSize();
	spriteComp->Sprite.setScale( sf::Vector2f( ENTITY_FACTORY_PROJECTILE_SIZE_X / spriteSize.x, ENTITY_FACTORY_PROJECTILE_SIZE_Y / spriteSize.y ) );
	spriteComp->Sprite.setOrigin( sf::Vector2f( 0.5f * spriteSize.x, 0.5f * spriteSize.y ) );

	VelocityComponent* velocityComp = GetDenseComponent<VelocityComponent>(entity);
	velocityComp->Velocity = direction * 40.0f;

	PhysicsComponent* physicsComp = GetDenseComponent<PhysicsComponent>(entity);
	physicsComp->RigidBody	= g_PhysicsEngine.CreateRigidBody( MotionType::PhysicsDriven );
	physicsComp->Group		= ENTITY_TYPE_PROJECTILE;
	physicsComp->RigidBody->SetUserData( entity );
	glm::vec2 halfSize( 0.5f * ENTITY_FACTORY_PROJECTILE_SIZE_X, 0.5f * ENTITY_FACTORY_PROJECTILE_SIZE_Y );
	g_PhysicsEngine.CreateCollisionVolumeAABB( physicsComp->RigidBody, -halfSize, halfSize );

	return entity;
}