file(GLOB sources "*.cpp")

add_subdirectory(Tank)

include_directories(${CMAKE_SOURCE_DIR}/src/Tank)
link_directories(${CMAKE_BINARY_DIR}/src/Tank)

add_executable(mythos ${sources})

target_link_libraries(mythos tank ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
if(Cotire)
    cotire(mythos)
endif(Cotire)
