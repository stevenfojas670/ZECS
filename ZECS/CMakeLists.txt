add_library(ZECS SHARED
    src/Core.h
    src/Entities/EntityManager.h
    src/Entities/EntityManager.cpp
    src/Components/ComponentStorage.h
    src/Components/ComponentManager.h
)

# PUBLIC: consumers of ZECS inherit this include path automatically.
target_include_directories(ZECS PUBLIC src)

# PRIVATE: ZECS itself compiles with __declspec(dllexport); anything linking
# against it sees __declspec(dllimport). See ZECS_API in src/Core.h.
target_compile_definitions(ZECS PRIVATE ZECS_BUILD_DLL)
