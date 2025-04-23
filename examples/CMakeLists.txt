cmake_minimum_required(VERSION 3.10)

file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} */)
foreach(subdir ${SUBDIRS})
    if (IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${subdir})
        file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/${subdir}/*.c
			${CMAKE_SOURCE_DIR}/${subdir}/*.h)
        if (SOURCES)
            string(REPLACE "/" "_" target_name ${subdir})
			message(STATUS "Adding example: ${target_name}")

			# Executable
            add_executable(${target_name} ${SOURCES})

			# Flags
			target_compile_options(${target_name} PRIVATE
			$<$<C_COMPILER_ID:MSVC>:/W4 /WX>
			$<$<C_COMPILER_ID:Clang>:-O3 -Wall -Wextra -Werror -Wfloat-equal
				-Wundef -Wcast-align -Wwrite-strings -Wconversion
				-Wunreachable-code -Wpedantic -Wshadow -Wwrite-strings
				-Wcast-qual -Wstrict-aliasing -Wpointer-arith -Wformat=2
				-Weverything -Wextra-semi -Wmissing-prototypes
				-Wunreachable-code-aggressive -Wimplicit-fallthrough
				-Wloop-analysis -Wrange-loop-analysis -Wcomma -Wmove
				-Wconditional-uninitialized -Wassign-enum
				-Wunused-exception-parameter -Wcovered-switch-default
				-Wno-error=c++98-compat -Wno-error=global-constructors
				-Wno-error=exit-time-destructors -Wno-error=padded>
			$<$<C_COMPILER_ID:Gnu>:-O3 -Wall -Wextra -Werror -Wfloat-equal
				-Wundef -Wcast-align -Wwrite-strings -Wconversion
				-Wunreachable-code -Wpedantic -Wshadow -Wwrite-strings
				-Wcast-qual -Wstrict-aliasing -Wpointer-arith -Wformat=2
				-Wextra-semi -Wmissing-prototypes -Wimplicit-fallthrough
				-Wno-error=c++98-compat -Wno-error=global-constructors
				-Wno-error=exit-time-destructors -Wno-error=padded>
			)

			# Link Libraries
			target_link_libraries(${target_name} PRIVATE SXEval)
        endif()
    endif()
endforeach()
