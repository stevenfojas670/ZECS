#include <iostream>
#include <memory>

#include "EntityManager.h"

// assert() compiles out under NDEBUG, so Release would silently pass.
// This always runs and makes the process exit non-zero for CTest.
static int g_failures = 0;

#define CHECK(expr)                                                       \
	do                                                                    \
	{                                                                     \
		if (!(expr))                                                      \
		{                                                                 \
			std::cout << "FAIL: " << #expr                                \
			          << " (" << __FILE__ << ":" << __LINE__ << ")\n";    \
			++g_failures;                                                 \
		}                                                                 \
	} while (0)

int main()
{
	// Heap-allocated: EntityManager embeds Slot[65536] (~384 KB), which is
	// more than belongs on the default 1 MB stack.
	auto em = std::make_unique<ZECS::EntityManager>();

	// Distinct live entities must not share a slot.
	ZECS::Handle a = em->CreateEntity();
	ZECS::Handle b = em->CreateEntity();
	CHECK(ZECS::index(a) != ZECS::index(b));

	// A destroyed slot returns to the free list, so the next entity should
	// reuse that index with a bumped generation -- same slot, different handle.
	ZECS::Handle a_index = a;
	em->DestroyEntity(a);
	ZECS::Handle c = em->CreateEntity();
	CHECK(ZECS::index(c) == ZECS::index(a_index));
	CHECK(ZECS::generation(c) != ZECS::generation(a_index));
	CHECK(c.id != a_index.id);

	// The untouched entity keeps its own slot.
	CHECK(ZECS::index(b) != ZECS::index(c));

	if (g_failures != 0)
	{
		std::cout << g_failures << " check(s) failed\n";
		return 1;
	}

	std::cout << "All checks passed\n";
	return 0;
}
