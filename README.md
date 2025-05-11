# Maze Router

This project implements a basic maze routing algorithm (Lee's Algorithm and Soukup's Algorithm) in C++

## Features
- Grid-based maze routing
- Avoids obstacles
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
- Prints the path length if a route is found.
- Example: `Path found with length: 14`

