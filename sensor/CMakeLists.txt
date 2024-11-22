
project(kestrel-sensor VERSION 0.1)

add_executable(kestrel-sensor 
    main.cpp
)
target_include_directories(
kestrel-sensor 
PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(kestrel-sensor
PUBLIC
    yaml-cpp::yaml-cpp
    libkds
)
