## Overview

This is a custom built single-threaded header only ECS library built for my personal game engine ZiggyX.

## Structure

| Class              | Purpose                                                                                                                                                                        |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `zec`              | Main controller for the system. It will serve as the wrapper for all calls to the different components such as the `Entity Manager`, `Component Manager` and `System Manager`. |
| `EntityManager`    | Responsible for creating and removing entities.                                                                                                                                |
| `ComponentManager` | Responsible for orchestrating the creation and removal of `ComponentStorage<T>` sparse sets as well as inserting, removing and retrieving data into those sparse sets.         |
| `SystemManager`    | Responsible for orchestrating systems. I'm not quite there yet.                                                                                                                |
| `ComponentStorage` | Templated sparse set that stores the component data mapped to the entity ids.                                                                                                  |


## Testing

`Catch2` is used for testing.
