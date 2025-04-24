cmake_minimum_required(VERSION 3.10)

file(GLOB SUBDIRS RELATIVE ${CMAKE_SOURCE_DIR} */)
foreach(SUBDIR ${SUBDIRS})
    if (IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${SUBDIR})
        file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/${SUBDIR}/*.c
			${CMAKE_SOURCE_DIR}/${SUBDIR}/*.h)
        if (SOURCES)
            string(REPLACE "/" "_" TARGET_NAME ${SUBDIR})
			message(STATUS "Adding example: ${TARGET_NAME}")

			# Executable
            add_executable(${TARGET_NAME} ${SOURCES})

			# Flags
			target_compile_options(${TARGET_NAME} PRIVATE
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
			target_link_libraries(${TARGET_NAME} PRIVATE SXEval)
        endif()
    endif()
endforeach()
