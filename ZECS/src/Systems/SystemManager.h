#pragma once

#include "Core.h"
#include <memory>

namespace ZECS
{
	template <typename T>
	inline SystemType GetSystemTypeId()
	{
		static SystemType typeId = internal::GetSystemId();
		return typeId;
	}

	class ISystem
	{
	public:
		virtual ~ISystem() = default;
		virtual void Update(float) = 0;
	};

	class SystemManager
	{
	public:

	private:
		std::unique_ptr<ISystem> m_systems[MAX_SYSTEMS];
	};
}