# Basket Stats Manager

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Make](https://img.shields.io/badge/Build-Make-4CAF50?style=for-the-badge&logo=gnu)
![Valgrind](https://img.shields.io/badge/Memory-Zero_Leaks-success?style=for-the-badge)

A lightning-fast, memory-safe Command Line Interface (CLI) application written in pure C for managing, analyzing, and exporting basketball team and player statistics.

Built completely from scratch with **zero external dependencies**, this project showcases deep knowledge of C by implementing custom data structures (Hashtable + Vector) and a robust, custom-built JSON parser to ensure maximum performance, memory efficiency, and data integrity.

## Key Features

* **Custom Data Structures**: Utilizes a synergistic approach with a dynamic array (`Vector`) for sequential iterations and an `O(1)` `Hashtable` for lightning-fast player lookups.
* **Advanced Player Analytics**: Tracks points, rebounds (offensive/defensive), assists, steals, blocks, turnovers, fouls, and shooting percentages (1pt, 2pt, 3pt).
* **Robust Data Serialization**: Import and export team/player data dynamically to `.txt` or `.json` formats.
* **Custom JSON Engine**: Reads, parses, and validates JSON files strictly from scratch, without relying on 3rd-party libraries.
* **Memory Safe**: Strictly tested with Valgrind. Absolutely **0 memory leaks**, 0 invalid reads, and no segmentation faults.

## Project Architecture

The project follows a standard, modular C architecture, separating declarations from implementations:

```text
basket-stats/
├── include/                # Header files (.h) - Data structures and APIs
│   ├── hashtable.h         # Hashtable definitions
│   ├── vector.h            # Vector definitions
│   ├── json_parser.h       # JSON parsing API
│   ├── player.h, team.h    # Core entity definitions
│   └── ...                 # Other headers (menu, file ops, validations)
├── src/                    # Source files (.c) - Core logic and implementations
│   ├── main.c              # Application entry point
│   ├── hashtable.c         # Custom Hashtable logic
│   ├── vector.c            # Dynamic array logic
│   ├── json_parser.c       # Custom JSON parsing engine
│   ├── io.c, file_op.c     # Terminal formatting and File I/O operations
│   ├── player.c, team.c    # Player and team management
│   └── ...                 # Other modules (menus, error handling, stats)
├── tests/                  # Mock data files for parser validation & edge cases
│   ├── players.json, team.json 
│   ├── players.txt, team.txt   
│   └── empty.json, nba.json... # Edge-case data for robust testing
├── .gitignore              # Ignored files for version control
├── LICENSE                 # Project license
├── Makefile                # Build automation with automatic dependency tracking
└── run.sh                  # Bash script for execution and Valgrind checks
```


## Prerequisites

Make sure you have gcc and make installed on your system.
For memory leak checking, you will also need valgrind.
```Bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential valgrind
```

## Build the Project

The project uses a Makefile that automatically handles dependencies (.d files) and compiles the object files efficiently.
Bash

### 1. Clone the repository
git clone [https://github.com/Spyrosmaicho/basket-stats.git](https://github.com/Spyrosmaicho/basket-stats.git)

### 2. Navigate to the directory
```Bash
cd basket-stats
```
### 3. Compile the project
```Bash
make
```
## Execution

You can run the executable directly or use the provided shell script for memory checking:

### Run the application directly
```Bash
./basket
```

### OR use the shell script (runs the app through Valgrind)
```Bash
./run.sh
```

To clean the compiled object files and the executable, simply run:
```Bash
make clean
```


### Data Analytics Integration (Python)
Because the application exports data in standard CSV format, you can easily hook it up to a Python script for advanced visualizations. The repository includes a ready-to-use Python script (`plot_stats.py`) that generates a comprehensive analytics dashboard.

**Requirements for the script to work:**
* **File Name & Location:** The exported data file must be named `players.csv` and placed in the same directory as the Python script.
* **Format:** The CSV must be generated directly by this C application to ensure the column headers exactly match the script's expectations.
* **Minimum Data:** Your team must contain **at least 5 players**. This is required because the script specifically calculates and visualizes the "Top 5 Scorers" and "Top 5 Rebounders".

**How to generate the dashboard:**
Make sure you have `pandas` and `matplotlib` installed on your system (`pip install pandas matplotlib`). Then, simply run:

```bash
cd tests
python3 plot_stats.py
# Output: Dashboard has been succesfully created in 'team_dashboard.png'!