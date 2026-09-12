#include <catch2/catch_test_macros.hpp>
#include "Components/ComponentManager.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Register-Tests: Registering a component and verifying its ID.", "[ComponentManager]")
	{
		struct Health { int value; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		cm->RegisterComponent<Health>(); // ID for Health should be 1

		ZECS::ComponentType healthId = cm->GetComponentType<Health>();

		REQUIRE(cm->GetComponentType<Health>() == healthId);
		REQUIRE(cm->GetComponentType<Health>() == healthId);
	}

	TEST_CASE("Register-Tests: Getting the component id of a non-registered component.", "[ComponentManager]")
	{
		struct Health { int value; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		REQUIRE(cm->IsRegistered<Health>() == false);
	}

	TEST_CASE("Register-Tests: Two different components have two different ids", "[ComponentManager]")
	{
		struct Health { int value; };
		struct Transform { int x; int y; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		cm->RegisterComponent<Health>();
		cm->RegisterComponent<Transform>();

		REQUIRE(cm->GetComponentType<Health>() != cm->GetComponentType<Transform>());
	}
}