cmake_minimum_required(VERSION 3.7)
project(gfc_kk)
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-O2 -g") 
set(SOURCE_FILES
        main.cpp
        graph.cpp
        graph.hpp)


set(GRAPHVIZ_INCLUDE_DIR "//usr/include/graphviz")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS filesystem regex)

if(Boost_FOUND)
	add_executable(gfc_kk ${SOURCE_FILES})    
    target_link_libraries(gfc_kk Boost::filesystem Boost::regex)
endif()

