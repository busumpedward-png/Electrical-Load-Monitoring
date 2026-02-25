# Electrical Load Monitoring & Billing System (C++)

This is a console-based C++ program that simulates:

1. Electrical load monitoring (appliances and their energy use)
2. Electricity billing based on a tariff per kWh

Data is stored using text files with `fstream`.

---

## Project Files

- `main.cpp` → main program
- `appliances.txt` → stores appliance records
- `billing_summary.txt` → stores saved billing summaries

---

## Features

### 1. Appliance Management

- Register appliances (name, watts, hours/day)
- View all appliances
- Search appliance by name

### 2. Load & Energy Calculation

- Stores power rating in watts (W)
- Stores daily usage hours (0–24)
- Calculates energy in kilowatt-hours (kWh):
  - `kWh/day = (Watts / 1000) * Hours`
- Calculates total daily energy for all appliances

### 3. Billing

- Accepts electricity tariff per kWh (must be positive)
- Calculates total daily cost:
  - `Daily Cost = Total kWh/day * Tariff`
- Shows detailed billing breakdown (per appliance)
- Shows optional 30-day estimate
- Allows saving billing summary to `billing_summary.txt`

### 4. File Storage

- Appliances are saved in `appliances.txt`
- Appliances are loaded automatically when the program starts
- Billing summaries are appended to `billing_summary.txt` when saved

### 5. Validation Rules

- Appliance name must not be empty
- Power rating must be greater than 0
- Usage hours must be between 0 and 24
- Tariff must be positive
- Invalid menu choices are handled properly

---

## How to Run (Git Bash / Windows)

1. Open Git Bash in the project folder.
2. Compile:

```bash
g++ -std=c++17 -o app.exe main.cpp
```
