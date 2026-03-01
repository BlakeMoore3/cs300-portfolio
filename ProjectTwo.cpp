// Blake Moore

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
	string courseNumber;
	string name;
	vector<string> prerequisiteList;
};

// Vector Storage
vector<Course> courses;

bool LoadCoursesVector(const string& filename);
void PrintCourseListVector();
void PrintCourseVector(const string& courseNumber);

int main() {
	int choice = 0;
	bool dataLoaded = false;

	// File to pull from
	// change as needed

	string loadFile = "CS 300 ABCU_Advising_Program_Input.csv";

	while (choice != 9) {

		// Display menu
		cout << "\n1. Load Data\n";
		cout << "2. Print Course List\n";
		cout << "3. Print Course\n";
		cout << "9. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 1) {
			dataLoaded = LoadCoursesVector(loadFile);

			if (dataLoaded) {
				cout << "Data loaded successfully.\n";
			}

			else {
				cout << "Failed to load file.\n";
			}
		}

		else if (choice == 2) {
			if (!dataLoaded) {
				cout << "Please load data first.\n";
			}
			else {
				PrintCourseListVector();
			}
		}
		
		else if (choice == 3) {
			if (!dataLoaded) {
				cout << "Please load data first.\n";
			}
			else {
				string courseNumber;
				cout << "Enter course number: ";
				cin >> courseNumber;
				PrintCourseVector(courseNumber);
			}
		}

		else if (choice == 9) {
			cout << "Closing Program.\n";
		}
		
		else {
			cout << "Invalid option. \n";
		}
	}

	return 0;
}

bool LoadCoursesVector(const string& filename) {

	// clear old data if reloading
	courses.clear();
	unordered_set<string> courseNumbers;

	ifstream file(filename);

	if (!file.is_open()) {
		cout << "Error opening file.\n";
		return false;
	}

	string line;

	// read each line of the file
	while (getline(file, line)) {

		if (line.empty()) {
			continue;
		}

		vector<string> tokens;
		string token;
		stringstream ss(line);

		// Split by comma
		while (getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		if (tokens.size() < 2) {
			cout << "Invalid line format.\n";
			continue;
		}

		Course c;
		c.courseNumber = tokens[0];
		c.name = tokens[1];

		// Add prerequisites
		for (size_t i = 2; i < tokens.size(); i++) {
			if (!tokens[i].empty()) {
				c.prerequisiteList.push_back(tokens[i]);
			}
		}

		courseNumbers.insert(c.courseNumber);
		courses.push_back(c);
	}

	file.close();

	// Validate prerequisites exis
	for (size_t i = 0; i < courses.size(); i++) {
		for (size_t j = 0; j < courses[i].prerequisiteList.size(); j++) {

			string prereq = courses[i].prerequisiteList[j];

			if (courseNumbers.find(prereq) == courseNumbers.end()) {
				cout << "Invalid prerequisite: " << prereq << endl;
			}
		}
	}

	return true;
}

void PrintCourseListVector() {
	
	// Sort by course number
	sort(courses.begin(), courses.end(), [](Course a, Course b) {
		return a.courseNumber < b.courseNumber;
		});

	// Print sorted list
	for (size_t i = 0; i < courses.size(); i++) {
		cout << courses[i].courseNumber << ", " << courses[i].name << endl;
	}
}

void PrintCourseVector(const string& courseNumber) {

	bool found = false;

	for (size_t i = 0; i < courses.size(); i++) {

		if (courses[i].courseNumber == courseNumber) {

			found = true;

			cout << courses[i].courseNumber << ", " << courses[i].name << endl;

			if (courses[i].prerequisiteList.empty()) {
				cout << "Prerequisites: None\n";
			}

			else {
				cout << "Prerequisites: ";
				for (size_t j = 0; j < courses[i].prerequisiteList.size(); j++) {
					cout << courses[i].prerequisiteList[j];

					if (j < courses[i].prerequisiteList.size() - 1) {
						cout << ", ";
					}
				}
				cout << endl;
			}
		}
	}

	if (!found) {
		cout << "Course not found.\n";
	}
}

