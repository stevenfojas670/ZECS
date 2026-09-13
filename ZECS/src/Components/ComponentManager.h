#pragma once

#include "ComponentStorage.h"
#include "Core.h"
#include <memory>

namespace ZECS
{
	template <typename T>
	inline ComponentType GetComponentTypeId()
	{
		static ComponentType typeId = internal::GetComponentId();
		return typeId;
	}

	class ComponentManager
	{
	public:

		template <typename T>
		void RegisterComponent()
		{
			ComponentType typeId = GetComponentTypeId<T>();
			m_storages[typeId] = std::make_unique<ComponentStorage<T>>();
		}

		template <typename T>
		void UnregisterComponent()
		{
			ComponentType typeId = GetComponentTypeId<T>();

			if (!IsRegistered<T>()) return;

			m_storages[typeId].reset();
		}

		template <typename T>
		bool IsRegistered()
		{
			ComponentType typeId = GetComponentTypeId<T>();

			return m_storages[typeId] != nullptr ? true : false;
		}

		template <typename T>
		ComponentType GetComponentType()
		{
			return GetComponentTypeId<T>();
		}

		template <typename T>
		void AddComponent(Entity id, T data)
		{
			GetStorage<T>()->Insert(id, data);
		}

		template <typename T>
		T* GetComponent(Entity id)
		{
			return GetStorage<T>()->Get(id);
		}

		template <typename T>
		void RemoveComponent(Entity id)
		{
			GetStorage<T>()->Remove(id);
		}

	private:
		std::unique_ptr<IComponentStorage> m_storages[MAX_COMPONENTS];

		template <typename T>
		ComponentStorage<T>* GetStorage()
		{
			ComponentType typeId = GetComponentTypeId<T>();

			assert(m_storages[typeId] != nullptr && "ComponentStorage for type T does not exist!");
			return static_cast<ComponentStorage<T>*>(m_storages[typeId].get());
		}
	};
}