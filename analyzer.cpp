#include "analyzer.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

string TripAnalyzer::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int TripAnalyzer::extractHour(const string& dateTimeStr) {
    size_t spacePos = dateTimeStr.find(' ');
    if (spacePos == string::npos) return -1;
    size_t colonPos = dateTimeStr.find(':', spacePos);
    if (colonPos == string::npos) return -1;

    string hourStr = dateTimeStr.substr(spacePos + 1, colonPos - spacePos - 1);
    try {
        return stoi(hourStr);
    } catch (...) {
        return -1;
    }
}

void TripAnalyzer::ingestFile(const string& filePath) {
    ifstream infile(filePath);
    if (!infile.is_open()) return;

    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string segment;
        vector<string> tokens;

        while (getline(ss, segment, ',')) {
            tokens.push_back(trim(segment));
        }

        if (tokens.size() < 6) continue;

        string pickupZone = tokens[1];
        string pickupDateTime = tokens[3];

        if (pickupZone.empty()) continue;

        int hour = extractHour(pickupDateTime);
        if (hour < 0 || hour > 23) continue;

        zoneCounts[pickupZone]++;
        string slotKey = pickupZone + "_" + to_string(hour);
        slotCounts[slotKey]++;
    }
}

vector<ZoneCount> TripAnalyzer::topZones(int n) {
    vector<ZoneCount> result;
    for (const auto& pair : zoneCounts) {
        result.push_back({pair.first, pair.second});
    }

    sort(result.begin(), result.end(), [](const ZoneCount& a, const ZoneCount& b) {
        if (a.count != b.count) return a.count > b.count;
        return a.zone < b.zone;
    });

    if ((size_t)n < result.size()) result.resize((size_t)n);
    return result;
}

vector<SlotCount> TripAnalyzer::topBusySlots(int n) {
    vector<SlotCount> result;
    for (const auto& pair : slotCounts) {
        size_t pos = pair.first.find_last_of('_');
        if (pos == string::npos) continue;

        string zone = pair.first.substr(0, pos);
        int hour = stoi(pair.first.substr(pos + 1));
        result.push_back({zone, hour, pair.second});
    }

    sort(result.begin(), result.end(), [](const SlotCount& a, const SlotCount& b) {
        if (a.count != b.count) return a.count > b.count;
        if (a.zone != b.zone) return a.zone < b.zone;
        return a.hour < b.hour;
    });

    if ((size_t)n < result.size()) result.resize((size_t)n);
    return result;
}
