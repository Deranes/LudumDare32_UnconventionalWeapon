#include "SSMovement.h"

#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/PlacementComponent.h"
#include "../../component/VelocityComponent.h"

SSMovement& SSMovement::GetInstance( )
{
    static SSMovement instance;
    return instance;
}

void SSMovement::Startup( )
{
    Subsystem::Startup();
}

void SSMovement::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSMovement::Update( const float deltaTime )
{
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= placementFlag | velocityFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			PlacementComponent*		placementComp	= GetDenseComponent<PlacementComponent>( entityID );
			VelocityComponent*		velocityComp	= GetDenseComponent<VelocityComponent>( entityID );
			
			placementComp->Position += deltaTime * velocityComp->Velocity;
		}
		entityID++;
	}
}