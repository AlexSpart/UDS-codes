if(NOT TARGET Boost::system)
    message(STATUS "Skip build of socktap because of missing Boost::system dependency")
    return()
endif()

if(NOT TARGET Boost::program_options)
    message(STATUS "Skip build of socktap because of missing Boost::program_options dependency")
    return()
endif()

find_package(Threads REQUIRED)

option(DEBUG "Option description" OFF)
if(DEBUG)
  message("Compiling with DEBUG mode ON")
  add_definitions(-DDEBUG)
else()
   message("Compiling with DEBUG mode OFF")
endif()

add_library(quadkeymapper-common STATIC
    quadkey_handler.cpp
    quadkey.hpp
)

add_executable(quadkeymapper
    quadkey_service.cpp
)


target_link_libraries(quadkeymapper-common PUBLIC Boost::system Boost::program_options Threads::Threads )
#target_include_directories(quadkeymapper-common PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})
target_link_libraries(quadkeymapper quadkeymapper-common )
#target_include_directories(quadkeymapper PUBLIC ${LIBMONGOCXX_INCLUDE_DIRS})

#install(TARGETS quadkeymapper EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS quadkeymapper DESTINATION bin)

