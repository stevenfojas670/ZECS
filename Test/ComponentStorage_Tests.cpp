#include <catch2/catch_test_macros.hpp>
#include "ComponentStorage.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Insert-Tests: Insert component into storage.", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(10, Health{ 100 });

		REQUIRE(cs->Has(10));
	}

	TEST_CASE("Insert-Tests: Insert a negative id", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = -10;

		cs->Insert(id, Health{ 100 });

		REQUIRE(cs->Has(id) == true);
	}

	TEST_CASE("Insert-Tests: Insert more than the maximum allowable components", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = 65535;

		cs->Insert(id, Health{ 100 });

		REQUIRE(cs->Has(id) == false);
	}

	TEST_CASE("Insert-Tests: Random insertions", "[ComponentStorage]")
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

	TEST_CASE("Insert-Tests: Backfill testing", "[ComponentStorage]")
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
	}

	TEST_CASE("Remove-Tests: Remove a non-last component", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(0, Health{ 100 });
		cs->Insert(1, Health{ 95 });

		cs->Remove(0);

		REQUIRE(cs->Has(0) == false);
	}

	TEST_CASE("Remove-Tests: Remove the last component", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(0, Health{ 100 });
		cs->Insert(1, Health{ 95 });

		cs->Remove(1);

		REQUIRE(cs->Has(1) == false);
	}

	TEST_CASE("Remove-Tests: Remove a non-existent component", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		int id = 10;

		cs->Remove(id);

		REQUIRE(cs->Has(id) == false);
	}
}