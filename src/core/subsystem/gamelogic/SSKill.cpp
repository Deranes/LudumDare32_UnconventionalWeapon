#include "SSKill.h"

#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/PhysicsComponent.h"
#include "../../../physics/IPhysicsEngine.h"

SSKill& SSKill::GetInstance( )
{
    static SSKill instance;
    return instance;
}

void SSKill::Startup( )
{
    // Perform Initialization here (Don't forget to set startup order priority!)
    Subsystem::Startup();
}

void SSKill::Shutdown( )
{
    // Perform Cleanup here (Don't forget to set shutdown order priority!)
    Subsystem::Shutdown();
}

void SSKill::Update( const float deltaTime )
{
    // Perform non-simulation update logic here (Don't forget to set update order priority!)
}

void SSKill::KillEntity( Entity entity ) {
	EntityMask entityMask	= g_EntityManager.GetEntityMask( entity );
	EntityMask physicsFlag	= DenseComponentCollection<PhysicsComponent>::GetInstance().GetComponentTypeFlag();

	if ( entityMask & physicsFlag ) {
		PhysicsComponent* physicsComp = GetDenseComponent<PhysicsComponent>( entity );
		g_PhysicsEngine.DestroyRigidBody( physicsComp->RigidBody );
	}

	g_EntityManager.RemoveEntity( entity );
}