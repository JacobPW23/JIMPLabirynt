CC=gcc
FLAGS= -g -Wall

./bin/maze: ./src/main.o ./src/Maze.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o
	$(CC) $(FLAGS) ./src/main.o ./src/Maze.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o -o ./bin/maze
./src/main.o: ./src/main.c ./src/MazeSolver.c ./src/Graph.c
	$(CC) $(FLAGS) -c ./src/main.c -o ./src/main.o
./src/Graph.o: ./src/Graph.c
	$(CC) $(FLAGS) -c ./src/Graph.c -o ./src/Graph.o
./src/Maze.o: ./src/Maze.c
	$(CC) $(FLAGS) -c ./src/Maze.c -o ./src/Maze.o
./src/List.o: ./src/List.c 
	$(CC) $(FLAGS) -c ./src/List.c -o ./src/List.o
./src/MazeSolver.o: ./src/MazeSolver.c ./src/Graph.c
	$(CC) $(FLAGS) -c ./src/MazeSolver.c -o ./src/MazeSolver.o
clean:
	rm ./src/*.o ./bin/maze
