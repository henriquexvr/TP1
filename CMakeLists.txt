cmake_minimum_required(VERSION 3.10)
project(normalize C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set optimization flags
if(MSVC)
    # Windows Visual Studio
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /W4")
    message(STATUS "Compiler: MSVC (Windows)")
elseif(APPLE)
    # macOS with Clang
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra")
    message(STATUS "Compiler: Clang (macOS)")
else()
    # Linux with GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra")
    message(STATUS "Compiler: GCC (Linux)")
endif()

# Detect CPU architecture
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")

# Determine SIMD implementation based on architecture
set(SIMD_SOURCE "")
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|amd64|x86|i686")
    # x86/x86-64 architecture
    message(STATUS "Architecture: x86-64 (SSE)")
    set(SIMD_SOURCE "src/normalizeSse.c")
    
    # Add SSE flags if not on Windows (MSVC handles it automatically)
    if(NOT MSVC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse")
    endif()
    
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|aarch64|ARM64")
    # ARM architecture
    message(STATUS "Architecture: ARM (NEON)")
    set(SIMD_SOURCE "src/normalizeSseArm.c")
    
    # Add NEON flags if not on Windows
    if(NOT MSVC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a+simd")
    endif()
    
else()
    message(WARNING "Unknown architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    message(WARNING "Falling back to Quake implementation without SIMD")
    # Don't add SIMD, use fallback to Quake only
endif()

# Source files
set(SOURCES
    src/main.c
    src/csvReader.c
    src/normalizeBaseline.c
    src/normalizeQuake.c
)

# Add SIMD source if available
if(SIMD_SOURCE)
    list(APPEND SOURCES ${SIMD_SOURCE})
endif()

# Create executable
add_executable(normalize ${SOURCES})

# Link math library
target_link_libraries(normalize m)

# Print compilation summary
message(STATUS "============================================")
message(STATUS "Project: normalize")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "SIMD Implementation: ${SIMD_SOURCE}")
message(STATUS "============================================")
