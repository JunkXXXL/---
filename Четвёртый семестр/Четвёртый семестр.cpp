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

    std::srand(std::time(nullptr));
    for (int i = 0; i < numbersCount; i++)
    {
        fFile << rand() % maxNumberValue << " ";
    }

    fFile.close();
    return true;
}

void Merge(const std::string& fileName, int p)
{
    std::ofstream Ffile;
    Ffile.open(fileName);
    std::ifstream* fls = new std::ifstream[2];
    fls[0].open("Afile.txt");
    fls[1].open("Bfile.txt");

    if (!fls[0].is_open() || !fls[1].is_open() || !Ffile.is_open() || !fls[0] || !fls[1])
    {
        return;
    }

    short pointer = 0;
    double Anumber, Bnumber;
    fls[0] >> Anumber; fls[1] >> Bnumber;
    while (fls[0] && fls[1])
    {
        if (Anumber < Bnumber)
        {
            Ffile << Anumber;
            fls[0] >> Anumber;
        }
        else
        {
            Ffile << Bnumber;
            fls[1] >> Bnumber;
        }
    }

    while (fls[0])
    {
        fls[0] >> Anumber;
        Ffile << Anumber;
    }

    while (fls[1])
    {
        fls[1] >> Bnumber;
        Ffile << Bnumber;
    }

    fls[0].close(); fls[1].close(); Ffile.close();
    delete[] fls;
}

bool Separate(const std::string& fileName, int p)
{
    std::ifstream Ffile;
    Ffile.open(fileName);
    std::ofstream* fls = new std::ofstream[2];
    fls[0].open("Afile.txt");
    fls[1].open("Bfile.txt");

    if (!fls[0].is_open() || !fls[1].is_open() || !Ffile.is_open())
    {
        return false;
    }

    int pointer = 0;
    double number;
    while (Ffile)
    {
        for (int i = 0; i < p; i++)
        {
            Ffile >> number;  fls[pointer % 2] << number;
        }
        pointer++;
    }

    if (!fls[0] || !fls[1])
    {
        fls[0].close(); fls[1].close(); Ffile.close();
        delete[] fls;
        Merge(fileName, p);
        return true;
    }
    else {
        fls[0].close(); fls[1].close(); Ffile.close();
        delete[] fls;
        return false;
    }
}

void sortFile(const std::string& fileName)
{
    int p = 1;
    while (!Separate(fileName, p))
    {
        Merge(fileName, p);
        p = p * 2;
        std::cout << p << " ";
    }
    
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
    fFile.close();
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
    const int numbersCount = 100;
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