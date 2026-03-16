# CSV Trip Analyzer

A high-performance C++ data analysis tool that processes large-scale CSV trip records and ranks zones and time slots by trip frequency.

---

## Features

- **Top Zone Ranking** — Finds the most active pickup zones by trip count
- **Busy Time Slot Ranking** — Identifies the busiest (zone, hour) combinations across the dataset
- **Robust Parsing** — Handles malformed rows, missing fields, and invalid timestamps without crashing
- **High Performance** — O(n) aggregation via hash maps, O(m log m) sorting — scales to millions of rows
- **Deterministic Output** — Tie-breaking by zone ID (ascending) and hour (ascending) ensures consistent results

---

## How It Works

1. Reads a CSV file row by row
2. Extracts `PickupZoneID` and hour from `PickupDateTime`
3. Aggregates trip counts per zone and per (zone, hour) slot using `unordered_map`
4. Sorts results and returns top-k entries

---

## CSV Format

```
TripID,PickupZoneID,DropoffZoneID,PickupDateTime,DistanceKm,FareAmount
1,ZONE_A,ZONE_X,2024-01-01 09:15,1.2,10.0
2,ZONE_B,ZONE_Y,2024-01-01 23:59,2.0,12.5
```

- Header row is always present
- Rows with missing or malformed fields are skipped silently
- Time format: `YYYY-MM-DD HH:MM`
- Zone IDs are case-sensitive

---

## Build & Run

```bash
make
./analyzer
```

---

## File Structure

| File | Description |
|---|---|
| `analyzer.h` | Class declaration and data structures |
| `analyzer.cpp` | Core implementation |
| `main.cpp` | Driver program — runs analysis and prints results |
| `SmallTrips.csv` | Sample dataset for local testing |
| `Makefile` | Build configuration (C++17) |

---

## Course

**CMP2003 – Data Structures** — Bahçeşehir University, Computer Engineering
