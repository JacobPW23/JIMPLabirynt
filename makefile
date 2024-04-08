CC=gcc
FLAGS= -g -Wall

./bin/maze: ./src/main.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o ./src/Solution.o ./src/ShowSolution.o ./src/GraphReader.o
	$(CC) $(FLAGS) ./src/main.o ./src/MazeSolver.o ./src/Graph.o ./src/List.o ./src/Solution.o ./src/ShowSolution.o ./src/GraphReader.o ./src/PriorityQueue.c -o ./bin/maze -lm
./src/main.o: ./src/main.c ./src/MazeSolver.c ./src/Graph.c ./src/GraphReader.c
	$(CC) $(FLAGS) -c ./src/main.c -o ./src/main.o
./src/Graph.o: ./src/Graph.c
	$(CC) $(FLAGS) -c ./src/Graph.c -o ./src/Graph.o -lm
./src/GraphWriter.o: ./src/GraphWriter.c ./src/Graph.o
	$(CC) $(FLAGS) -c ./src/GraphWriter.c -o ./src/GraphWriter.o
./src/GraphReader.o: ./src/GraphReader.c
	$(CC) $(FLAGS) -c ./src/GraphReader.c -o ./src/GraphReader.o
./src/List.o: ./src/List.c 
	$(CC) $(FLAGS) -c ./src/List.c -o ./src/List.o
./src/MazeSolver.o: ./src/MazeSolver.c ./src/Graph.c ./src/Solution.c ./src/PriorityQueue.c
	$(CC) $(FLAGS) -c ./src/MazeSolver.c -o ./src/MazeSolver.o -lm
./src/Solution.o: ./src/Solution.c ./src/Graph.c
	$(CC) $(FLAGS) -c ./src/Solution.c -o ./src/Solution.o
./src/PriorityQueue.o: ./src/PriorityQueue.c
	$(CC) $(FLAGS) -c ./src/PriorityQueue.c -o ./src/PriorityQueue
./src/ShowSolution.o: ./src/ShowSolution.c ./src/Graph.c ./src/Solution.c
	$(CC) $(FLAGS) -c ./src/ShowSolution.c -o ./src/ShowSolution.o
./src/MazeReader.o: ./src/MazeReader.c ./src/Graph.c ./src/List.c
	$(CC) $(FLAGS) -c ./src/MazeReader.c -o ./src/MazeReader.o
preprocessor: ./src/preprocessor.o ./src/GraphWriter.o ./src/MazeReader.o ./src/List.o ./src/Graph.o
	$(CC) $(FLAGS) ./src/preprocessor.o ./src/GraphWriter.o ./src/MazeReader.o ./src/List.o ./src/Graph.o -o ./bin/preprocessor
./src/preprocessor.o: ./src/preprocessor.c ./src/Graph.c ./src/MazeReader.c ./src/GraphWriter.c
	$(CC) $(FLAGS) -c ./src/preprocessor.c -o ./src/preprocessor.o
clean:
	rm ./src/*.o ./bin/preprocessor ./bin/maze
