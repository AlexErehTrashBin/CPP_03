#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <fstream>

using namespace std;

auto parseArrayFromFile(const string&filename) -> optional<vector<int>>;

auto getAllElementsInFile(ifstream&iss) -> int;

auto writeArrayToFile(const vector<int>&vec, const string&filename) -> void;

/// Дан текстовый файл f1, содержащий последовательность целых чисел.
/// Отсортировать числа по возрастанию и записать их в файл f2.

auto printArray(const vector<int>&vector) -> void;

auto bubbleSort(vector<int>&vec) -> void {
    const auto n = vec.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main() {
    string inFile, outFile;
    optional<vector<int>> arr;

    while (arr == nullopt) {
        cout << "Введите название файла с массивом: ";
        cin >> inFile;
        arr = parseArrayFromFile(inFile);
    }

    auto arrValue = arr.value();

    cout << "Введите название файла с отсортированным массивом: ";
    cin >> outFile;

    printArray(arrValue);
    bubbleSort(arrValue);
    printArray(arrValue);
    writeArrayToFile(arrValue, outFile);
    system("pause");
}

auto printArray(const vector<int>&vector) -> void {
    // C++ 11 - range based for loop
    for (const auto &item: vector) {
        cout << item << ' ';
    }
    cout << endl;
}

auto getAllElementsInFile(ifstream&iss) -> int {
    const auto prevPos = iss.tellg();
    int result = 0;
    int tempForReadAllElements;
    while (!iss.eof()) {
        iss >> tempForReadAllElements;
        result++;
    }

    iss.seekg(prevPos, ios::beg);
    iss.clear();
    return result;
}

auto writeArrayToFile(const vector<int>&vec, const string&filename) -> void {
    ofstream ofs(filename);

    if (!ofs.is_open()) {
        cerr << "Ошибка при записи в файл " << filename << "." << endl;
        return;
    }

    // C++ 11 - Range based for loop
    for (const auto &number: vec) {
        ofs << number << " ";
    }
}

auto parseArrayFromFile(const string&filename) -> optional<vector<int>> {
    vector<int> arr;

    ifstream inputFileStream(filename);

    if (!inputFileStream) {
        cerr << "Ошибка при открытии файла " << filename << "." << endl;
        return nullopt;
    }

    const int allElementsInFile = getAllElementsInFile(inputFileStream);
    arr.resize(allElementsInFile);

    for (int i = 0; i < allElementsInFile; ++i) {
        inputFileStream >> arr[i];
    }

    inputFileStream.close();
    return arr;
}
