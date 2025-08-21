#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include "grade_manager.h"

using std::cout;
using std::ifstream;
using std::string;
using std::map;
using std::vector;
using std::unique_ptr;
using std::make_unique;

struct AttendanceRecord {
	string playerName;
	string weekday;
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

const int WEDNESDAY_POINTS = 3;
const int WEEKEND_POINTS = 2;
const int DEFAULT_POINTS = 1;

const int WEDNESDAY_BONUS_THRESHOLD = 10;
const int WEEKEND_BONUS_THRESHOLD = 10;
const int WEDNESDAY_BONUS_POINTS = 10;
const int WEEKEND_BONUS_POINTS = 10;

extern AttendanceRecord inputData[MAX_INPUT];
extern int inputCount;

class AttendanceManager {
public:
	void manageAttendance(string inputPath);

private:
	map<string, int> playerIdMap;
	int playerCount = 0;
	string playerNames[MAX_PLAYERS];
	int attendanceByDay[MAX_PLAYERS][TOTAL_WEEKDAYS];
	int playerPoints[MAX_PLAYERS];
	const Grade* playerGrades[MAX_PLAYERS];
	int wednesdayAttendanceCount[MAX_PLAYERS]; 
	int weekendAttendanceCount[MAX_PLAYERS];
	GradeManager gradeManager;

	void calculateBonusPoints();
	void calculateDefaultPoints();
	int getWeekdayIndex(const string& weekday);
	int getWeekdayPoints(const string& weekday);
	int getPlayerId(const string& playerName);
	void printRemovedPlayer();
	void printNameAndPoint();
	void printResults();
	void assignGrades();
	void calculateTotalPoints();
	void readAttendanceData(string inputPath);
};