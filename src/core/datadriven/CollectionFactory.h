#pragma once

#include "BaseCollection.h"
#include "DenseComponentCollection.h"

// Get a list of all given components collections. Also assigns unique ID to the collections.
template <typename... Components>
static std::vector<BaseCollection*>* GetCollections()
{
	std::vector<BaseCollection*>* collections = new std::vector<BaseCollection*>[(sizeof...(Components))];
	*collections = { &DenseComponentCollection<Components>::GetInstance()... };
	for (short i = 0; i < static_cast<short>(collections->size()); ++i )
	{
		collections->at( i )->SetComponentTypeIndex( i );
	}
	
	return collections;
}