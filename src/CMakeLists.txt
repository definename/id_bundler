cmake_minimum_required(VERSION 3.2.1)

project(bundler_sample)

if (MSVC14 OR MSVC12) # Has the support we need.
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_compile_options(/W4)
	set(CMAKE_CXX_STANDARD 14)
else ()
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if (COMPILER_SUPPORTS_CXX14)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-missing-braces")
    elseif (COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-missing-braces")
    else ()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. "
	    "Please use a different C++ compiler.")
    endif ()
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(PCHSupport)
include(CRTLinkage)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED COMPONENTS
		program_options
		)

set(STUB_INSTALL_ID "fb6499c2-6aea-11e7-907b-a6006ad3dba0")
set(STUB_EMAIL "f615529a-6aea-11e7-907b-a6006ad3dba0")
set(STUB_PASSWORD "e1ea315a-6aea-11e7-907b-a6006ad3dba0")
set(STUB_SERVER_HOST "faab7cea-6c88-11e7-907b-a6006ad3dba0")
set(STUB_SERVER_PORT "fef401d2-6c88-11e7-907b-a6006ad3dba0")

add_subdirectory(modules/agent-bundler)
