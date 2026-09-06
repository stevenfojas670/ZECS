#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "EntityManager.h"

TEST_CASE("Distinct live entities occupy distinct slots", "[EntityManager]")
{
	// Heap-allocated: EntityManager embeds Slot[65536] (~384 KB), which is more
	// than belongs on the default 1 MB stack.
	auto em = std::make_unique<ZECS::EntityManager>();

	ZECS::Handle a = em->CreateEntity();
	ZECS::Handle b = em->CreateEntity();

	REQUIRE(ZECS::index(a) != ZECS::index(b));
}
