cmake_minimum_required(VERSION 2.8.11)

project(JudgeServer)



include_directories(
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS}  ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" ")

# Define the CXX sources
set ( CXX_SRCS
    BasicSocket.cc
    main.cc
    PollManager.cc
    ServerSocket.cc
)

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall --std=c++11")

add_executable(JudgeServer ${CXX_SRCS} ${C_SRCS})

