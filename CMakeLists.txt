cmake_minimum_required(VERSION 3.3)
project(FireBridge)


set(MAGMA_VULKAN ON)
set(MAGMA_OPENGL OFF) 
set(MAGMA_EMSCRIPTEN OFF)

set(DISABLE_CATKIN ON)

add_subdirectory(vendor/Magma)
add_subdirectory(vendor/serial)

add_executable(FireBridge 
"app/src/main.cpp" 
"app/src/application.h" 
"app/src/setup.cpp"
"app/src/ui.cpp" 
 "app/src/SerialMonitor.h")

target_include_directories(
	FireBridge PUBLIC
	vendor/serial/include
)

target_link_libraries(FireBridge
PRIVATE
magma
serial
)