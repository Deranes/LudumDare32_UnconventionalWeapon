#include "EntityManager.h"

#include <cassert>
#include <bitset>
//#include <utility/Logger.h>

EntityManager& EntityManager::GetInstance()
{
	static EntityManager instance;
	return instance;
}

EntityManager::EntityManager()
{
	for ( int i = 0; i < COMPONENTS_MAX_DENSE; ++i )
	{
		m_EntitySlotsFree.push( i );
	}
	m_EntityMasks.resize( COMPONENTS_MAX_DENSE );
}

EntityManager::~EntityManager()
{
	delete m_Collections; //TODO THis might break?
}

void EntityManager::SetCollectionVector( std::vector<BaseCollection*>* collections )
{
	m_Collections = collections;
}

void EntityManager::RemoveComponent( Entity entity, ComponentTypeIndex componentTypeIndex )
{
	assert(componentTypeIndex < m_Collections->size());
	assert(entity < COMPONENTS_MAX_DENSE);
	// Remove component from the component types collection
	m_Collections->at( componentTypeIndex )->DestructComponent( entity );
	// Turn flag off that marks this component type
	m_EntityMasks.at( entity ) &= ~(1 << componentTypeIndex);
}

void EntityManager::AddComponent( Entity entity, ComponentTypeIndex componentTypeIndex )
{
	assert(componentTypeIndex < m_Collections->size());
	assert(entity < COMPONENTS_MAX_DENSE);
	// Add component to the component types collection
	m_Collections->at( componentTypeIndex )->ConstructComponent( entity );
	// Turn flag on that marks this component type
	m_EntityMasks.at( entity ) |= 1ULL << componentTypeIndex;
}

Entity EntityManager::CreateEntity()
{
	// TODOJM: Dynamically expand? Discuss this when relevant limits can be tested.
	assert( m_EntitySlotsFree.size() > 0 );
	// Get first element from the queue
	Entity entity = m_EntitySlotsFree.front();
	m_EntitySlotsFree.pop();
	// Mark entity to have no components as default
	m_EntityMasks.at(entity) = 0;
	m_MaxEntityValue = std::max( m_MaxEntityValue, entity );

	return entity;
}

void EntityManager::RemoveEntity( Entity entity )
{
	assert(entity < COMPONENTS_MAX_DENSE);
	EntityMask mask = m_EntityMasks.at(entity);
	m_EntityMasks.at(entity) = 0;
	// Loop through each flag in the component mask
	for ( unsigned long i = 0; i < sizeof(EntityMask); ++i )
	{
		// Only remove component if flag is set
		if ( mask & (1ULL << i) )
		{
			m_Collections->at( i )->DestructComponent( entity );
		}
	}
	// Push the removed entity to the queue for later reuse
	m_EntitySlotsFree.push(entity);
}

void EntityManager::PrintMasks()
{
	//Logger::GetStream() << "Entity masks: " << std::endl;
	for ( Entity i = 0; i < m_MaxEntityValue; ++i )
	{
		//Logger::GetStream() << i << ": " << std::bitset<ENTITY_MANAGER_NR_OF_BITS_TO_PRINT>(m_EntityMasks[i]) << std::endl;
	}
}

const std::vector<EntityMask>& EntityManager::GetEntityMasks() const
{
	return m_EntityMasks;
}

EntityMask EntityManager::GetEntityMask( Entity entity ) const
{
	assert( entity < m_EntityMasks.size() );
	return m_EntityMasks.at( entity );
}
