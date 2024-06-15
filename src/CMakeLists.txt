# CMake最低版本号要求
cmake_minimum_required(VERSION 3.20)

# 项目信息
project(FudanCompiler)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-result")

# 添加包含路径
include_directories(include/backend/arm)
include_directories(include/backend/llvm)
include_directories(include/frontend)
include_directories(include/optimizer)
include_directories(include/utils/dsa)
include_directories(include/utils/printer)
include_directories(vendor/lxml)

include_directories(${PROJECT_BINARY_DIR}/include/frontend/)

# 递归构建
add_subdirectory(lib)
add_subdirectory(vendor)

set(LIBS 
  optimizer
  utils
  vendor_lxml
  frontend
  backend_arm
  backend_llvm
)
add_dependencies(${LIBS} vendor_libsysy)

set(main "main")
add_executable(${main} main.c)
target_link_libraries(${main} PUBLIC ${LIBS})