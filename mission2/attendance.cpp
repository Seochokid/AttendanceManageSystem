#include "attendance.h"

AttendanceRecord inputData[MAX_INPUT];
int inputCount = 0;

void AttendanceManager::manageAttendance(string inputPath) {
    readAttendanceData(inputPath);
    calculateTotalPoints();
    assignGrades();
    printResults();
}

void AttendanceManager::calculateBonusPoints() {
    for (int i = 1; i <= playerCount; i++) {
        if (attendanceByDay[i][WEDNESDAY] >= WEDNESDAY_BONUS_THRESHOLD) {
            playerPoints[i] += WEDNESDAY_BONUS_POINTS;
        }

        int weekendAttendance = attendanceByDay[i][SATURDAY] + attendanceByDay[i][SUNDAY];
        if (weekendAttendance >= WEEKEND_BONUS_THRESHOLD) {
            playerPoints[i] += WEEKEND_BONUS_POINTS;
        }
    }
}

void AttendanceManager::calculateDefaultPoints() {
    string playerName, weekday;
    int playerId, weekdayIndex, points;
    for (int i = 0; i < inputCount; i++) {
        playerName = inputData[i].playerName;
        weekday = inputData[i].weekday;
        playerId = getPlayerId(playerName);
        weekdayIndex = getWeekdayIndex(weekday);
        if (weekdayIndex == -1) {
            cout << "Invalid weekday: " << weekday << "\n";
            continue; // Skip invalid weekdays
        }
        points = getWeekdayPoints(weekday);
        if (weekdayIndex == WEDNESDAY) {
            wednesdayAttendanceCount[playerId]++;
        }
        else if (weekdayIndex == SATURDAY || weekdayIndex == SUNDAY) {
            weekendAttendanceCount[playerId]++;
        }
        attendanceByDay[playerId][weekdayIndex]++;
        playerPoints[playerId] += points;
    }
}

int AttendanceManager::getWeekdayIndex(const string& weekday) {
    if (weekday == "monday") return MONDAY;
    if (weekday == "tuesday") return TUESDAY;
    if (weekday == "wednesday") return WEDNESDAY;
    if (weekday == "thursday") return THURSDAY;
    if (weekday == "friday") return FRIDAY;
    if (weekday == "saturday") return SATURDAY;
    if (weekday == "sunday") return SUNDAY;
    return -1; // Invalid weekday
}

int AttendanceManager::getWeekdayPoints(const string& weekday) {
    if (weekday == "wednesday") return WEDNESDAY_POINTS;
    if (weekday == "saturday" || weekday == "sunday") return WEEKEND_POINTS;
    return DEFAULT_POINTS;
}

int AttendanceManager::getPlayerId(const string& playerName) {
    if (playerIdMap.count(playerName) == 0) {
        playerIdMap[playerName] = ++playerCount;
        playerNames[playerCount] = playerName;
    }
    return playerIdMap[playerName];
}

void AttendanceManager::printRemovedPlayer() {
    cout << "\n";
    cout << "Removed player\n";
    cout << "==============\n";
    for (int i = 1; i <= playerCount; i++) {
        if (playerGrades[i]->getName() == "NORMAL" &&
            wednesdayAttendanceCount[i] == 0 &&
            weekendAttendanceCount[i] == 0) {
            cout << playerNames[i] << "\n";
        }
    }
}

void AttendanceManager::printNameAndPoint() {
    for (int i = 1; i <= playerCount; i++) {
        cout << "NAME : " << playerNames[i] << ", ";
        cout << "POINT : " << playerPoints[i] << ", ";
        cout << "GRADE : " << playerGrades[i]->getName() << "\n";
    }
}

void AttendanceManager::printResults() {
    printNameAndPoint();
    printRemovedPlayer();
}

void AttendanceManager::assignGrades() {
    for (int i = 1; i <= playerCount; i++) {
        playerGrades[i] = gradeManager.determineGrade(playerPoints[i]);
    }
}

void AttendanceManager::calculateTotalPoints() {
    calculateDefaultPoints();
    calculateBonusPoints();
}

void AttendanceManager::readAttendanceData(string inputPath) {
    ifstream fin(inputPath);
    for (int i = 0; i < MAX_INPUT; i++, inputCount++) {
        string playerName, weekday;
        fin >> inputData[i].playerName >> inputData[i].weekday;
        if (fin.eof()) {
            break;
        }
    }
}