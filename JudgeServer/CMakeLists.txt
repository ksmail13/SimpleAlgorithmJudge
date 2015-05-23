cmake_minimum_required(VERSION 2.8.11)

project(JudgeServer)



include_directories(
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  -lpthread")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    BasicSocket.cc
    PollManager.cc
    ServerSocket.cc
    JudgeServer.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_REENTRANT")

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall")

add_executable(JudgeServer ${CXX_SRCS} ${C_SRCS}
    main.cc Judge.cpp Judge.h Thread.cpp Thread.h SemaphoreObejct.cpp SemaphoreObejct.h  Grading.cpp Grading.h)

