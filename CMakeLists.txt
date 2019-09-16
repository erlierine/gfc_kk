cmake_minimum_required(VERSION 3.7)
project(gfc_kk)

find_package(BISON)
find_package(FLEX)


BISON_TARGET(MyParser parser.ypp ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cpp COMPILE_FLAGS -vd)
FLEX_TARGET(MyScanner lexer.lex ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "-O2 -g") 
#set(CMAKE_CXX_FLAGS "-lgvc -lcgraph -lcdt") 
set(SOURCE_FILES
        ast.cpp
        ast.hpp
        graph.cpp
        graph.hpp
        )


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS filesystem regex)

if(Boost_FOUND)
	add_executable(
	gfc_kk 
	${SOURCE_FILES}    
	${BISON_MyParser_OUTPUTS}
   	${FLEX_MyScanner_OUTPUTS}
	ast.hpp)    
	target_link_libraries(gfc_kk Boost::filesystem Boost::regex)
	target_link_libraries(gfc_kk -lgvc -lcgraph -lcdt)
endif()

