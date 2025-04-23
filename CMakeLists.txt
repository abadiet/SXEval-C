cmake_minimum_required(VERSION 3.10)

# Options
option(BUILD_EXAMPLES "Build examples" ON)

# Project
project(SXEval C)

# Download/Update librairies if needed
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodules update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --remote
			--init --recursive
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --remote --init
				--recursive failed with ${GIT_SUBMOD_RESULT}, please checkout
				submodules")
        endif()
    endif()
endif()
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/sfsexp" OR
		NOT EXISTS "${PROJECT_SOURCE_DIR}/lib/uthash")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was
		turned off or failed. Please update submodules and try again.")
endif()

# Sources
file(GLOB_RECURSE SOURCES src/*.c lib/sfsexp/src/*.c lib/uthash/src/*.c)
file(GLOB_RECURSE INCLUDES include/*.h lib/sfsexp/src/*.h lib/uthash/src/*.h)

# Library
add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

# Flags
target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<C_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<C_COMPILER_ID:Clang>:-O3 -Wall -Wextra -Werror -Wfloat-equal -Wundef
		-Wcast-align -Wwrite-strings -Wconversion -Wunreachable-code -Wpedantic
		-Wshadow -Wwrite-strings -Wcast-qual -Wstrict-aliasing -Wpointer-arith
		-Wformat=2 -Weverything -Wextra-semi -Wmissing-prototypes
		-Wunreachable-code-aggressive -Wimplicit-fallthrough -Wloop-analysis
		-Wrange-loop-analysis -Wcomma -Wmove -Wconditional-uninitialized
		-Wassign-enum -Wunused-exception-parameter -Wcovered-switch-default
		-Wno-error=c++98-compat -Wno-error=global-constructors
		-Wno-error=exit-time-destructors -Wno-error=padded>
	$<$<C_COMPILER_ID:Gnu>:-O3 -Wall -Wextra -Werror -Wfloat-equal -Wundef
		-Wcast-align -Wwrite-strings -Wconversion -Wunreachable-code -Wpedantic
		-Wshadow -Wwrite-strings -Wcast-qual -Wstrict-aliasing -Wpointer-arith
		-Wformat=2 -Wextra-semi -Wmissing-prototypes -Wimplicit-fallthrough
		-Wno-error=c++98-compat -Wno-error=global-constructors
		-Wno-error=exit-time-destructors -Wno-error=padded>
)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC include lib/sfsexp/src
	lib/uthash/src)

#Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
