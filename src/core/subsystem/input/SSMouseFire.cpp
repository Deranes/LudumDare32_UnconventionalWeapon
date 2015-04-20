#include "SSMouseFire.h"

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/AimComponent.h"
#include "../../component/PlacementComponent.h"
#include "../gfx/SSRender.h"
#include "../gamelogic/SSWeapon.h"

SSMouseFire& SSMouseFire::GetInstance( )
{
    static SSMouseFire instance;
    return instance;
}

void SSMouseFire::Startup( )
{
    Subsystem::Startup();
}

void SSMouseFire::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSMouseFire::Update( const float deltaTime )
{
	EntityMask aimFlag			= DenseComponentCollection<AimComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask placementFlag	= DenseComponentCollection<PlacementComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask combinedFlag		= aimFlag | placementFlag;

	int entityID = 0;
	for (auto& entityMask : EntityManager::GetInstance().GetEntityMasks())
	{
		if ( (entityMask & combinedFlag) == combinedFlag )
		{
			AimComponent*		aimComp			= GetDenseComponent<AimComponent>(entityID);
			PlacementComponent*	placementComp	= GetDenseComponent<PlacementComponent>(entityID);

			glm::vec2 mouseWorldPos = g_SSRender.CalculateWorldMousePos();
			glm::vec2 dist = mouseWorldPos - placementComp->Position;
			placementComp->Rotation = glm::atan( dist.y, dist.x ) * 180.0f / 3.1416f;

			if ( sf::Mouse::isButtonPressed( aimComp->FireButton ) ) {
				g_SSWeapon.Fire( entityID, glm::normalize( dist ) );
			}
		}
		entityID++;
	}
}
