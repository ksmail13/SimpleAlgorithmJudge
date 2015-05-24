cmake_minimum_required(VERSION 2.8.11)
project(JudgeServer)



include_directories(
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/
    /home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/

)

# Linker options
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} ")

# Library path
set(CMAKE_LDFLAGS "${CMAKE_LDFLAGS} -L\".\" -L\"./include/mongo\"")

# Define the CXX sources
set ( CXX_SRCS
    BasicSocket.cpp
    PollManager.cpp
    ServerSocket.cpp
    JudgeServer.cpp
    InetSocket.cpp
    jsoncpp.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_REENTRANT")

set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0")

add_executable(JudgeServer ${CXX_SRCS} ${C_SRCS}
    main.cpp Judge.cpp Judge.h Thread.cpp Thread.h SemaphoreObejct.cpp SemaphoreObejct.h  Grading.cpp Grading.h Timer.cpp Timer.h JudgeManager.cpp JudgeManager.h)

# set_property(TARGET JudgeServer PROPERTY COMPILE_OPTIONS "-pthread")
target_link_libraries(JudgeServer pthread)
target_link_libraries(JudgeServer ./lib/libmongoclient.a)