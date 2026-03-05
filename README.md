# Neural Cellular Automata (NCA) Engine

A C++ implementation of Neural Cellular Automata featuring a custom lightweight neural network library (TinyML) and SFML-based rendering.

## 🚀 Phase Two Completed: Genome Evolution & Training

This project has successfully completed **Phase Two**, which introduced genetic algorithms to evolve Neural Cellular Automata to achieve population homeostasis.

**Current Features (Phase Two Additions):**
- **Genetic Algorithms (`PopulationManager` & `GenomeOps`):** Supports crossover and mutation of neural network weights across populations. Includes multi-threaded evaluation using `std::async` for fast parallel genome testing.
- **Homeostasis Fitness Function:** Evaluates genomes over a sequence of time steps to ensure continuous stability (e.g., maintaining a perfectly balanced cell count of 83), rather than just hitting a target on a single frame.
- **Improved Neural Update Rules:** Includes Stochastic Update Masks (50% async update chance) and Alive Masks (strict death for cells with no living neighbors) to ensure robust and realistic cellular growth.
- **Training UI Controls:** The SFML window now supports interactive training commands to mutate, randomize, and manually trigger population evolution in real-time.

## 🔮 Upcoming Phases

The architecture is designed to be extensible. Next phases incoming:

- **Phase Three - Target Matrix Evolution:** Upgrading the fitness function to perform pixel-perfect comparisons against a target image or shape matrix, allowing the NCA to learn how to grow into and repair specific shapes (e.g. growing a lizard or a spaceship).



## 🛠️ Building the Project (WSL / Linux)

### Prerequisites
Make sure you have a modern GCC version (supporting C++17) and the SFML 3 development libraries installed on your system.

```bash
# Example for Debian/Ubuntu based systems
sudo apt update
sudo apt install build-essential libsfml-dev
```

### Compilation

The project uses a standard `Makefile`. It is configured to place all intermediate object files in the `obj/` directory to keep the source tree clean.

To build the executable:
```bash
make
```

### Running
After a successful build, the engine executable will be placed in the `build/` directory:
```bash
./build/NCAEngine
```

## 🧹 Cleaning the Build Space

To remove all compiled object files and the generated executable, run:
```bash
make clean
```
