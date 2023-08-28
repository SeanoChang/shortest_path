# Shortest Path Finder

Welcome to the Shortest Path Finder project! This program is designed to find the shortest path from every entry in the top row of a rectangular grid to the corresponding entry in the bottom row using Dijkstra's algorithm. Then among all the paths, find the shortest path.

## Features

- **Dijkstra's Algorithm**: The program employs Dijkstra's algorithm to determine the shortest path from each entry in the top row of the grid to the corresponding entry in the bottom row.

- **Rectangular Grid**: The algorithm works on a rectangular grid where each cell has a weight associated with it. The program calculates the shortest path considering the weights.

- **Efficient Pathfinding**: Dijkstra's algorithm ensures that the shortest paths are found efficiently by exploring the grid's cells in a strategic order. 

## Getting Started

1. **Clone the Repository**: Start by cloning this repository to your local machine:

   ```bash
   git clone https://github.com/SeanoChang/shortest_path.git
   ```

2. **Navigate to the Project Directory**: Move into the project directory:

   ```bash
   cd shortest_path
   ```
   
3. **Compile and Run the Program**: Execute the compiled program:

   ```bash
   make test
   ```

4. **Outputs**:
   - `outputs/*.t` files for text grid files
   - `outputs/*.f` files for the fastest times (every top row entry)
   - `outputs/*.p` files for the fastest path

## Usage

1. **Define the Grid**: Specify the dimensions of the rectangular grid and the weights associated with each cell.

2. **Run the Program**: Use the compiled program to calculate and display the shortest paths.
