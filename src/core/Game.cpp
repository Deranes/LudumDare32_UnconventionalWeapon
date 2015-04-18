#include "Game.h"
#include <stdio.h> //printf
#include "subsystem/SubsystemManager.h"
#include "EntityFactory.h"
#include "datadriven/EntityManager.h"
#include "datadriven/CollectionFactory.h"
#include "component/SpriteComponent.h"
#include "component/PlacementComponent.h"
#include "component/ControllableComponent.h"
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
													ControllableComponent
													>();

	g_EntityManager.SetCollectionVector(collections);

	g_SubsystemManager.Startup();
	EntityFactory::CreatePlayer( glm::vec2( 2.0f, 3.0f ), sf::Color::Blue );

	g_SSRender.SetWindow(window);
}

//update game state
void Game::Update(sf::Clock& gameTime){
	float dt = gameTime.restart().asSeconds();

	g_SubsystemManager.Update(dt);
}