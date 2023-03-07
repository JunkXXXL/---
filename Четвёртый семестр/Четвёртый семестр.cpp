#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

bool createFileWithNumbers(const std::string& fileName, const int numbersCount, const int maxNumberValue)
{
    std::ofstream fFile;
    fFile.open(fileName);

    if (!fFile.is_open())
    {
        return false;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0., maxNumberValue);
    for (int i = 0; i < numbersCount; i++)
    {
        fFile << dist(mt) << " ";
    }

    fFile.close();
    return true;
}

void sortFile(const std::string& fileName)
{

}

bool isFileContainsSortedArray(const std::string& fileName)
{
    std::ifstream fFile;
    fFile.open(fileName);

    if (!fFile.is_open() && !fFile)
    {
        return false;
    }

    double lastNumber, currentNumber;
    fFile >> lastNumber;

    while (fFile)
    {
        fFile >> currentNumber;
        if (currentNumber < lastNumber)
        {
            return false;
        }
        lastNumber = currentNumber;
    }
    return true;
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

    for (int i = 0; i < 1; i++) {
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
}