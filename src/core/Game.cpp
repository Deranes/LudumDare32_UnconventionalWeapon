#include "Game.h"
#include <stdio.h> //printf
#include "subsystem/SubsystemManager.h"
#include "EntityFactory.h"
#include "datadriven/EntityManager.h"
#include "datadriven/CollectionFactory.h"
#include "component/SpriteComponent.h"
#include "component/PlacementComponent.h"
#include "component/ControllableComponent.h"
#include "component/GravityComponent.h"
#include "component/VelocityComponent.h"
#include "component/PhysicsComponent.h"
#include "component/FollowComponent.h"
#include "../gfx/TextureBank.h"
#include "subsystem/gfx/SSRender.h"

Game::Game(){
	
}

Game::~Game(){
	g_SubsystemManager.Shutdown();
}

//load textures and audio
void Game::Initialize(sf::RenderWindow* window){
	g_TextureBank.Initialize();

	std::vector<BaseCollection*>* collections = GetCollections<
													SpriteComponent,
													PlacementComponent,
													ControllableComponent,
													GravityComponent,
													VelocityComponent,
													PhysicsComponent,
													FollowComponent
													>();

	g_EntityManager.SetCollectionVector(collections);

	g_SubsystemManager.Startup();

	m_Player = EntityFactory::CreatePlayer( glm::vec2( 2.0f, 8.0f ), sf::Color::White );
	EntityFactory::CreateWeapon( m_Player, glm::vec2( 0.0f, - 1.5f ) );

	g_SSRender.SetWindow(window);
	g_SSRender.SetTargetEntity(m_Player);
}

//update game state
void Game::Update(float deltaTime){
	g_SubsystemManager.Update(deltaTime);
}