#include "SSFollow.h"

#include <glm/geometric.hpp>
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/FollowComponent.h"
#include "../../component/PlacementComponent.h"
#include "../../component/VelocityComponent.h"

SSFollow& SSFollow::GetInstance( )
{
    static SSFollow instance;
    return instance;
}

void SSFollow::Startup( )
{
    Subsystem::Startup();
}

void SSFollow::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSFollow::Update( const float deltaTime )
{
	EntityMask followFlag		= DenseComponentCollection<FollowComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= followFlag | placementFlag;

	int entityID = 0;
	for ( auto& entityMask : g_EntityManager.GetEntityMasks() )
	{
		if ( ( entityMask & combinedFlag ) == combinedFlag )
		{
			FollowComponent*	followComp		= GetDenseComponent<FollowComponent>( entityID );
			PlacementComponent*	placementComp	= GetDenseComponent<PlacementComponent>( entityID );

			glm::vec2 targetPosition = GetDenseComponent<PlacementComponent>( followComp->TargetEntity )->Position + followComp->Offset;

			if ( entityMask & velocityFlag ) {
				VelocityComponent*	velocityComp	= GetDenseComponent<VelocityComponent>( entityID );

				if ( placementComp->Position != targetPosition ) {
					glm::vec2 targetVelocity = followComp->Acceleration * (targetPosition - placementComp->Position);
					velocityComp->Velocity = 0.5f * (velocityComp->Velocity + targetVelocity);
				}
				placementComp->Position += deltaTime * velocityComp->Velocity;
			} else {
				placementComp->Position = targetPosition;
			}
			
		}
		entityID++;
	}
}