#include "grade_manager.h"

string NormalGrade::getName() const {
    return "NORMAL";
}

bool NormalGrade::qualifies(int points) const {
    return true;
}

string SilverGrade::getName() const {
    return "SILVER";
}

bool SilverGrade::qualifies(int points) const {
    return points >= SILVER_THRESHOLD;
}

string GoldGrade::getName() const {
    return "GOLD";
}

bool GoldGrade::qualifies(int points) const {
    return points >= GOLD_THRESHOLD;
}

unique_ptr<Grade> GradeFactory::createGrade(const string& gradeName) {
    if (gradeName == "GOLD") return make_unique<GoldGrade>();
    if (gradeName == "SILVER") return make_unique<SilverGrade>();
    return make_unique<NormalGrade>();
}

GradeManager::GradeManager() {
    grades.push_back(GradeFactory::createGrade("GOLD"));
    grades.push_back(GradeFactory::createGrade("SILVER"));
    grades.push_back(GradeFactory::createGrade("NORMAL"));
}

const Grade* GradeManager::determineGrade(int points) const {
    for (const auto& grade : grades) {
        if (grade->qualifies(points)) {
            return grade.get();
        }
    }
    return nullptr;
}