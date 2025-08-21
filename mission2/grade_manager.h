#pragma once
#include <iostream>
#include <vector>

using std::string;
using std::unique_ptr;
using std::vector;
using std::make_unique;

class Grade {
public:
	virtual string getName() const = 0;
	virtual bool qualifies(int points) const = 0;
};

class NormalGrade : public Grade {
public:
	string getName() const override;
	bool qualifies(int points) const override;
};

class SilverGrade : public Grade {
public:
	string getName() const override;
	bool qualifies(int points) const override;

private:
	const int SILVER_THRESHOLD = 30;
};

class GoldGrade : public Grade {
public:
	string getName() const override;
	bool qualifies(int points) const override;
private:
	const int GOLD_THRESHOLD = 50;
};

class GradeFactory {
public:
	static unique_ptr<Grade> createGrade(const string& gradeName);
};

class GradeManager {
private:
	vector<unique_ptr<Grade>> grades;

public:
	GradeManager();
	const Grade* determineGrade(int points) const;
};