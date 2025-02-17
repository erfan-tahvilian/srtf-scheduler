# SRTF (Shortest Remaining Time First) Scheduler - C++

## Overview

This project is an implementation of the **Shortest Remaining Time First (SRTF) scheduling algorithm** in **C++**. SRTF is a preemptive version of **Shortest Job Next (SJN)** where the process with the least remaining execution time is executed first. This project allows users to manually enter process details or import/export them via CSV files.

## Features

- **SRTF Scheduling Algorithm:** Implements preemptive shortest remaining time first scheduling.
- **Process Management:** Users can manually input process details including **arrival time** and **burst time**.
- **CSV Import/Export:** Allows importing and exporting process details using CSV files.
- **Gantt Chart Display:** Generates a visual **Gantt Chart** representation of the scheduling.
- **Statistics Calculation:** Computes **waiting time, turnaround time, and average values**.
- **Interactive CLI Menu:** User-friendly interface with options to choose different functionalities.

## Capabilities

1. **Manual Process Input:** Users can enter process details interactively.
2. **CSV File Handling:** Supports importing process data from a `.csv` file.
3. **Process Scheduling:** Runs the SRTF algorithm and computes scheduling metrics.
4. **Gantt Chart Representation:** Displays process execution order visually.
5. **Export Process Data:** Saves scheduling results into a `.csv` file.
6. **Performance Statistics:** Shows average waiting time and turnaround time.

## Installation

### Prerequisites

- **C++ Compiler** (e.g., g++, clang++)
- **Windows Operating System** (required due to Windows-specific library used)

### Build and Run

```sh
# Clone the repository
git clone https://github.com/erfan-tahvilian/srtf-scheduler.git
cd srtf-scheduler

# Compile the project
g++ -o srtf.exe main.cpp -std=c++17

# Run the program
srtf.exe
```

## Usage

1. **Select an option** from the main menu:
   - `[1] Shortest Remaining Time First` → Manually input process details and run the scheduler.
   - `[2] Import processes from CSV file` → Load process data.
   - `[3] Export processes to CSV file` → Save results.
   - `[4] Exit` → Close the application.
2. **If manual input is selected**, enter:
   - Number of processes.
   - Arrival time and burst time for each process.
3. **View results:**
   - **Processes Table:** Shows scheduling details.
   - **Gantt Chart:** Displays process execution sequence.
   - **Waiting & Turnaround Time Statistics.**

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

## Support & Donations

If you find this project useful and would like to support further development, you can donate via:

- **Tron (TRX) Address:** `TL8WyZLLGu8UraHAT8dCoeMsnzGpX2oAYn`
- **Binance Coin (BNB - BEP20) Address:** `0xeC4F61F21238685cC842bC236D86684e5fc2Bc57`
- **Bitcoin (BTC) Address:** `bc1q2y9m8y02fqgsr4c6533duwmqtmrhadc8k8mkt4`

Your support is greatly appreciated! 🚀