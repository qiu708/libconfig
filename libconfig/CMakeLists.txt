set(SOURCE_FILES
    Config.cpp
        )

add_library(libconfig STATIC ${SOURCE_FILES})
target_link_libraries(libconfig yaml-cpp)

install(TARGETS libconfig DESTINATION lib)

file(GLOB HEADERS "*.h")


#message(STATUS "glob headers ${HEADERS}|headers ${HEADERS2}")
install(FILES ${HEADERS} DESTINATION include/libconfig)
add_subdirectory(test)

