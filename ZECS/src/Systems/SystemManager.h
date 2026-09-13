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

		template <typename T>
		void RegisterSystem()
		{
			SystemType typeId = GetSystemTypeId<T>();
			m_systems[typeId] = std::make_unique<T>();
		}

		template <typename T>
		T* GetSystem()
		{
			SystemType typeId = GetSystemTypeId<T>();
			return m_systems[typeId] != nullptr ? static_cast<T*>(m_systems[typeId].get()) : nullptr;
		}

		template <typename T>
		bool IsRegistered()
		{
			SystemType typeId = GetSystemTypeId<T>();
			return m_systems[typeId] != nullptr ? true : false;
		}

		void Update(float deltaTime)
		{
			for (auto& system : m_systems)
			{
				if (system) system->Update(deltaTime);
			}
		}

	private:
		std::unique_ptr<ISystem> m_systems[MAX_SYSTEMS];
	};
}