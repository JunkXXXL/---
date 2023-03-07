#include <iostream>
#include <fstream>

bool createFileWithNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{

    return false;
}

void sortFile(const std::string& fileName)
{

}

bool isFileContainsSortedArray(const std::string& fileName)
{

    return false;
}

int createAndSortFile(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    sortFile(fileName); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

int main()
{
    std::string fileName = "file.txt";
    const int numbersCount = 1000000;
    const int maxNumberValue = 100000;

    for (int i = 0; i < 10; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }

        return 0;
    }