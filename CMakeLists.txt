# !!! WARNING !!! AUTO-GENERATED FILE, PLEASE DO NOT MODIFY IT AND USE
# https://docs.platformio.org/page/projectconf/section_env_build.html#build-flags
#
# If you need to override existing CMake configuration or add extra,
# please create `CMakeListsUser.txt` in the root of project.
# The `CMakeListsUser.txt` will not be overwritten by PlatformIO.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project("quadiuno" C CXX)

include(CMakeListsPrivate.txt)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/CMakeListsUser.txt)
include(CMakeListsUser.txt)
endif()

add_custom_target(
    Production ALL
    COMMAND platformio -c clion run "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    Debug ALL
    COMMAND platformio -c clion run --target debug "$<$<NOT:$<CONFIG:All>>:-e${CMAKE_BUILD_TYPE}>"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
include_directories(.pio/libdeps)
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/os")
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")
include_directories("external/WIZ_Ethernet_Library/Arduino IDE 1.5.x/Ethernet/src/")

add_executable(Z_DUMMY_TARGET ${SRC_LIST} src/os/pinprog.cpp include/pinprog.h src/database.cpp include/database.h src/scheduler.cpp src/ostime.cpp include/ostime.h include/scheduler.h src/xsynchro.cpp include/xsynchro.h src/como2.cpp src/xlane.cpp include/xlane.h src/inconma.cpp include/inconma.h src/spy.cpp include/spy.h)
