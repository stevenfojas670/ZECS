#pragma once

#include "Core.h"
#include <iostream>

namespace ZECS
{
	class EntityManager
	{
	public:
		EntityManager() : m_free_list_head(0)
		{
			for (size_t i = 0; i < MAX_ENTITIES; i++)
			{
				m_slots[i].generation = 0;
				m_slots[i].isOccupied = false;

				m_slots[i].next_free = (i + 1 < MAX_ENTITIES)
					? static_cast<unsigned short>(i + 1)
					: NULL_INDEX;
			}
		}

		~EntityManager() = default;

		Handle CreateEntity()
		{
			/*
			* Bad state, we should probably log that we have max entities have to remove some
			* Or we can do a ring buffer and start override other shit, but we'd break everything
			* We could crash clear the entire Slot area of a certain type of item that wouldn't break
			* like Halo 3 did.
			*/
			if (this->m_free_list_head == NULL_INDEX)
			{
				// Log some type of error
				return Handle{ NULL_INDEX };
			}

			// Good state, insert
			unsigned short idx = this->m_free_list_head;

			this->m_slots[m_free_list_head].isOccupied = true;
			this->m_free_list_head = this->m_slots[m_free_list_head].next_free;

			Handle h;
			h.id = handle(idx, this->m_slots[idx].generation);
			return h;
		}

		void DestroyEntity(const Handle& h)
		{
			Entity idx = index(h);
			Slot& currentSlot = this->m_slots[index(h)];

			if (!is_valid(h, this->m_slots))
			{
				std::cout << "Error: Attempted to destroy invalid or already dead Handle [index: "
					<< idx << "]\n";
				return;
			}

			currentSlot.generation++;
			currentSlot.isOccupied = false;
			currentSlot.next_free = this->m_free_list_head;
			this->m_free_list_head = idx;
		}

		bool IsAlive(const Handle& h) const
		{
			return is_valid(h, this->m_slots);
		}

	private:
		Slot m_slots[MAX_ENTITIES]{};
		unsigned short m_free_list_head;

	public:
		const Slot& GetSlot(unsigned short index) const { return m_slots[index]; }
		unsigned short GetFreeListHead() const { return m_free_list_head; }
	};
}