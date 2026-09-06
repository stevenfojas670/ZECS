#pragma once

#include "Core.h"

namespace ZECS
{
	class ZECS_API EntityManager
	{
	public:
		EntityManager();
		~EntityManager();
		Handle CreateEntity();
		void DestroyEntity(const Handle&);
		bool IsAlive(const Handle&) const;
	private:
		Slot m_slots[MAX_ENTITIES]{};
		unsigned short m_free_list_head;
	};
}