#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

bool isAlpha(char c) {
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool isNumeric(char c) {
    return c >= '0' && c <= '9';
}

bool isAlphaNumeric(string s) {
    for (const char &c: s) {
        if (!isAlpha(c) && !isNumeric(c)) {
            return false;
        }
    }
    return true;
}

// generate random strings (a lot of them) into a file
static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

const char charset[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

string generateRandomString(int length) {
    string tmp = "";
    if (rand() % 2 == 0) {
        for (int i = 0; i < length; i++) {
            tmp += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
    } else {
        for (int i = 0; i < length; i++) {
            tmp += charset[rand() % (sizeof(charset) - 1)];
        }
    }
    return tmp;
}

void writeRandomStrings(int n) {
    // open file
    fstream f;
    f.open("example.txt", ios::out | ios::app);

    //write strings
    for (int i = 0; i < n; i++) {
        f << generateRandomString(20) << endl;
    }

    // close file
    f.close();
}

// correctness test (todo: should write results to file)
bool alphanumericTest_isCorrect() {
    fstream f;
    f.open("example.txt", ios::in);
    fstream f2;
    f2.open("cpp.txt", ios::in);

    string tmp;

    //auto start_time = chrono::high_resolution_clock::now();
    while (!f.eof()) {
        f >> tmp;
        bool alnum = true;
        for (int i = 0; i < tmp.length(); i++) {
            if (!isalnum(tmp[i])) {
                alnum = false;
            }
        }
        if (alnum != isAlphaNumeric(tmp)) {
            f.close();
            return false;
        }
    }

    //auto end_time = std::chrono::high_resolution_clock::now();
    //auto time = end_time - start_time;
    f.close();
    f2.close();
    return true;
}

// performance test
long alphanumericTest_performance() {
    fstream f;
    f.open("example.txt", ios::in);

    string tmp;

    auto start_time = chrono::high_resolution_clock::now();
    while (!f.eof()) {
        f >> tmp;
        isAlphaNumeric(tmp);
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto time = end_time - start_time;

    auto start_time_loop = chrono::high_resolution_clock::now();
    while (!f.eof()) {
        f >> tmp;
        isAlphaNumeric(tmp);
    }

    auto end_time_loop = chrono::high_resolution_clock::now();
    auto time_loop = end_time_loop - start_time_loop;

    f.close();
    return (time - time_loop) / chrono::milliseconds(1);
}

int main() {
    srand(time(NULL));
    //writeRandomStrings(10000000);

    bool correctnessTest = alphanumericTest_isCorrect();
    cout << (correctnessTest ? "Correctness test passed!" : "Correctness test failed!") << endl;
    long performanceTest = alphanumericTest_performance();
    cout << "Performance test took " << performanceTest << " milliseconds." << endl;

    return 0;
}
