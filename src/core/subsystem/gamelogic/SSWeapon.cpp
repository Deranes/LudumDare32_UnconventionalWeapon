#include "SSWeapon.h"

#include "../../datadriven/DenseComponentCollection.h"
#include "../../datadriven/EntityManager.h"
#include "../../component/WeaponComponent.h"
#include "../../component/VelocityComponent.h"

SSWeapon& SSWeapon::GetInstance( )
{
    static SSWeapon instance;
    return instance;
}

void SSWeapon::Startup( )
{
    Subsystem::Startup();
}

void SSWeapon::Shutdown( )
{
    Subsystem::Shutdown();
}

void SSWeapon::Update( const float deltaTime )
{
	EntityMask weaponFlag = DenseComponentCollection<WeaponComponent>::GetInstance().GetComponentTypeFlag();

	int entityID = 0;
	for (auto& entityMask : EntityManager::GetInstance().GetEntityMasks())
	{
		if ( entityMask & weaponFlag )
		{
			WeaponComponent* weaponComp = GetDenseComponent<WeaponComponent>(entityID);
			weaponComp->CooldownCurrent -= deltaTime;
		}
		entityID++;
	}
}

void SSWeapon::Fire( Entity entity, const glm::vec2& direction ) {
	EntityMask entityMask		= EntityManager::GetInstance().GetEntityMask(entity);
	EntityMask weaponFlag		= DenseComponentCollection<WeaponComponent>::GetInstance().GetComponentTypeFlag();
	EntityMask velocityFlag		= DenseComponentCollection<VelocityComponent>::GetInstance().GetComponentTypeFlag();

	if ( entityMask & weaponFlag ) {
		WeaponComponent* weaponComp = GetDenseComponent<WeaponComponent>(entity);
		if ( weaponComp->CooldownCurrent <= 0.0f ) {
			weaponComp->CooldownCurrent = weaponComp->CooldownMax;

			if ( entityMask & velocityFlag ) {
				VelocityComponent* velocityComp = GetDenseComponent<VelocityComponent>(entity);
				velocityComp->Velocity -= weaponComp->Recoil * direction;
			}
		}
	}
}