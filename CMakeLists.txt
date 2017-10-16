cmake_minimum_required(VERSION 3.1)

project(backup LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_executable(
  ${PROJECT_NAME}.elf
  $<TARGET_OBJECTS:ctrl>
  $<TARGET_OBJECTS:data>
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
  data
  OBJECT
  src/data/vector.c
)

target_include_directories(
  data
  PUBLIC
  src/data/include
)

add_library(
  dev
  OBJECT
  src/dev/instances.c
  src/dev/interrupt.c
  src/dev/pin.c
)

target_include_directories(
  dev
  INTERFACE
  src/dev/include
  PRIVATE
  src/data/include
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

add_executable(
  blinky.elf
  src/blinky.c
  src/dev/pin.c
)

add_executable(
  copy.elf
  src/copy.c
  src/dev/pin.c
  src/dev/interrupt.c
  src/data/vector.c
)

target_include_directories(
  copy.elf
  PRIVATE
  src/data/include
)

add_executable(
  fadey.elf
  src/fadey.c
  src/dev/pin.c
)

set_target_properties(
  ${PROJECT_NAME}.elf blinky.elf copy.elf fadey.elf ctrl dev main
  PROPERTIES
    COMPILE_FLAGS "-mmcu=atmega328 -Os"
    LINK_FLAGS "-mmcu=atmega328 -Wl,--gc-sections -mrelax -Wl,-Map,map.map"
)

macro(add_hex_target _target)
  add_custom_target(
    ${_target}.hex
    COMMAND
      avr-objcopy -j .text -j .data -O ihex ${_target}.elf ${_target}.hex
    DEPENDS ${_target}.elf
  )
endmacro(add_hex_target)

add_hex_target(${PROJECT_NAME})
add_hex_target(blinky)
add_hex_target(copy)
add_hex_target(fadey)
