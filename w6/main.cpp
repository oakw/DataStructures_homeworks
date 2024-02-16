// Martins_Prokuratovs_221RDB473
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int COLUMN_COUNT = 3;
typedef int (*recs)[COLUMN_COUNT];

int get_file_line_count(ifstream&);
void to_array_from_file(int (*arr)[COLUMN_COUNT], ifstream&, int);
int min(recs, int, int);
double avg(recs, int, int);
double std_dev(recs, int, int);


int main() {
    ifstream valuesFile ("2d.csv");

    // Understand how many records are in the file
    int recordsCount = get_file_line_count(valuesFile) - 1;
    auto records = new int[recordsCount][COLUMN_COUNT];

    if (recordsCount > 0) {
        to_array_from_file(records, valuesFile, recordsCount);
        printf("Minimum value in first col   : %d\n", min(records, 0, recordsCount));
        printf("Arithmetic mean in second col: %f\n", avg(records, 1, recordsCount));
        printf("Arithmetic mean in third col : %f\n", std_dev(records, 2, recordsCount));

    } else {
        printf("No values to process");
    }

    delete records;

    return 0;
}


/*
 * Custom round to get number with specified decimal places
 */
double round_pl(double num, int decimalPlaces) {
    return round(num * pow(10, decimalPlaces)) / pow(10, decimalPlaces);
}


/*
 * Get the standard deviation of all values in the column
 */
double std_dev(int (*records)[COLUMN_COUNT], int colNum, int recordsCount) {
    double mean = avg(records, colNum, recordsCount);
    double stdDevSum = 0;

    // Sum (x_1 - mean)
    for (int i = 0; i < recordsCount; i++)
        stdDevSum += pow(records[i][colNum] - mean, 2);

    // Sqrt(Sum / count)
    return round_pl(sqrt(stdDevSum / recordsCount), 2);
}


/*
 * Get an average of all values in the column
 * Sum and then divide by the records count
 */
double avg(recs records, int colNum, int recordsCount) {
    double sum = 0.0;
    
    for (int i = 0; i < recordsCount; i++)
        sum += records[i][colNum];

    return round_pl(sum / recordsCount, 2);
}


/*
 * Gets the minimal value in the column
 */
int min(recs records, int colNum, int recordsCount) {
    int min = records[0][colNum];

    for (int i = 0; i < recordsCount; i++)
        if (records[i][colNum] < min)
            min = records[i][colNum];

    return min;
}


/*
 * Populate records with the lines from the file
 */
void to_array_from_file(recs records, ifstream &stream, int recordsCount) {
    string line;

    if (stream.is_open()) {
        getline(stream, line); // Skip the header

        for (int i = 0; i < recordsCount; i++) {
            // Take the line
            if (getline(stream, line)) {
                int col = 0;
                
                while (! line.empty()) {
                    // Take the part before the comma
                    string part = line.substr(0, line.find(","));

                    // Remove that part and the next comma to process the line with only the numbers left
                    line = line.substr(part.length() + (line.find(',') == -1 ? 0 : 1));

                    records[i][col] = stoi(part);
                    col++;
                }
            }
        }
    }
}


/*
 * Count the number of lines in the file
 */
int get_file_line_count(ifstream &stream) {
    int count = 0;
    string line;

    if (stream.is_open()) {
        // https://cplusplus.com/reference/istream/istream/tellg/
        int old_pos = stream.tellg();
        stream.seekg(0);

        while (getline(stream, line))
            count++;

        // https://stackoverflow.com/a/16364456
        stream.clear();
        stream.seekg(0);
    }


    return count;
}
