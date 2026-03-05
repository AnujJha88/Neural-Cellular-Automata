# Neural Cellular Automata (NCA) Engine

A C++ implementation of Neural Cellular Automata featuring a custom lightweight neural network library (TinyML) and SFML-based rendering.

## 🚀 Phase One: Core Engine Implementation

This project is currently in **Phase One** of development. The primary goal of this phase has been to establish a robust, fast, and compilable foundation for the NCA simulation. 

**Current Features (Phase One):**
- **Custom Minimal ML Library (`TinyML`):** Features essential linear layers and activation functions (ReLU, Sigmoid, Tanh, Softmax) built from scratch to keep dependencies light.
- **NCA Simulation Engine:** A grid-based cellular automata model where cell states are updated simultaneously via forward passes through a neural network genome.
- **SFML 3 Rendering:** Modern SFML 3 integration for visualizing the cellular grid updates in real-time.
- **WSL/Linux Build Support:** A fully functioning `Makefile` that complies with C++17 standards, cleanly managing object files and executable targets.

## 🔮 Upcoming Phases

The architecture is designed to be extensible. Next phases incoming:

- **Phase Two - Genome Evolution & Training:** Implementation of genetic algorithms (via `GenomeOps`) to train and mutate cellular automata rules, aiming for specific pattern formations or self-repair behaviors.
- **Phase Three - Interactive UI & Controls:** Adding user interactions to draw/erase cells, tweak network weights in real-time, and pause/resume the simulation.
- **Phase Four - Performance Optimization:** Exploration of multithreading or GPU compute shaders for simulating much larger grids at high framerates.

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
