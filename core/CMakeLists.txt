project(SR_R_CORE)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC $ENV{VCPKG_ROOT}/installed/x64-windows/include
)

target_compile_definitions(${PROJECT_NAME} PUBLIC ROOT_DIR=${CMAKE_SOURCE_DIR})

message(STATUS ${PROJECT_SOURCE_DIR})
message(STATUS ${PROJECT_SOURCE_DIR}/include)

# the way to import 3rdparty
find_package(Threads REQUIRED)
find_package(TBB CONFIG REQUIRED COMPONENTS tbb)
find_package(benchmark CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
find_package(openmesh REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
target_link_libraries(${PROJECT_NAME} PUBLIC benchmark::benchmark benchmark::benchmark_main)
target_link_libraries(${PROJECT_NAME} PUBLIC TBB::tbb)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC rapidjson)
target_link_libraries(${PROJECT_NAME} PUBLIC tinyobjloader::tinyobjloader)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENMESH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${OPENMESH_INCLUDE_DIRS})
