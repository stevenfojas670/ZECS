#pragma once

#ifdef ZECS_BUILD_DLL
#define ZECS_API __declspec(dllexport)
#else
#define ZECS_API __declspec(dllimport)
#endif

namespace ZECS
{
	constexpr size_t MAX_ENTITIES = 1 << 16;
	constexpr size_t MAX_COMPONENTS = 256;

	struct Handle
	{
		unsigned int id; // [generation:16][index:16]
	};

	constexpr unsigned short INDEX_MASK = 0xFFFF;
	constexpr unsigned short GENERATION_SHIFT = 16;

	inline unsigned short index(const Handle& h)
	{
		return h.id & INDEX_MASK;
	}

	inline unsigned short generation(const Handle& h)
	{
		return h.id >> GENERATION_SHIFT;
	}

	inline unsigned int handle(unsigned int index, unsigned int generation)
	{
		return (generation << GENERATION_SHIFT) | index;
	}

	constexpr unsigned short NULL_INDEX = 0xFFFF;

	struct Slot
	{
		unsigned short generation;
		unsigned short next_free;
		bool isOccupied;
	};

	inline bool is_valid(const Handle& h, const Slot* slots)
	{
		unsigned short idx = index(h);
		unsigned short gen = generation(h);
		return slots[idx].isOccupied && slots[idx].generation == gen;
	}

	using ComponentType = unsigned int;
}