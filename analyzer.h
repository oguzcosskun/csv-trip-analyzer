#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include <unordered_map>

struct ZoneCount {
    std::string zone;
    int count;
};

struct SlotCount {
    std::string zone;
    int hour;
    int count;
};

class TripAnalyzer {
private:
    std::unordered_map<std::string, int> zoneCounts;
    std::unordered_map<std::string, int> slotCounts;

    std::string trim(const std::string& str);
    int extractHour(const std::string& dateTimeStr);

public:
    void ingestFile(const std::string& filePath);
    std::vector<ZoneCount> topZones(int n);
    std::vector<SlotCount> topBusySlots(int n);
};

#endif
