cmake_minimum_required(VERSION 2.8.8)
project(Tests)

include(../Framework_Common.cmake)

set(tests_srcs
	../../tests/BmpTest.cpp
	../../tests/BmpTest.h
	../../tests/Main.cpp
	../../tests/StringCastTest.cpp
	../../tests/StringCastTest.h
)

if(NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()

add_executable(Tests ${tests_srcs})
target_link_libraries(Tests Framework)
