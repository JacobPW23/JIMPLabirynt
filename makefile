CC=gcc
COPT= -ggdb -Wall -ansi -std=c99

./bin/maze: ./src/main.o ./src/Maze.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o ./src/format.o
	$(CC) $(COPT) ./src/main.o ./src/Maze.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o -o $@
	$(CC) $(COPT) ./src/format.o ./src/Maze.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o -o ./bin/format
graphtest:
	$(CC) $(COPT) -c ./src/graphTest.c ./src/Graph.c ./src/List.c
	$(CC) $(COPT)  graphTest.o ./src/Graph.o ./src/List.o -o $@
	./$@
	rm $@ *.o
list_test:
	$(CC) $(COPT) -c ./src/list_test.c ./src/List.c
	$(CC) $(COPT)  list_test.o ./src/List.o -o $@
	./$@
	rm $@ *.o
	
./src/main.o: ./src/main.c
./src/main.o: ./src/main.c
./src/Graph.o: ./src/Graph.c
./src/Maze.o: ./src/Maze.c
./src/List.o: ./src/List.c
./src/MazeSolver.o: ./src/MazeSolver.c
./src/format.o: ./src/format.c
clean:
	rm ./src/*.o ./bin/*
