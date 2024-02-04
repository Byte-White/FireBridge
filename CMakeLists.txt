cmake_minimum_required(VERSION 3.3)
project(MagmaApp)


add_compile_definitions(MAGMA_VULKAN_ENABLED)
#add_compile_definitions(MAGMA_OPENGL_ENABLED) 
#set(MAGMA_EMSCRIPTEN ON)


add_subdirectory(vendor/Magma)
#add_subdirectory(vendor/serial)

add_executable(MagmaApp 
"app/src/main.cpp" 
"app/src/setup.cpp"
"app/src/ui.cpp" 
)


target_link_libraries(MagmaApp
PRIVATE
magma
#serial
)