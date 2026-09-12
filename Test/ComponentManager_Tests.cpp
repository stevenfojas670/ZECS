#include <catch2/catch_test_macros.hpp>
#include "Components/ComponentManager.h"
#include "Entities/EntityManager.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Getting a registered component's type returns the same id on every call", "[ComponentManager][GetComponentType]")
	{
		struct Health { int value; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		cm->RegisterComponent<Health>(); // ID for Health should be 1

		ZECS::ComponentType healthId = cm->GetComponentType<Health>();

		REQUIRE(cm->GetComponentType<Health>() == healthId);
		REQUIRE(cm->GetComponentType<Health>() == healthId);
	}

	TEST_CASE("Checking an unregistered component makes IsRegistered() return false", "[ComponentManager][IsRegistered]")
	{
		struct Health { int value; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		REQUIRE(cm->IsRegistered<Health>() == false);
	}

	TEST_CASE("Registering two component types assigns them distinct ids", "[ComponentManager][RegisterComponent]")
	{
		struct Health { int value; };
		struct Transform { int x; int y; };

		auto cm = std::make_unique<ZECS::ComponentManager>();

		cm->RegisterComponent<Health>();
		cm->RegisterComponent<Transform>();

		REQUIRE(cm->GetComponentType<Health>() != cm->GetComponentType<Transform>());
	}

	TEST_CASE("Adding a component to an entity makes GetComponent() return its value", "[ComponentManager][AddComponent]")
	{
		struct Health { int value; };
		struct Transform { int x; int y; };

		auto em = std::make_unique<ZECS::EntityManager>();

		ZECS::Handle ent = em->CreateEntity();
		ZECS::Entity id = ZECS::index(ent);

		auto cm = std::make_unique<ZECS::ComponentManager>();

		cm->RegisterComponent<Health>();
		cm->AddComponent<Health>(id, Health{ 100 });

		auto component = cm->GetComponent<Health>(id);

		REQUIRE(component->value == 100);
	}

	TEST_CASE("Adding a component and removing then verifying it no longer exists with GetComponent()", "[ComponentManager][RemoveComponent]")
	{
		struct Health { int value; };

		auto em = std::make_unique<ZECS::EntityManager>();
		auto cm = std::make_unique<ZECS::ComponentManager>();

		ZECS::Handle h = em->CreateEntity();
		ZECS::Entity id = ZECS::index(h);

		cm->RegisterComponent<Health>();
		cm->AddComponent<Health>(id, Health{ 100 });
		cm->RemoveComponent<Health>(id);

		REQUIRE(cm->GetComponent<Health>(id) == nullptr);
	}
}