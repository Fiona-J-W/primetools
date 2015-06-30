project(primetools)

# to shut up cmake, I have no clue what version this needs:
cmake_minimum_required(VERSION 2.8)


# create sane environment
#####################################################################

# Sadly, this doesn't seem to work:
#set_property(GLOBAL PROPERTY CXX_STANDARD 11)
#set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

# Ok, so let's just hardcode all the flags instead:
# TODO: make this portable
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y" )

# we want tests:
enable_testing()


# options
#####################################################################
Option(BUILD_TESTS "build-tests" ON)


# required packages
#####################################################################

if(BUILD_TESTS)
	find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()


# targets
#####################################################################

include_directories("include")

file(GLOB library_headers "include/*.hpp")
file(GLOB library_code_files "src/lib/*.cpp")
file(GLOB app_code_files "src/app/*.cpp")
file(GLOB app_headers "src/app/*.hpp")
file(GLOB test_file "test/main.cpp")


add_library(prime_lib ${library_headers} ${library_code_files})
add_executable(prime_app ${app_code_files} ${app_headers})
target_link_libraries(prime_app prime_lib)

if(BUILD_TESTS)
	add_executable(primetools_tests ${test_file})
	target_link_libraries(primetools_tests
		prime_lib
		${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	)
	add_test(
		NAME "primetools_tests"
		COMMAND primetools_tests
	)
endif()
