cmake_minimum_required(VERSION 3.10)

project(arpc C CXX)

message("PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")

add_executable(client 
${PROJECT_SOURCE_DIR}/src/client.cpp
${PROJECT_SOURCE_DIR}/src/abup_rpc_service.cpp
)
target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/inc/)
target_link_libraries(client PRIVATE 
${PROJECT_SOURCE_DIR}/lib/librpc.so 
stdc++
)

add_executable(server 
${PROJECT_SOURCE_DIR}/src/server.cpp
${PROJECT_SOURCE_DIR}/src/abup_rpc_service.cpp
)
target_include_directories(server PRIVATE ${PROJECT_SOURCE_DIR}/inc/)
target_link_libraries(server PRIVATE 
    ${PROJECT_SOURCE_DIR}/lib/librpc.so 
    stdc++
)