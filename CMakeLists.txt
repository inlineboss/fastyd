cmake_minimum_required(VERSION 3.2)
project(yloader)

find_package( Boost COMPONENTS regex system program_options REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

add_subdirectory(fasty)
set (RAPIDJSON_BUILD_EXAMPLES False)
add_subdirectory(ext/rapidjson)
add_subdirectory(ext/zlib)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories( ${PROJECT_NAME} PRIVATE
	"${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/ext/rapidjson/include"
)

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::system protocol net)

target_compile_features (${PROJECT_NAME} PUBLIC cxx_std_20)
