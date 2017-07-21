project(agent-bundler)

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
  message(STATUS "${PROJECT_NAME} 64 bit") 
else()
  message(STATUS "${PROJECT_NAME} 32 bit") 
endif()

configure_file(src/res/BundlerStub.h.cmake BundlerStub.h @ONLY)

set(HEADER_FILES
	${CMAKE_CURRENT_BINARY_DIR}/BundlerStub.h
	)

set(SOURCE_FILES
	src/main.cpp
	)

set(RESOURCE_FILES
	)

set(MISC
	src/pch.h
	src/pch.cpp
	)

set_source_files_properties(
	${CMAKE_CURRENT_BINARY_DIR}/BundlerStub.h PROPERTIES GENERATED 1)

source_group("Header Files" FILES ${HEADER_FILES})
source_group("Resource Files" FILES ${RESOURCE_FILES})
source_group("Source Files" FILES ${SOURCE_FILES})
source_group("" FILES ${MISC})

include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}
	${Boost_INCLUDE_DIRS}
	)

add_executable(${PROJECT_NAME}
	${HEADER_FILES}
	${RESOURCE_FILES}
	${SOURCE_FILES}
	${MISC}
	)

target_link_libraries(${PROJECT_NAME}
	${Boost_LIBRARIES}
	)

add_definitions(
	-DUNICODE
	-D_UNICODE
	)
