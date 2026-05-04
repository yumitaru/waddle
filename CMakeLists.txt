cmake_minimum_required(VERSION 3.16)
project(Waddle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)


find_package (Vulkan REQUIRED)



FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.9
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0.9.9.8
)
FetchContent_MakeAvailable(glm)



find_package(slang CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

add_executable(Waddle
    src/main.cpp
)




target_link_libraries(Waddle
    PRIVATE
        Vulkan::Vulkan
        glfw
        glm::glm
)


