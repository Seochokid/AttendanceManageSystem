#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using std::cout;
using std::ifstream;
using std::string;
using std::map;

struct AttendanceRecord {
	string playerName;
	string weekday;
};

enum GradeLevel {
	NORMAL = 0,
	SILVER = 1,
	GOLD = 2
};

enum WeekdayIndex {
	MONDAY = 0,
	TUESDAY = 1,
	WEDNESDAY = 2,
	THURSDAY = 3,
	FRIDAY = 4,
	SATURDAY = 5,
	SUNDAY = 6
};

const int MAX_INPUT = 500;
const int MAX_PLAYERS = 100;
const int TOTAL_WEEKDAYS = 7;

const int GOLD_THRESHOLD = 50;
const int SILVER_THRESHOLD = 30;

const int WEDNESDAY_POINTS = 3;
const int WEEKEND_POINTS = 2;
const int DEFAULT_POINTS = 1;

const int WEDNESDAY_BONUS_THRESHOLD = 10;
const int WEEKEND_BONUS_THRESHOLD = 10;
const int WEDNESDAY_BONUS_POINTS = 10;
const int WEEKEND_BONUS_POINTS = 10;

AttendanceRecord inputData[MAX_INPUT];
map<string, int> playerIdMap;
int playerCount = 0;
string playerNames[MAX_PLAYERS];
int attendanceByDay[MAX_PLAYERS][TOTAL_WEEKDAYS];
int playerPoints[MAX_PLAYERS];
int playerGrades[MAX_PLAYERS];
int wednesdayAttendanceCount[MAX_PLAYERS];
int weekendAttendanceCount[MAX_PLAYERS];

string getGradeName(int grade) {
	switch (grade) {
	case GOLD: return "GOLD";
	case SILVER: return "SILVER";
	default: return "NORMAL";
	}
}

int getWeekdayIndex(const string& weekday) {
	if (weekday == "monday") return MONDAY;
	if (weekday == "tuesday") return TUESDAY;
	if (weekday == "wednesday") return WEDNESDAY;
	if (weekday == "thursday") return THURSDAY;
	if (weekday == "friday") return FRIDAY;
	if (weekday == "saturday") return SATURDAY;
	if (weekday == "sunday") return SUNDAY;
	return -1;
}

int getWeekdayPoints(const string& weekday) {
	if (weekday == "wednesday") return WEDNESDAY_POINTS;
	if (weekday == "saturday" || weekday == "sunday") return WEEKEND_POINTS;
	return DEFAULT_POINTS;
}

int getPlayerId(const string& playerName) {
	if (playerIdMap.count(playerName) == 0) {
		playerIdMap[playerName] = ++playerCount;
		playerNames[playerCount] = playerName;
	}
	return playerIdMap[playerName];
}

void printRemovedPlayer() {
	cout << "\n";
	cout << "Removed player\n";
	cout << "==============\n";
	for (int i = 1; i <= playerCount; i++) {
		if (playerGrades[i] == NORMAL &&
			wednesdayAttendanceCount[i] == 0 &&
			weekendAttendanceCount[i] == 0) {
			cout << playerNames[i] << "\n";
		}
	}
}

void printNameAndPoint() {
	for (int i = 1; i <= playerCount; i++) {
		cout << "NAME : " << playerNames[i] << ", ";
		cout << "POINT : " << playerPoints[i] << ", ";
		cout << "GRADE : " << getGradeName(playerGrades[i]) << "\n";
	}
}

void printResults() {
	printNameAndPoint();
	printRemovedPlayer();
}

void assignGrades() {
	for (int i = 1; i <= playerCount; i++) {
		if (playerPoints[i] >= GOLD_THRESHOLD) {
			playerGrades[i] = GOLD;
		}
		else if (playerPoints[i] >= SILVER_THRESHOLD) {
			playerGrades[i] = SILVER;
		}
		else {
			playerGrades[i] = NORMAL;
		}
	}
}

void calculateBonusPoints() {
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

void calculateDefaultPoints() {
	string playerName, weekday;
	int playerId, weekdayIndex, points;
	for (int i = 0; i < MAX_INPUT; i++) {
		playerName = inputData[i].playerName;
		weekday = inputData[i].weekday;
		playerId = getPlayerId(playerName);
		weekdayIndex = getWeekdayIndex(weekday);
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

void calculateTotalPoints() {
	calculateDefaultPoints();
	calculateBonusPoints();
}

void readAttendanceData() {
	ifstream fin("attendance_weekday_500.txt");
	for (int i = 0; i < MAX_INPUT; i++) {
		string playerName, weekday;
		fin >> inputData[i].playerName >> inputData[i].weekday;
	}
}

int main() {
	readAttendanceData();
	calculateTotalPoints();
	assignGrades();
	printResults();
	return 0;
}
