#include <catch2/catch_test_macros.hpp>
#include "Components/ComponentStorage.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Inserting a component makes Has() return true", "[ComponentStorage][Insert]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(10, Health{ 100 });

		REQUIRE(cs->Has(10));
	}

	TEST_CASE("Inserting a negative id wraps to a valid entity index", "[ComponentStorage][Insert]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = -10; // Entity is unsigned short, so -10 converts to 65526, a valid index

		cs->Insert(id, Health{ 100 });

		REQUIRE(cs->Has(id) == true);
	}

	TEST_CASE("Inserting at NULL_INDEX is rejected", "[ComponentStorage][Insert]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = 65535; // 65535 == NULL_INDEX, which Insert rejects

		cs->Insert(id, Health{ 100 });

		REQUIRE(cs->Has(id) == false);
	}

	TEST_CASE("Removing one component from a heavily populated storage makes Has() return false", "[ComponentStorage][Remove]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		for (int i = 0; i < 65535 / 2; i++)
		{
			cs->Insert(i * 2, Health{ 100 });
		}

		cs->Remove(800);

		REQUIRE(cs->Has(800) == false);
	}

	TEST_CASE("Inserting after removals keeps new components retrievable", "[ComponentStorage][Insert]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(0, Health{ 100 });
		cs->Insert(1, Health{ 99 });
		cs->Insert(2, Health{ 98 });

		cs->Remove(0);
		cs->Remove(1);

		REQUIRE(cs->Has(0) == false);
		REQUIRE(cs->Has(1) == false);

		cs->Insert(3, Health{ 97 });
		cs->Insert(4, Health{ 96 });

		REQUIRE(cs->Has(3) == true);
		REQUIRE(cs->Get(3)->value == 97);
		REQUIRE(cs->Has(4) == true);
		REQUIRE(cs->Get(4)->value == 96);
		REQUIRE(cs->Size() == 3);
	}

	TEST_CASE("Removing a non-last component makes Has() false and shrinks Size()", "[ComponentStorage][Remove]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(0, Health{ 100 });
		cs->Insert(1, Health{ 95 });

		cs->Remove(0);

		REQUIRE(cs->Has(0) == false);
		REQUIRE(cs->Size() == 1);
	}

	TEST_CASE("Removing the last component makes Has() return false", "[ComponentStorage][Remove]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(0, Health{ 100 });
		cs->Insert(1, Health{ 95 });

		cs->Remove(1);

		REQUIRE(cs->Has(1) == false);
	}

	TEST_CASE("Removing a component that was never inserted leaves Has() false", "[ComponentStorage][Remove]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = 10;

		cs->Remove(id);

		REQUIRE(cs->Has(id) == false);
	}
}