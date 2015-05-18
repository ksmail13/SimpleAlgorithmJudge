COMPILE_FLAG = -std=c++11
COMPILER = g++
OBJ_DIR = ./obj


judgeserver: main.o BasicSocket.o ServerSocket.o PollManager.o
	$(COMPILER) $(COMPILE_FLAG)  $(OBJ_DIR)/main.o $(OBJ_DIR)/BasicSocket.o ServerSocket.o PollManager.o -o %@

.c.o:
	$(COMPILER) $(COMPILE_FLAG) -g -c $<

main.o: main.cc InetSocket.h PollManager.h ServerSocket.h

BasicSocket.o: BasicSocket.cc BasicSocket.h

PollManager.o: PollManager.cc PollManager.h

ServerSocket.o: ServerSocket.cc ServerSocket.h
