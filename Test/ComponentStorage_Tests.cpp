#include <catch2/catch_test_macros.hpp>
#include "ComponentStorage.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Insert component into storage.", "[ComponentStorage]")
	{
		struct Health { int value; };

		auto cs = std::make_unique<ZECS::ComponentStorage<Health>>();

		cs->Insert(10, Health{ 100 });

		REQUIRE(cs->Has(10));
	}

	TEST_CASE("Remove component", "[ComponentStorage]")
	{

	}
}