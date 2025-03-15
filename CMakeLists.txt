cmake_minimum_required(VERSION 3.31)

project(algorithm_practice)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自定义目标来创建 bin 目录
add_custom_target(create_bin_dir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin
    COMMENT "Creating bin directory"
)

# 函数：添加可执行文件并设置依赖关系
function(add_executable_with_dependencies target_name)
    add_executable(${target_name} ${ARGN})
    add_dependencies(${target_name} create_bin_dir)
    set_target_properties(${target_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin"
    )
endfunction()

# 自动扫描所有子目录
file(GLOB subdirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(subdir ${subdirs})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${subdir}/CMakeLists.txt)
            add_subdirectory(src/${subdir})
            message(STATUS "Added subdirectory: src/${subdir}")
        endif()
    endif()
endforeach()

# 设置输出目录为根目录下的bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/bin)