#include "SSGravity.h"

#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/GravityComponent.h"
#include "../../component/VelocityComponent.h"

SSGravity& SSGravity::GetInstance( )
{
    static SSGravity instance;
    return instance;
}

void SSGravity::Startup( )
{
    Subsystem::Startup();
}

void SSGravity::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSGravity::Update( const float deltaTime )
{
	EntityMask gravityFlag		= DenseComponentCollection<GravityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= gravityFlag | velocityFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			GravityComponent*		gravityComp		= GetDenseComponent<GravityComponent>( entityID );
			VelocityComponent*		velocityComp	= GetDenseComponent<VelocityComponent>( entityID );
			
			velocityComp->Velocity += deltaTime * gravityComp->GravitationalAcceleration;
		}
		entityID++;
	}
}