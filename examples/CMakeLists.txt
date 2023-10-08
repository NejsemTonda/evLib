add_executable("test_allOnes")
set_property(TARGET "test_allOnes" PROPERTY CXX_STANDARD 20)
target_include_directories("test_allOnes" PUBLIC "..")
target_sources("test_allOnes" PUBLIC "allOnes.cpp")
 
add_executable("test_backpack")
set_property(TARGET "test_backpack" PROPERTY CXX_STANDARD 20)
target_include_directories("test_backpack" PUBLIC "..")
target_sources("test_backpack" PUBLIC "backpack.cpp")

add_executable("test_keyboard")
set_property(TARGET "test_keyboard" PROPERTY CXX_STANDARD 20)
target_include_directories("test_keyboard" PUBLIC "..")
target_sources("test_keyboard" PUBLIC "keyboard.cpp")

