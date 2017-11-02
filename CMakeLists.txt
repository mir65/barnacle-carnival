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
  src/data/ring.c
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
  src/dev/axis.c
  src/dev/encoder.c
  src/dev/instances.c
  src/dev/interrupt.c
  src/dev/motor.c
  src/dev/pin.c
  src/dev/pot.c
  src/dev/serial.c
  src/dev/servo.c
  src/dev/sticky.c
  src/dev/speedometer.c
  src/dev/timer.c
)

target_include_directories(
  dev
  PUBLIC
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
  test/blinky.c
  src/dev/pin.c
)

target_include_directories(
  blinky.elf
  PRIVATE
  src
  src/dev/include
)

add_executable(
  copy.elf
  test/copy.c
  src/dev/pin.c
  src/dev/interrupt.c
  src/data/vector.c
)

target_include_directories(
  copy.elf
  PRIVATE
  src
  src/data/include
)

add_executable(
  fadey.elf
  test/fadey.c
  src/dev/pin.c
  src/dev/timer.c
)

target_include_directories(
  fadey.elf
  PRIVATE
  src
  src/dev/include
)

add_executable(
  relay.elf
  test/relay.c
  src/data/vector.c
  src/dev/axis.c
  src/dev/interrupt.c
  src/dev/pin.c
  src/dev/servo.c
  src/dev/timer.c
)

target_include_directories(
  relay.elf
  PRIVATE
  src
  src/data/include
  PRIVATE
  src/dev/include
)

add_executable(
  hello.elf
  test/hello.c
  src/dev/serial.c
)

target_include_directories(
  hello.elf
  PRIVATE
  src
  src/dev/include
)

add_executable(
  displacement.elf
  test/displacement.c
  src/data/vector.c
  src/dev/encoder.c
  src/dev/interrupt.c
  src/dev/pin.c
  src/dev/serial.c
)

target_include_directories(
  displacement.elf
  PRIVATE
  src
  src/data/include
  src/dev/include
)

add_executable(
  velocity.elf
  test/velocity.c
  src/data/ring.c
  src/data/vector.c
  src/dev/encoder.c
  src/dev/interrupt.c
  src/dev/pin.c
  src/dev/serial.c
  src/dev/speedometer.c
  src/dev/timer.c
)

target_include_directories(
  velocity.elf
  PRIVATE
  src
  src/data/include
  src/dev/include
)

add_executable(
  pot.elf
  test/pot.c
  src/data/vector.c
  src/dev/pin.c
  src/dev/pot.c
  src/dev/serial.c
)

target_include_directories(
  pot.elf
  PRIVATE
  src
  src/data/include
  src/dev/include
)

set_target_properties(
  ${PROJECT_NAME}.elf
    blinky.elf copy.elf fadey.elf relay.elf hello.elf
    displacement.elf velocity.elf pot.elf
    ctrl dev main
  PROPERTIES
    COMPILE_FLAGS "-mmcu=atmega328 -Os"
    LINK_FLAGS "-L /usr/lib/gcc/avr/4.9.2 -mmcu=atmega328 -Wl,--gc-sections -mrelax -Wl,-Map,map.map"
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
add_hex_target(relay)
add_hex_target(hello)
add_hex_target(displacement)
add_hex_target(velocity)
add_hex_target(pot)
