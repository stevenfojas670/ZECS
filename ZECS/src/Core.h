#pragma once

namespace ZECS
{
	constexpr size_t MAX_ENTITIES = 1 << 16;

	struct Handle
	{
		unsigned short id; // [generation:16][index:16]
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

	struct Slot
	{
		unsigned short generation;
		unsigned short next_free;
		bool isOccupied;
	};

	/// <summary>
	/// Verify if the slot is valid
	/// </summary>
	/// <param name="h"></param>
	/// <param name="slots"></param>
	/// <returns></returns>
	inline bool is_valid(const Handle& h, const Slot* slots)
	{
		unsigned short idx = index(h);
		unsigned short gen = generation(h);
		return slots[idx].isOccupied && slots[idx].generation == gen;
	}
}