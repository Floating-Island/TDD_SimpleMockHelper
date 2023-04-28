# the name of the target operating system, version and processor
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# which compilers to use for C and C++
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
set(CMAKE_C_COMPILER     "${TOOLCHAIN_PREFIX}-gcc")
set(CMAKE_CXX_COMPILER   "${TOOLCHAIN_PREFIX}-g++")

# use static flag so executables have dlls inside them
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  /usr/${TOOLCHAIN_PREFIX} /usr/include)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)