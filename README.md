
# Ising_DeepL

## Project Overview
The Ising_DeepL project combines computational physics and deep learning to study the Ising model. The project simulates the Ising model using the Metropolis algorithm, implemented in C++, to generate spin configurations at various temperatures. These configurations are then classified using a Convolutional Neural Network (CNN) implemented in TensorFlow within a Jupyter notebook.

## Contents
- `ising.cc`: C++ source file for simulating the Ising model with the Metropolis algorithm.
- `ising.h`: Header file for the Ising model C++ implementation.
- `Ising_CNN.ipynb`: Jupyter notebook with TensorFlow CNN for classifying Ising model configurations.

## Requirements
- C++ Compiler (e.g., g++, clang)
- Python 3.x
- TensorFlow 
- NumPy
- Matplotlib
- pandas

## Installation
To get started, clone the repository to your local machine:

```
git clone https://github.com/sarthakj1997/Ising_DeepL.git
cd Ising_DeepL
```

### Setting Up the C++ Environment
Ensure you have a C++ compiler installed and compile the Ising model source code:

```
g++ -o ising ising.cc
```

### Setting Up the Python Environment
Create a virtual environment and install the required Python packages:

```
python -m venv venv
source venv/bin/activate  # On Windows use `venv\Scripts\activate`
pip install -r requirements.txt
```

## Usage
### Generating Configurations
To generate configurations with the Ising model, run the compiled C++ program with the necessary arguments:

```
./ising <Lattice Dimension> <size of every lattice dimension> <No. of MC sweeps> <Save Frequency> <tempStart> <tempEnd> <Step size of temp> <critical temp> <thermalization>
```

### Classifying Configurations
Open the Jupyter notebook to train and evaluate the CNN model for classifying the configurations:

```
jupyter notebook Ising_CNN.ipynb
```

Instructions within the notebook will guide you through the process.

