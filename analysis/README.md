# Sorting Algorithm Analysis Tools

This folder contains Python scripts for analyzing and visualizing the results of the sorting algorithm experiments.

## Folder Structure
- `generate_graphs.py`: Script to generate performance graphs
- `requirements.txt`: Python package dependencies
- `data/`: Folder for storing CSV data files
- `graphs/`: Folder for storing generated graphs

## Setup
1. Make sure you have Python 3.6 or later installed
2. Install the required packages:
```bash
pip install -r requirements.txt
```

## Usage
1. First, run the C++ program in the parent directory to generate CSV files
2. Then, run the Python script to generate graphs:
```bash
python generate_graphs.py
```

## Generated Graphs
The script will generate three types of graphs for each test case:
1. Runtime comparison graphs
2. Operation count comparison graphs
3. Theoretical vs. actual performance graphs

All graphs will be saved in the `graphs/` directory. 