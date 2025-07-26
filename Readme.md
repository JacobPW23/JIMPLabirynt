## JIMPLabirynt

Academic project done during course of programming languages.
CLI programs for maze solving.
Example maze files in MazesToSolve directory.


### Installation and build:
In project's root directory:
```
make
make preprocessor
```

### Example of usage:
In project's root directory:

solving example:
```
bin/preprocessor -m MazesToSolve/200x200 -f 200.graph
bin/maze -s 200.graph -a dfs
```
compression example:
```
bin/preprocessor -m MazesToSolve/10x10 -f 10.bin -c 
```

### Files in project:
/src:

- Graph.c - graph functions 
- Graph.h - graph prototypes
- GraphReader.c - responsible for reading graph from files
- GraphReader.h - prototypes of functions and data structures
- GraphWriter.c - responsible for writing graph to file
- GraphWriter.h - prototypes of functions and data structures
- List.c - linear list implementation
- List.h - linear list prototypes
- MazeReader.c - responsible for reading maze from file (plain or compressed)
- MazeReader.h  - prototypes of functions and data structures
- MazeSolver.c - responsible for finding path in graph, 
- MazeSolver.h - prototypes of function
- PriorityQueue.c - priority queue implementation 
- PriorityQueue.h - priority queue prototypes
- ShowSolution.c - responsible for printing solution to console
- ShowSolution.h - prototypes of functions and data structures
- Solution.c - implementation of stack to store solution as graph nodes
- Solution.h - prototypes of functions and data structures
- main.c - main
- preprocessor.c - main file of preprocessor module, responsible for transformation form maze to graph


