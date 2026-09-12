#pragma once

#include "Core.h"

namespace ZECS
{
	class IComponentStorage
	{
	public:
		virtual ~IComponentStorage() = default;
	};

	template <typename T>
	class ComponentStorage : public IComponentStorage
	{
	public:
		ComponentStorage();
		~ComponentStorage();
		void Insert(Entity id, T data);
		void Remove(Entity id);
		bool Has(Entity id) const;
		T* Get(Entity id);
		int Size() const { return size; }
	private:
		unsigned short m_sparseSet[MAX_ENTITIES];
		unsigned short m_denseId[MAX_ENTITIES];
		T m_denseComponent[MAX_ENTITIES];
		int size;
	};

	template <typename T>
	ComponentStorage<T>::ComponentStorage() : size(0)
	{
		for (size_t i = 0; i < MAX_ENTITIES; i++)
		{
			this->m_sparseSet[i] = NULL_INDEX;
			this->m_denseId[i] = NULL_INDEX;
			this->m_denseComponent[i] = T{};
		}
	}

	template <typename T>
	ComponentStorage<T>::~ComponentStorage() = default;

	template <typename T>
	void ComponentStorage<T>::Insert(Entity id, T data)
	{
		if (id == NULL_INDEX) return;
		this->m_denseComponent[size] = data;
		this->m_denseId[size] = id;
		this->m_sparseSet[id] = size;
		size++;
	}

	template <typename T>
	void ComponentStorage<T>::Remove(Entity id)
	{
		if (!Has(id)) return;

		Entity idx = this->m_sparseSet[id];
		int last = size - 1;

		if (idx != last)
		{
			this->m_denseId[idx] = this->m_denseId[last];
			this->m_denseComponent[idx] = this->m_denseComponent[last];
			this->m_sparseSet[this->m_denseId[last]] = idx;
		}

		this->m_denseComponent[last] = T{};
		this->m_denseId[last] = NULL_INDEX;
		this->m_sparseSet[id] = NULL_INDEX;
		size--;
	}

	template <typename T>
	bool ComponentStorage<T>::Has(Entity id) const
	{
		if (id == NULL_INDEX) return false;
		return this->m_sparseSet[id] < size && this->m_denseId[this->m_sparseSet[id]] == id;
	}

	template <typename T>
	T* ComponentStorage<T>::Get(Entity id)
	{
		if (id == NULL_INDEX || !Has(id))
			return nullptr;

		return &this->m_denseComponent[this->m_sparseSet[id]];
	}
}