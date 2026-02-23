# Basket Stats Manager

![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c)
![Make](https://img.shields.io/badge/Build-Make-4CAF50?style=for-the-badge&logo=gnu)

A lightning-fast, memory-safe Command Line Interface (CLI) application written in pure C for managing, analyzing, and exporting basketball team and player statistics.

Built completely from scratch with **zero external dependencies**, this project showcases deep knowledge of C by implementing custom data structures (Hashtable + Vector) and a robust, custom-built JSON parser to ensure maximum performance, memory efficiency, and data integrity.

## Key Features

* **Custom Data Structures**: Utilizes a synergistic approach with a dynamic array (`Vector`) for sequential iterations and an `O(1)` `Hashtable` for lightning-fast player lookups.
* **Advanced Player Analytics**: Tracks points, rebounds, assists, steals, blocks, turnovers, fouls, and shooting percentages.
* **Robust Data Serialization**: Import and export team/player data dynamically to `.txt` or `.json` formats.
* **Memory Safe**: Strictly tested with Valgrind. Absolutely **0 memory leaks**, 0 invalid reads, and no segmentation faults.
* **Interactive Web Dashboard**: Includes a modern Data Analytics GUI built with Python and Streamlit to visualize the exported data, run complex queries, and compare players head-to-head.

## Project Architecture

The project follows a standard, modular C architecture, separating declarations from implementations:

```text
basket-stats/
├── .github/workflows/      # CI/CD pipelines
│   └── c-build.yml         # GitHub Actions automated build testing
├── analytics/              # Data visualization and Web GUI (Python)
│   ├── app.py              # Streamlit Web Application (Interactive Dashboard)
│   ├── players.csv         # Exported data file from the C backend
│   └── nba.csv             # Exported real NBA data
├── include/                # Header files (.h) - Data structures and APIs
│   ├── hashtable.h         # Hashtable definitions
│   ├── vector.h            # Vector definitions
│   ├── json_parser.h       # Custom JSON parsing API
│   └── ...                 # Core entity and utility headers
├── run/                    # Build and Execution directory
│   ├── Makefile            # Build automation for the C program
│   └── run.sh              # Bash script for execution and Valgrind memory checks
├── src/                    # Source files (.c) - Core logic and implementations
│   ├── main.c              # Application entry point
│   ├── hashtable.c         # Custom Hashtable logic (O(1) lookups)
│   ├── vector.c            # Dynamic array logic
│   └── ...                 # Logic for menus, file ops, and statistics
├── tests/                  # API integrations and mock data
│   ├── fetch_nba.py        # Python script to fetch real-time data from the NBA API
│   ├── nba.json            # Real NBA player data formatted for the C parser
│   └── new.txt             # Mock data for robustness testing
├── .gitignore              # Ignored files for version control
├── LICENSE                 # Project license
└── README.md               # Project documentation
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
cd basket-stats/run
```
### 3. Compile the project
```Bash
make
```
## Execution

You can run the executable directly or use the provided shell script for memory checking(make sure you are still inside the run/ folder):

### Run the application directly
```Bash
./basket
```

### OR use the shell script (runs the app through Valgrind)
```Bash
./run.sh
```

To clean the compiled object files, simply run the following instruction inside the `run/` directory:
```Bash
make clean
```


### Data Analytics Web Dashboard & NBA API

This project goes beyond a simple C backend by providing a full end-to-end data pipeline. It features a modern, interactive Web Dashboard built with Python, and the ability to fetch real-world data directly from the NBA.

####  Fetching Real NBA Data (Optional)
Instead of typing players manually, you can populate the C application with real NBA statistics from the current season.
Ensure you have the API library installed: `pip install nba_api`
```bash
# Navigate to the tests folder
cd tests

# Run the fetch script
python3 fetch_nba.py
```
This will generate `nba.json`, which contains the top NBA players accurately formatted. You can then load this file inside the C application and interact with real stats!

#### Launching the Web Dashboard

The C application exports the memory-stored data into a clean CSV format. You can use the included Python Web Dashboard to interact with this data visually.

**Requirements**:

Export your data from the C application and ensure it is saved as players.csv (or nba.csv) inside the analytics/ folder.

**Installation & Execution**:

Ensure you have the required Python libraries for the GUI and interactive charts:
```Bash
pip install streamlit pandas matplotlib numpy plotly scikit-learn
```
Then, navigate to the analytics folder and start the Streamlit server:
```Bash
cd analytics
streamlit run app.py
```
This will automatically open a local web page in your default browser featuring:

- **Season Highlights (KPIs)**: Instant top-level metrics calculating the Top Scorer, Best Playmaker, and Defensive Anchor of the loaded roster.

- **Interactive Plotly Charts**: Select and view advanced metrics. Hover over data points to see details, zoom in, and analyze Player Profiles (Radar Charts), Playmaking Efficiency, and True Shooting %.

- **Advanced Database Queries**: Use live UI sliders to filter the entire roster based on multiple statistical categories (Points, Rebounds, Assists, Steals, Percentages). Includes a one-click CSV download for the filtered results.

- **Pro Head-to-Head Cards**: Compare two players side-by-side with conditional color-coded formatting to instantly see who wins in each statistical category.

- **AI Scouting & Clustering (Machine Learning)**: An advanced ML pipeline built with `scikit-learn`. Features a **Player Similarity Engine** (using Cosine Similarity) to find statistical "twins" across the league, and **Archetype Clustering** (using PCA dimensionality reduction and K-Means) to automatically group players into distinct playstyles on an interactive 2D scatter plot.