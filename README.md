# Maze Router

This project implements a grid-based maze router using **Lee's algorithm** and **Soukup's algorithm**, supporting shortest path visualization.

## Features
- Grid-based maze routing
- Only visualizes the **shortest path**, not all visited nodes
- Supports custom start/end positions and obstacle placement
- ASCII output for terminal-based visualization
- Outputs path length if routing is successful

## Project Structure
```
maze_router_cpp/
├── main.cpp                # C++ source code for router
├── examples/
│   └── example1.txt        # Example input file
```

## Input Format (`examples/example1.txt`)
- First line: grid dimensions (rows cols)
- Next rows×cols entries: 0 (empty) or 1 (obstacle)
- Final line: startX startY endX endY
- Left-bottom edge is (0, 0)

**Example:**
```
5 7
0 0 0 0 0 0 0
0 1 1 1 0 1 1
0 0 0 0 0 0 0
1 1 1 1 1 1 0
0 0 0 0 0 0 0
0 0 6 4
```

## How to Run
```bash
g++ -std=c++11 -o router main.cpp
./router
```
- Select algorithm
```bash
./router lee       # Uses Lee's Algorithm (default)
./router soukup    # Uses Soukup’s Algorithm
```

## Output
- Prints the path length and ASCII Visualization if a route is found
- Example:
```bash
[Lee] Path found with length: 14

Visualized Path Grid:
....**E
.###*##
....***
######*
S******
```
- Saves ASCII Visualization to output/output_grid.txt

