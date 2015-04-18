#pragma once

#include <cassert>

#include "BaseCollection.h"

template <typename Component>
class DenseComponentCollection : public BaseCollection
{
public:
	static DenseComponentCollection<Component>& GetInstance()
	{
		static DenseComponentCollection<Component> instance;
		return instance;
	}

	DenseComponentCollection()
	{
		m_Components.resize(COMPONENTS_MAX_DENSE);
	}

	// This function will create a new component with standard values defined in the component struct
	// NOTE: This will recreate at a slot defined with Entity id, make sure this slot is unused.
	void ConstructComponent( Entity entity ) override
	{
		assert( entity < COMPONENTS_MAX_DENSE );
		Component* component = &m_Components.at( entity );
		// Initialize with standard values defined in the struct
		*component = Component();
	}

	void DestructComponent( Entity entity ) override
	{
		assert( entity < COMPONENTS_MAX_DENSE );
	}

	Component* GetComponent( Entity id )
	{
		assert( id < COMPONENTS_MAX_DENSE );
		return &m_Components.at( id );
	}

	std::vector<Component>* GetComponents()
	{
		return &m_Components;
	}

private:
	std::vector<Component> m_Components;
	ComponentTypeIndex m_ComponentTypeIndex;
};

/////////////////////////////
/// Conveniency functions ///
/////////////////////////////

template <typename Component>
static Component* GetDenseComponent( Entity entity )
{
	return DenseComponentCollection<Component>::GetInstance().GetComponent( entity );
}

template <typename Component>
static std::vector<Component>* GetDenseComponentArray( )
{
	return DenseComponentCollection<Component>::GetInstance().GetComponents();
}

template <typename Component>
static EntityMask GetDenseComponentFlag( )
{
	return DenseComponentCollection<Component>::GetInstance( ).GetComponentTypeFlag( );
}

template <typename Component>
static ComponentTypeIndex GetDenseComponentTypeIndex( )
{
	return DenseComponentCollection<Component>::GetInstance( ).GetComponentTypeIndex( );
}
