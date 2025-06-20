cmake_minimum_required(VERSION 3.20)
project(Underdog VERSION 1.0.0 LANGUAGES CXX)

# Настройки стандарта C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# macOS specific Vulkan SDK path for Homebrew
if(APPLE)
    set(VULKAN_SDK $ENV{VULKAN_SDK})
    if(NOT VULKAN_SDK)
        set(VULKAN_SDK "/opt/homebrew/opt/vulkan-loader")
    endif()
    set(Vulkan_INCLUDE_DIRS "/opt/homebrew/opt/vulkan-headers/include")
    set(Vulkan_LIBRARIES "/opt/homebrew/opt/vulkan-loader/lib/libvulkan.dylib")
endif()

# Поиск необходимых пакетов
find_package(Vulkan REQUIRED)

# Проверка Vulkan
if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan not found! Please install Vulkan SDK")
endif()

# Обработка GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

# Добавление исполняемого файла
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/vulkan_support.cpp
    include/vulkan_support.hpp
    include/components.hpp
)

# Copy shaders to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
)

# Настройка include директорий
target_include_directories(${PROJECT_NAME} PRIVATE
    ${Vulkan_INCLUDE_DIRS}
    ${glfw_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PRIVATE src
)

# Линковка библиотек
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Vulkan_LIBRARIES}
    glfw
    ${CMAKE_DL_LIBS}
)

# macOS specific settings
if(APPLE)
    find_library(METAL_LIBRARY Metal REQUIRED)
    find_library(FOUNDATION_LIBRARY Foundation REQUIRED)
    find_library(QUARTZCORE_LIBRARY QuartzCore REQUIRED)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${METAL_LIBRARY}
        ${FOUNDATION_LIBRARY}
        ${QUARTZCORE_LIBRARY}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
    )
endif()

# Дополнительные настройки для Windows
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        opengl32.lib  # Required on Windows
    )
endif()
