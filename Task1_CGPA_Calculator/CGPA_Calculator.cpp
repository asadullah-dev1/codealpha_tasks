/*
    CodeAlpha Internship - Task 1: CGPA Calculator
    ------------------------------------------------
    What this program does:
    1. Asks how many courses you took this semester.
    2. For each course, asks for the LETTER GRADE and CREDIT HOURS.
    3. Converts each letter grade to grade points (using a 4.0 scale).
    4. Calculates this semester's GPA.
    5. Combines it with your PREVIOUS CGPA (if any) to get your overall CGPA.
    6. Displays a summary table + final CGPA.
*/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>   // for setprecision() -> controls decimal places when printing

using namespace std;

// A simple "struct" to group data about one course together.
// Think of it as a mini-table row: name, grade, credit hours, grade points.
struct Course {
    string name;
    string grade;
    double creditHours;
    double gradePoints; // grade converted to a number (e.g., A = 4.0)
};

// This function takes a letter grade (like "A" or "B+") and returns
// the matching grade point value. Returns -1 if the grade is invalid.
double gradeToPoints(string grade) {
    if (grade == "A")  return 4.0;
    if (grade == "A-") return 3.7;
    if (grade == "B+") return 3.3;
    if (grade == "B")  return 3.0;
    if (grade == "B-") return 2.7;
    if (grade == "C+") return 2.3;
    if (grade == "C")  return 2.0;
    if (grade == "C-") return 1.7;
    if (grade == "D")  return 1.0;
    if (grade == "F")  return 0.0;
    return -1; // signals "invalid grade" to the caller
}

int main() {
    int numCourses;

    cout << "===== CGPA Calculator =====\n";
    cout << "Enter number of courses this semester: ";
    cin >> numCourses;

    // vector<Course> = a list that can grow, holding Course structs
    vector<Course> courses;

    double totalCreditHours = 0.0;
    double totalGradePoints = 0.0; // sum of (grade points * credit hours)

    // Loop once per course to collect its details
    for (int i = 0; i < numCourses; i++) {
        Course c;
        cout << "\n--- Course " << (i + 1) << " ---\n";

        cout << "Course name: ";
        cin >> c.name;

        // Keep asking until a valid grade is entered
        do {
            cout << "Grade (A, A-, B+, B, B-, C+, C, C-, D, F): ";
            cin >> c.grade;
            c.gradePoints = gradeToPoints(c.grade);
            if (c.gradePoints == -1) {
                cout << "Invalid grade, please try again.\n";
            }
        } while (c.gradePoints == -1);

        cout << "Credit hours: ";
        cin >> c.creditHours;

        // Add this course's contribution to the running totals
        totalCreditHours += c.creditHours;
        totalGradePoints += c.gradePoints * c.creditHours;

        courses.push_back(c); // add this course to our list
    }

    // GPA = total grade points earned / total credit hours attempted
    double semesterGPA = totalGradePoints / totalCreditHours;

    // Ask for previous academic record so we can compute overall CGPA.
    // If this is their first semester, they can enter 0 for both.
    double prevCGPA, prevCreditHours;
    cout << "\nEnter your PREVIOUS CGPA (enter 0 if this is your first semester): ";
    cin >> prevCGPA;
    cout << "Enter your PREVIOUS total credit hours (enter 0 if first semester): ";
    cin >> prevCreditHours;

    // To combine CGPA correctly, we convert previous CGPA back into grade points,
    // add this semester's grade points, then divide by the new total credit hours.
    double prevGradePoints = prevCGPA * prevCreditHours;
    double overallCreditHours = prevCreditHours + totalCreditHours;
    double overallCGPA = (prevGradePoints + totalGradePoints) / overallCreditHours;

    // ---- Display results ----
    cout << fixed << setprecision(2); // show 2 decimal places for all numbers below

    cout << "\n===== Course Summary =====\n";
    for (int i = 0; i < (int)courses.size(); i++) {
        cout << courses[i].name << " | Grade: " << courses[i].grade
             << " | Credit Hours: " << courses[i].creditHours
             << " | Grade Points: " << courses[i].gradePoints << "\n";
    }

    cout << "\nSemester GPA: " << semesterGPA << "\n";
    cout << "Overall CGPA: " << overallCGPA << "\n";

    return 0;
}
