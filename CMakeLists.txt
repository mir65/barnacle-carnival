cmake_minimum_required(VERSION 3.1)

project(backup LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(
  ${PROJECT_NAME}
  $<TARGET_OBJECTS:ctrl>
  $<TARGET_OBJECTS:dev>
  $<TARGET_OBJECTS:main>
)

add_library(
  ctrl
  OBJECT
  src/ctrl/init.c
  src/ctrl/pid.c
  src/ctrl/steering.c
  src/ctrl/velocity.c
)

target_include_directories(
  ctrl
  INTERFACE
  src/ctrl/include
  PRIVATE
  src/dev/include
)

add_library(
  dev
  OBJECT
  src/dev/instances.c
  src/dev/pin.c
)

target_include_directories(
  dev
  INTERFACE
  src/dev/include
)

add_library(
  main
  OBJECT
  src/main.c
)

target_include_directories(
  main
  PRIVATE
  src/ctrl/include
  src/dev/include
)

# Begin test

add_executable(
  test1.elf
  src/test1.c
)

set_target_properties(
  ${PROJECT_NAME} ctrl dev main test1.elf
  PROPERTIES
    COMPILE_FLAGS "-mmcu=atmega328 -Os"
    LINK_FLAGS "-mmcu=atmega328 -Wl,--gc-sections -mrelax -Wl,-Map,map.map"
)

add_custom_target(
  test1.hex
  COMMAND
    avr-objcopy -j .text -j .data -O ihex test1.elf test1.hex
  DEPENDS test1.elf
)

# End test
