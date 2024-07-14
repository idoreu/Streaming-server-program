CC = g++
OBJS = StreamingDBa1.o maina1.o
EXEC = StreamingDBa1
DEBUG= -g
COMP_FLAG = -std=c++11 -DNDEBUG -Wall $(DEBUG)
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
maina1.o : StreamingDBa1.o
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
StreamingDBa1.o : StreamingDBa1.h AVLTree.o movie.o user.o group.o
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
AVLTree.o : AVLTree.h AVLTree.cpp
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
movie.o : AVLTree.h AVLTree.cpp movie.h movie.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
user.o : user.h user.cpp group.h group.cpp wet1util.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
group.o : AVLTree.h AVLTree.cpp wet1util.h group.h user.h user.cpp 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)