#include "gmock/gmock.h"
#include <fstream>
#include <sstream>
#include "attendance.h"

using namespace testing;
using std::string;
using std::ofstream;
using std::ostringstream;

class AttendanceManagerTestFixture : public Test {
protected:
    AttendanceManager attendanceManager;
    string testFilePath = "test_attendance.txt";

    void SetUp() override {
        inputCount = 0;
        ofstream testFile(testFilePath);

        // user1: Normal grade
        testFile << "user1 monday\n";
        testFile << "user1 wednesday\n";
        testFile << "user1 friday\n";
        testFile << "user1 saturday\n";
        testFile << "user1 sunday\n";

        // user2: Gold grade
        for (int i = 0; i < 10; i++) {
            testFile << "user2 wednesday\n";
        }
        for (int i = 0; i < 5; i++) {
            testFile << "user2 saturday\n";
        }
        for (int i = 0; i < 2; i++) {
            testFile << "user2 sunday\n";
        }

        // user3: Silver grade
        for (int i = 0; i < 30; i++) {
            testFile << "user3 monday\n";
        }

        // user4: Normal grade and removed player
        for (int i = 0; i < 5; i++) {
            testFile << "user4 monday\n";
        }

        // user 5: Weekend bonus player
        for (int i = 0; i < 5; i++) {
            testFile << "user5 saturday\n";
            testFile << "user5 sunday\n";
        }

        // user6: Invalid weekday
        testFile << "user6 invalid_day\n";

        testFile.close();
    }

    void TearDown() override {
        std::remove(testFilePath.c_str());
    }

    // Helper to capture stdout
    string captureOutput(std::function<void()> func) {
        testing::internal::CaptureStdout();
        func();
        return testing::internal::GetCapturedStdout();
    }
};

TEST_F(AttendanceManagerTestFixture, TestManageAttendanceUser1Case) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("NAME : user1, POINT : 9, GRADE : NORMAL"));
}

TEST_F(AttendanceManagerTestFixture, TestManageAttendanceUser2Case) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("NAME : user2, POINT : 54, GRADE : GOLD"));
}

TEST_F(AttendanceManagerTestFixture, TestManageAttendanceUser3Case) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("NAME : user3, POINT : 30, GRADE : SILVER"));
}

TEST_F(AttendanceManagerTestFixture, TestManageAttendanceUser4Case) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("NAME : user4, POINT : 5, GRADE : NORMAL"));
}

TEST_F(AttendanceManagerTestFixture, TestManageAttendanceUser5Case) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("NAME : user5, POINT : 30, GRADE : SILVER"));
}

TEST_F(AttendanceManagerTestFixture, TestRemovedPlayer) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("Removed player"));
    EXPECT_THAT(output, HasSubstr("user4"));
}

TEST_F(AttendanceManagerTestFixture, TestInvalidWeekday) {
    string output = captureOutput([this]() {
        attendanceManager.manageAttendance(testFilePath);
        });

    EXPECT_THAT(output, HasSubstr("Invalid weekday: invalid_day"));
}

int main() {
#ifdef _DEBUG
    InitGoogleMock();
    return RUN_ALL_TESTS();
#else
    AttendanceManager attendanceManager;
    attendanceManager.manageAttendance("attendance_weekday_500.txt");
    return 0;
#endif
}