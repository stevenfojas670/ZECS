#pragma once

#include "Core.h"

namespace ZECS
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();
		unsigned int CreateEntity();
		void DestroyEntity();
	private:
		Slot slots[]
	};
}