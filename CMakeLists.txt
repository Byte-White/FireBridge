cmake_minimum_required(VERSION 3.3)
project(FireBridge)


#add_compile_definitions(MAGMA_VULKAN_ENABLED)
add_compile_definitions(MAGMA_OPENGL_ENABLED) 
#set(MAGMA_EMSCRIPTEN ON)

set(DISABLE_CATKIN ON)

add_subdirectory(vendor/Magma)
add_subdirectory(vendor/serial)

add_executable(FireBridge 
"app/src/main.cpp" 
"app/src/application.h" 
"app/src/setup.cpp"
"app/src/ui.cpp" 
)

target_include_directories(
	FireBridge PUBLIC
	vendor/serial/include
)

target_link_libraries(FireBridge
PRIVATE
magma
serial
)