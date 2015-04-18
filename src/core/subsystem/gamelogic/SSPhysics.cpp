#include "SSPhysics.h"

#include "../../../physics/IPhysicsEngine.h"
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/PhysicsComponent.h"
#include "../../component/PlacementComponent.h"
#include "../../component/VelocityComponent.h"

SSPhysics& SSPhysics::GetInstance( )
{
    static SSPhysics instance;
    return instance;
}

void SSPhysics::Startup( )
{
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
}