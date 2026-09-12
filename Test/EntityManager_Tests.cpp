#include <catch2/catch_test_macros.hpp>
#include "Entities/EntityManager.h"
#include "Helpers.h"

namespace Tests
{
	TEST_CASE("Creating two entities assigns them distinct indices", "[EntityManager][CreateEntity]")
	{
		// Heap-allocated: EntityManager embeds Slot[65536] (~384 KB), which is more
		// than belongs on the default 1 MB stack.
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		ZECS::Handle b = em->CreateEntity();

		REQUIRE(ZECS::index(a) != ZECS::index(b));
	}

	TEST_CASE("Destroying an entity frees its slot and increments its generation", "[EntityManager][DestroyEntity]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		ZECS::Handle b = em->CreateEntity();
		ZECS::Handle c = em->CreateEntity();

		auto current_free_list_head = em->GetFreeListHead();

		em->DestroyEntity(b);

		// We need to verify that index 1 has { gen: 1, isOccupied: false, next_free: 3 }

		auto& slot = em->GetSlot(ZECS::index(b));

		REQUIRE(em->IsAlive(b) == false);
		REQUIRE(slot.generation == 1);
		REQUIRE(slot.isOccupied == false);
		REQUIRE(slot.next_free == current_free_list_head);
		REQUIRE(em->GetFreeListHead() == 1);
	}

	TEST_CASE("Destroying two entities links the second freed slot to the first", "[EntityManager][DestroyEntity]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		ZECS::Handle b = em->CreateEntity();
		ZECS::Handle c = em->CreateEntity();

		em->DestroyEntity(a);
		em->DestroyEntity(b);

		auto& slot = em->GetSlot(ZECS::index(b));

		REQUIRE(slot.next_free == 0);
	}

	TEST_CASE("Creating entities after destroys reuses freed slots in LIFO order", "[EntityManager][CreateEntity]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		ZECS::Handle b = em->CreateEntity();
		ZECS::Handle c = em->CreateEntity();

		em->DestroyEntity(a);
		em->DestroyEntity(b);

		ZECS::Handle d = em->CreateEntity();
		ZECS::Handle e = em->CreateEntity();

		auto& slot_0 = em->GetSlot(ZECS::index(a));
		auto& slot_1 = em->GetSlot(ZECS::index(b));

		REQUIRE(em->GetFreeListHead() == 3);

		REQUIRE(slot_0.next_free == 3);
		REQUIRE(slot_0.generation == 1);
		REQUIRE(slot_0.isOccupied == true);
		REQUIRE(ZECS::index(a) == ZECS::index(e));

		REQUIRE(slot_1.next_free == 0);
		REQUIRE(slot_1.generation == 1);
		REQUIRE(slot_1.isOccupied == true);
		REQUIRE(ZECS::index(d) == ZECS::index(b));
	}

	TEST_CASE("Destroying a reused slot increments its generation to 2", "[EntityManager][DestroyEntity]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		ZECS::Handle b = em->CreateEntity();

		em->DestroyEntity(a);

		ZECS::Handle c = em->CreateEntity();

		em->DestroyEntity(c);

		auto& slot = em->GetSlot(ZECS::index(c));

		REQUIRE(slot.generation == 2);
	}

	TEST_CASE("A destroyed handle is no longer alive", "[EntityManager][IsAlive]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		em->DestroyEntity(a);

		REQUIRE(em->IsAlive(a) == false);
	}

	TEST_CASE("Destroying an entity twice logs an error to the console", "[EntityManager][DestroyEntity]")
	{
		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle a = em->CreateEntity();
		em->DestroyEntity(a);

		CaptureStdout capture;
		em->DestroyEntity(a);

		REQUIRE(capture.str().find("Error: Attempted to destroy invalid or already dead Handle") != std::string::npos);
	}
}