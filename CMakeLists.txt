cmake_minimum_required(VERSION 3.14)
project(snake)

set(CMAKE_CXX_STANDARD 17)

IF(WIN32)
	set(SFML_DIR "SFML/lib/cmake/SFML")
	find_package(SFML COMPONENTS graphics window system REQUIRED)	
ELSE()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
ENDIF()


add_executable(snake src/ui/scaled.cpp src/ui/button.cpp src/ui/option.cpp src/ src/obj/block.cpp src/obj/drawable_block.cpp src/obj/gamemap.cpp src/obj/drawable_gamemap.cpp src/obj/drawable_snake.cpp src/assets.cpp src/game.cpp src/main.cpp)
target_link_libraries(snake sfml-graphics sfml-window sfml-system)