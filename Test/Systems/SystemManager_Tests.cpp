#include <catch2/catch_test_macros.hpp>
#include "Systems/SystemManager.h"
#include "Systems.h"
#include "Helpers.h"
#include <memory>

namespace Tests
{
	TEST_CASE("Registering Movement System and verifying it was inserted into system container.", "[SystemManager][Register]")
	{
		auto sm = std::make_unique<ZECS::SystemManager>();


	}
}