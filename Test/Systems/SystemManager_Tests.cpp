#include <catch2/catch_test_macros.hpp>
#include "Systems/SystemManager.h"
#include "Systems.h"
#include "Helpers.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Registering Movement System and verifying it exists with GetSystem()", "[SystemManager][Register]")
	{
		auto sm = std::make_unique<ZECS::SystemManager>();

		sm->RegisterSystem<MovementSystem>();

		auto ms = sm->GetSystem<MovementSystem>();

		REQUIRE(ms != nullptr);
	}

	TEST_CASE("Getting a system that does not exist and expecting a nullptr to be returned", "[SystemManager][GetSystem]")
	{
		auto sm = std::make_unique<ZECS::SystemManager>();

		auto ms = sm->GetSystem<MovementSystem>();

		REQUIRE(ms == nullptr);
	}
}