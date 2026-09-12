#pragma once

#include "ComponentStorage.h"
#include "Core.h"
#include <memory>

namespace ZECS
{
	namespace internal
	{
		inline ComponentType GetComponentId()
		{
			static ComponentType s_componentId = 1;
			return s_componentId++;
		}
	}

	template <typename T>
	inline ComponentType GetComponentTypeId()
	{
		static ComponentType typeId = internal::GetComponentId();
		return typeId;
	}

	class ComponentManager
	{
	public:
		template <typename T> void RegisterComponent();
		template <typename T> bool IsRegistered();
		template <typename T> ComponentType GetComponentType();
	private:
		std::unique_ptr<IComponentStorage> m_storages[MAX_COMPONENTS];
		template <typename T> ComponentStorage<T>* GetStorage();
	};

	template <typename T>
	ComponentStorage<T>* ComponentManager::GetStorage()
	{
		ComponentType typeId = GetComponentTypeId<T>();
		return static_cast<ComponentStorage<T>*>(m_storages[typeId].get());
	}

	template <typename T>
	void ComponentManager::RegisterComponent()
	{
		ComponentType typeId = GetComponentTypeId<T>();
		this->m_storages[typeId] = std::make_unique<ComponentStorage<T>>();
	}

	template <typename T>
	bool ComponentManager::IsRegistered()
	{
		ComponentType typeId = GetComponentTypeId<T>();

		return this->m_storages[typeId] != nullptr ? true : false;
	}

	template <typename T>
	ComponentType ComponentManager::GetComponentType()
	{
		return GetComponentTypeId<T>();
	}
}