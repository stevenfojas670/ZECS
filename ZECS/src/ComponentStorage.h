#pragma once

#include "Core.h"

namespace ZECS
{
	template <typename T>
	class ComponentStorage
	{
	public:
		ComponentStorage();
		~ComponentStorage();
		void Insert(unsigned short id, T data);
		void Remove(unsigned short id);
	private:
		unsigned short m_sparseSet[MAX_ENTITIES];
		unsigned short m_denseId[MAX_ENTITIES];
		T m_denseComponent[MAX_ENTITIES];
		int size;
	};

	template <typename T>
	ComponentStorage<T>::ComponentStorage() : size(0)
	{

	}

	template <typename T>
	ComponentStorage<T>::~ComponentStorage()
	{

	}

	template <typename T>
	void ComponentStorage<T>::Insert(unsigned short id, T data)
	{
		this->m_denseComponent[size] = data;
		this->m_denseId[size] = id;
		this->m_sparseSet[id] = size;
		size++;
	}

	template <typename T>
	void ComponentStorage<T>::Remove(unsigned short id)
	{
		unsigned short idx = this->m_sparseSet[id];
		int last = size - 1;

		if (idx != last)
		{
			this->m_denseId[idx] = this->m_denseId[last];
			this->m_denseComponent[idx] = this->m_denseComponent[last];
			this->m_sparseSet[this->denseId[last]] = idx;
		}
		size--;
	}
}