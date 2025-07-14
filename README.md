# Variations of the n×2-Puzzle and Appropriate Algorithms
Bachelor's Thesis by Viktor Rieß at 
Goethe University Frankfurt, Department of Computer Science and Mathematics.

An implementation of algorithms for solving 2-column sliding puzzles (n×2 puzzles) written in C++.  
Features a web application for playing the puzzle and visualizing the algorithms.
This project was developed as part of my Bachelor's thesis.


## Requirements 
- **C++20 compatible compiler** 
- **CMake >= 3.29**

## Cloning the Repository and Building the Project (on Linux, Mac, and WSL)
Open the terminal in any directory and execute the following commands:  

### On Linux, Mac, and WSL:
`git clone https://github.com/Vikplusplus/nx2-puzzle-code.git`  
`cd nx2-puzzle-code`  
`mkdir build`  
`cd build`   
`cmake ..`  
`make`  

### On Windows, using MinGW-w64:
`git clone https://github.com/Vikplusplus/nx2-puzzle-code.git`  
`cd nx2-puzzle-code`  
`mkdir build`  
`cd build`   
`cmake .. -G "MinGW Makefiles"`  
`cmake --build .`  

## Run the Code
After building, open the terminal in the build directory and run:  
./nx2-puzzle-code

Now, go to https://localhost:8080 to access the web application.

## Project Structure

- `Algorithms/` — Source code for algorithms
- `WebAPI/` — Source code for the Web API
- `main.cpp` — Launching the web application
- `CMakeLists.txt` — CMake configuration
- `LICENSE` — License and usage information
- `.gitignore` — Git ignore
- `README.md`          

## License
This project is licensed under the MIT License. See `LICENSE` for details.

## Acknowledgements
- `nlohmann/json.hpp` for JSON handling
- `yhirose/httplib.h` for HTTP server functionality