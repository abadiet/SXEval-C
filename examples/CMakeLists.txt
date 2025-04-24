cmake_minimum_required(VERSION 3.10)

set(FLAGS_FIX_LIB_GNU -Wno-error=strict-prototypes
    -Wno-error=missing-prototypes -Wno-error=implicit-fallthrough
    -Wno-error=sign-conversion -Wno-error=sign-compare -Wno-error=type-limits)
set(FLAGS_FIX_LIB_CLANG ${FLAGS_FIX_LIB_GNU} -Wno-error=documentation-html
    -Wno-error=missing-variable-declarations
    -Wno-error=tautological-unsigned-zero-compare
    -Wno-error=covered-switch-default)

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
			$<$<C_COMPILER_ID:AppleClang>:-O3 -Wall -Wextra -Werror -Wfloat-equal
				-Wundef -Wcast-align -Wwrite-strings -Wconversion
				-Wunreachable-code -Wpedantic -Wshadow -Wwrite-strings
				-Wcast-qual -Wstrict-aliasing -Wpointer-arith -Wformat=2
				-Weverything -Wextra-semi -Wmissing-prototypes
				-Wunreachable-code-aggressive -Wimplicit-fallthrough
				-Wloop-analysis -Wrange-loop-analysis -Wcomma -Wmove
				-Wconditional-uninitialized -Wassign-enum
				-Wunused-exception-parameter -Wcovered-switch-default
				-Wno-error=padded ${FLAGS_FIX_LIB_CLANG}>
			$<$<C_COMPILER_ID:GNU>:-O3 -Wall -Wextra -Werror -Wfloat-equal
				-Wundef -Wcast-align -Wwrite-strings -Wconversion
				-Wunreachable-code -Wpedantic -Wshadow -Wwrite-strings
				-Wcast-qual -Wstrict-aliasing -Wpointer-arith -Wformat=2
				-Wmissing-prototypes -Wimplicit-fallthrough
				-Wno-error=padded ${FLAGS_FIX_LIB_GNU}>
			)

			# Link Libraries
			target_link_libraries(${TARGET_NAME} PRIVATE SXEval)
        endif()
    endif()
endforeach()
