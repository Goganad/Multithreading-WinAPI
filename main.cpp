#include <vector>
#include <string>
#include <fstream>
#include "FileSorter.h"

using namespace std;

void writeToFile(const vector<string> &lines, const string &path) {
    ofstream out(path);
    for (const string &line : lines) {
        out << line;
    }
    out.close();
}

vector<string> readFromFile(const string &path) {
    ifstream in(path);
    vector<string> lines;

    string str;
    while (getline(in, str)) {
        lines.push_back(str);
    }
    in.close();

    return lines;
}

int main() {
    vector<string> strings = readFromFile("strings.txt");
    FileSorter sorter = FileSorter(strings, 5);
    writeToFile(sorter.sorted, "sorted_strings.txt");
    return 0;
}
