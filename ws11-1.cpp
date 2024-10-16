#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// vector of int.
// used to store the records
typedef vector<int> Records;

class RecordsManager {
private:
    fstream _file;
    string _filename;

public:
    RecordsManager(string filename) : _filename(filename) {}

    void read(Records &records) {
        _file.open(_filename, ios::in);
        if (_file.is_open()) {
            string line;
            try {
                while (getline(_file, line)) {
                    try {
                        records.push_back(stoi(line));
                    } catch (const invalid_argument &e) {
                        cerr << "Error: Invalid argument when reading the file '" << _filename << "' on line: " << line << endl;
                        throw; // propagate the exception to main
                    } catch (const out_of_range &e) {
                        cerr << "Error: Out of range value in file '" << _filename << "' on line: " << line << endl;
                        throw; // propagate the exception to main
                    }
                }
            } catch (...) {
                _file.close(); // Ensure the file is closed before rethrowing the exception
                throw; // propagate any exception
            }
            _file.close();
        } else {
            cerr << "Error: Unable to open the file '" << _filename << "'" << endl;
            throw runtime_error("File opening failed");
        }
    }
};

int main() {
    try {
        RecordsManager recordM("test_clean.txt");

        Records myRecords;

        // reads records
        recordM.read(myRecords);

        // calculate and print out the sum
        int sum = 0;
        for (int i = 0; i < myRecords.size(); i++) {
            sum += myRecords[i];
        }
        cout << "Sum of records: " << sum << endl;

    } catch (const invalid_argument &e) {
        cerr << "Exception: Invalid data encountered during file processing." << endl;
    } catch (const out_of_range &e) {
        cerr << "Exception: Number out of range encountered during file processing." << endl;
    } catch (const exception &e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}