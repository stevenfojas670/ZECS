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
	private:
		Slot slots[MAX_ENTITIES]{};
		unsigned short free_list_head;
	};
}