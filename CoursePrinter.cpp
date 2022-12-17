//============================================================================
// Name        : Project 2
// Author      : Rebekah Collett
// Version     : 1.0
// Description : Course and Prerequisite Schedule
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <vector>
#include "csvparser.hpp"


using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 200;

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string courseTitle;
    vector <string> coursePreReq;

};


//============================================================================
// Static methods used for testing
//============================================================================


/**
 * Load a CSV file containing courses into a vector.
 *
 * @param csvPath the file path to the CSV file
 * @return a vector holding all the courses that were read
 */
vector<Course> loadCourses(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of courses.
    vector<Course> courses;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {
            csv::Row row = file[i];

            // Create a data structure and add to the collection of courses
            Course course = {
                row[0],
                row[1],
            };

            for (int i = 2; i < row.size(); i++){
                course.coursePreReq.push_back(row[i]); 
            }

            courses.push_back(course);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}
//print out all courses
void printAll(vector<Course> courses){
    for (int i = 0; i < courses.size(); i++){
        cout << courses[i].courseTitle << endl;
    }    
}

//print out specific course and course info
void printCourseInfo(string courseId, vector<Course> courses){
     
    string preReqs;
    for (int i = 0; i < courses.size(); i++){
        if (courses[i].courseId == courseId){
            cout << courses[i].courseId << ", " << courses[i].courseTitle << endl;
            for (int j = 0; j < courses[i].coursePreReq.size(); j++){
                preReqs += courses[i].coursePreReq[j] + ", ";
            }
            cout << "Prerequisites: " << preReqs << endl;
        }
    }

}

int main() {

    int userInput;
    string userCourse;
    string csvPath;
    vector<Course> courses;

    while (userInput != 9) {
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do" << endl;
        cin >> userInput;
        switch (userInput) {
            case 1:
                cout << "Please input the path to a CSV file containing courses." << endl;
                cin >> csvPath;
                courses = loadCourses(csvPath);
                break;
            case 2:
                printAll(courses);
                break;

            case 3:
                cout << "What course do you want to know about?" << endl;
                cin >> userCourse;
                printCourseInfo(userCourse, courses);
                break;

            case 9:
                cout << "Thank you for using the course planner!";
                break;
        }
    }
}

