#pragma once

#include "EntityManager.h"
#include "Core.h"

namespace ZECS
{
	EntityManager::EntityManager() : free_list_head(0)
	{
		for (size_t i = 0; i < MAX_ENTITIES; i++)
		{
			slots[i].generation = 0;
			slots[i].isOccupied = false;

			slots[i].next_free = (i + 1 < MAX_ENTITIES)
				? static_cast<unsigned short>(i + 1)
				: NULL_INDEX;
		}
	}

	EntityManager::~EntityManager()
	{

	}

	Handle EntityManager::CreateEntity()
	{
		/*
		* Bad state, we should probably log that we have max entities have to remove some
		* Or we can do a ring buffer and start override other shit, but we'd break everything
		* We could crash clear the entire Slot area of a certain type of item that wouldn't break
		* like Halo 3 did.
		*/
		if (this->free_list_head == NULL_INDEX)
		{
			// Log some type of error
			return Handle{ 0 };
		}

		// Good state, insert
		unsigned short idx = this->free_list_head;

		this->slots[free_list_head].isOccupied = true;
		this->free_list_head = this->slots[free_list_head].next_free;

		Handle h;
		h.id = handle(idx, this->slots[idx].generation);
		return h;
	}

	void EntityManager::DestroyEntity(const Handle& h)
	{
		unsigned short idx = index(h);
		Slot& currentSlot = this->slots[index(h)];

		if (!is_valid(h, this->slots))
		{
			return;
		}

		currentSlot.generation++;
		currentSlot.isOccupied = false;
		currentSlot.next_free = this->free_list_head;
		this->free_list_head = idx;
	}
}