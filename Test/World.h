#include "EntityManager.h"
#include "ComponentStorage.h"

namespace Tests
{
	struct Vector3
	{
		int x;
		int y;
		int z;
	};

	struct Health
	{
		int value;
	};

	struct Transform
	{
		int x;
		int y;
		int z;
	};

	struct Velocity
	{
		Vector3 velocity;
	};

	class World
	{
		// The world requires an outer abstraction to actually store all components
	};
}