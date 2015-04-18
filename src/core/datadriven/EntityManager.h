#pragma once

#include <array>
#include <vector>
#include <queue>

#include "BaseCollection.h"
#include "ComponentTypes.h"

#define g_EntityManager EntityManager::GetInstance()

#define ENTITY_MANAGER_NR_OF_BITS_TO_PRINT 24

class EntityManager
{
public:
	static EntityManager& GetInstance();
	EntityManager();
	~EntityManager();

	void 	SetCollectionVector ( std::vector<BaseCollection*>* collections );

	void 	RemoveComponent		( Entity entity, ComponentTypeIndex componentTypeIndex );
	void 	AddComponent		( Entity entity, ComponentTypeIndex componentTypeIndex );
	Entity 	CreateEntity		( );
	void 	RemoveEntity 		( Entity entity );

	void 	PrintMasks			( );

	const std::vector<EntityMask>& GetEntityMasks() const;
	EntityMask GetEntityMask( Entity entity ) const;

private:
	std::vector<BaseCollection*>* 						m_Collections;
	std::vector<EntityMask> 							m_EntityMasks;
	std::queue<Entity> 								m_EntitySlotsFree;
	Entity		 									m_MaxEntityValue = 0;
};
