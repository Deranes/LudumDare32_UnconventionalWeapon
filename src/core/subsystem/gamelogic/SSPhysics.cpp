#include "SSPhysics.h"

#include "../../../physics/IPhysicsEngine.h"
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/PhysicsComponent.h"
#include "../../component/PlacementComponent.h"
#include "../../component/VelocityComponent.h"
#include "../gamelogic/SSKill.h"

SSPhysics& SSPhysics::GetInstance( )
{
    static SSPhysics instance;
    return instance;
}

void SSPhysics::Startup( )
{
	g_PhysicsEngine.SetNumberOfGroups( ENTITY_TYPE_SIZE );

	g_PhysicsEngine.SetGroupInteraction( ENTITY_TYPE_PLAYER, ENTITY_TYPE_WALL, true );
	g_PhysicsEngine.SetGroupInteraction( ENTITY_TYPE_PROJECTILE, ENTITY_TYPE_WALL, true );

    Subsystem::Startup();
}

void SSPhysics::Shutdown( )
{
	g_PhysicsEngine.Shutdown();

    Subsystem::Shutdown();
}

void SSPhysics::Update( const float deltaTime )
{
	EntityMask physicsFlag		= DenseComponentCollection<PhysicsComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= physicsFlag | placementFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			PhysicsComponent*	physicsComp		= GetDenseComponent<PhysicsComponent>( entityID );
			PlacementComponent*	placementComp	= GetDenseComponent<PlacementComponent>( entityID );
			
			physicsComp->RigidBody->SetPosition( placementComp->Position );
			physicsComp->RigidBody->SetGroup( physicsComp->Group );

			if ( entityMask & velocityFlag ) {
				VelocityComponent* velocityComp = GetDenseComponent<VelocityComponent>( entityID );
				physicsComp->RigidBody->SetVelocity( velocityComp->Velocity );
			}
		}
		entityID++;
	}

	g_PhysicsEngine.Step( deltaTime );

	entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			PhysicsComponent*	physicsComp		= GetDenseComponent<PhysicsComponent>( entityID );
			PlacementComponent*	placementComp	= GetDenseComponent<PlacementComponent>( entityID );
			
			placementComp->Position = physicsComp->RigidBody->GetPosition();

			if ( entityMask & velocityFlag ) {
				VelocityComponent* velocityComp = GetDenseComponent<VelocityComponent>( entityID );
				velocityComp->Velocity = physicsComp->RigidBody->GetVelocity();
			}
		}
		entityID++;
	}

	for ( auto& collision : g_PhysicsEngine.GetCollisions() ) {
		EntityMask entityMask = g_EntityManager.GetEntityMask( collision.A_UserData );
		if ( entityMask & physicsFlag ) {
			if ( GetDenseComponent<PhysicsComponent>(collision.A_UserData)->Group == ENTITY_TYPE_PROJECTILE ) {
				g_SSKill.KillEntity( collision.A_UserData );
			}
		}

		entityMask = g_EntityManager.GetEntityMask( collision.B_UserData );
		if ( entityMask & physicsFlag ) {
			if ( GetDenseComponent<PhysicsComponent>(collision.B_UserData)->Group == ENTITY_TYPE_PROJECTILE ) {
				g_SSKill.KillEntity( collision.B_UserData );
			}
		}
	}
}