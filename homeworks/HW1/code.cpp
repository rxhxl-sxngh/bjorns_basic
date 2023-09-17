// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double examScoreTotal;
    double finalExamScore;
    double hwTotal;
    double hwCount;
    double lwTotal;
    double lwCount;
    double readingTotal;
    double readingCount;
    double engagementTotal;
    double engagementCount;
    double compileCheckCount;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            // TODO(student): process exam score
            double currentExam;
            currentExam = score;
            examScoreTotal += currentExam;
        } else if (category == "final-exam") {
            // TODO(student): process final score
            finalExamScore = score;
        } else if (category == "hw") {
            // TODO(student): process hw score
            double currentHW;
            currentHW = score;
            hwTotal += currentHW;
            hwCount += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            bool currentLW;
            currentLW = score;
            if (currentLW) {
                lwTotal += 1;
            }
            lwCount += 1;
        } else if (category == "reading") {
            // TODO(student): process reading score
            double currentReading;
            currentReading = score;
            readingTotal += currentReading;
            readingCount += 1;
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            double currentEngagement;
            currentEngagement = score;
            engagementTotal += currentEngagement;
            engagementCount += 1;
        }else if  (category == "compile-check") {
            // TODO(student): process compile-check score
            bool currentCompileCheck;
            currentCompileCheck = score;
            if (currentCompileCheck) {
                compileCheckCount += 1;
            }
        }else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = 0;
    exam_average = (examScoreTotal + finalExamScore) / 3.0;
    if (finalExamScore > exam_average) {
        exam_average = finalExamScore;
    }

    double hw_average = 0;
    if (hwCount == 0) {
        hw_average = 0;
    } else {
        hw_average = hwTotal/hwCount;
    }
    

    double lw_average = 0;
    if (lwCount == 0) {
        lw_average = 0;
    } else {
        lw_average = (lwTotal/lwCount) * 100;
    }
    

    double reading = 0;
    if (readingCount == 0) {
        reading = 15.0;
    } else {
        reading = (readingTotal/readingCount) + 15.0;
    }
    if (reading > 100.0) {
        reading = 100.0;
    }

    double engagement = 0;
    engagement = (engagementTotal/engagementCount) + 15.0;
    if (engagementCount == 0) {
        engagement = 15.0;
    }
    if (engagement > 100.0) {
        engagement = 100.0;
    }

    double compileCheck_average = 0;
    compileCheck_average = compileCheckCount;
    if (compileCheck_average == 1) {
        lw_average *= 0.5;
    } else if (compileCheck_average == 0) {
        lw_average = 0.0;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = 0;
    weighted_total = (exam_average * 0.4) + (hw_average * 0.4) + (lw_average * 0.1) + (reading * 0.05) + (engagement * 0.05);

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total >= 89.5) {
        final_letter_grade = 'A';
    } else if (weighted_total < 89.5 && weighted_total >= 79.5) {
        final_letter_grade = 'B';
    } else if (weighted_total < 79.5 && weighted_total >= 69.5) {
        final_letter_grade = 'C';
    } else if (weighted_total < 69.5 && weighted_total >= 59.5) {
        final_letter_grade = 'D';
    } else {
        final_letter_grade = 'F';
    }

    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement | compile-check" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
