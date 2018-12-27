cmake_minimum_required(VERSION 3.0.0)
project(detMat)

option(LIB "generate shared library" OFF)

if(LIB) 
  execute_process(COMMAND "mcc -W cpplib:libmrxg -T link:lib -d ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/matlab/*")
endif()

set(MATLAB_LIBS /usr/local/MATLAB/R2014b/runtime/glnxa64/libmwmclmcrrt.so)

add_executable(det ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(det PUBLIC ${CMAKE_SOURCE_DIR}/src/libmrxg.so ${MATLAB_LIBS})
target_include_directories(det PUBLIC /usr/local/MATLAB/R2014b/extern/include)
target_compile_options(det PUBLIC -O2 -std=gnu++11)
