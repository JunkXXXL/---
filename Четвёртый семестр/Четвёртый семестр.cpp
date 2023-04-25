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

bool newCreateFileWithNumbers(const std::string& fileName, const int numbersCount, const unsigned long long maxNumberValue)
{
    std::ofstream fFile;
    fFile.open(fileName);

    if (!fFile.is_open())
    {
        return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, maxNumberValue);
    for (int i = 0; i < numbersCount; i++)
    {
        fFile << gen() % maxNumberValue << " ";
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

    int i, j;

    unsigned long long Anumber, Bnumber;
    fls[0] >> Anumber; fls[1] >> Bnumber;
    
    while (fls[0] && fls[1])
    {
        i = j = 0;

        while (fls[0] && fls[1] && i < p && j < p)
        {
            if (Anumber < Bnumber)
            {
                Ffile << Anumber << " ";
                fls[0] >> Anumber;
                i += 1;
            }
            else
            {
                Ffile << Bnumber << " ";
                fls[1] >> Bnumber;
                j += 1;
            }
        }

        while (fls[0] && i < p)
        {
            Ffile << Anumber << " ";
            fls[0] >> Anumber;
            i += 1;
        }

        while (fls[1] && j < p)
        {
            Ffile << Bnumber << " ";
            fls[1] >> Bnumber;
            j += 1;
        }

    }

    while (fls[0])
    {
        Ffile << Anumber << " ";
        fls[0] >> Anumber;
    }

    while (fls[1])
    {
        Ffile << Bnumber << " ";
        fls[1] >> Bnumber;
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
    int number;
    while (Ffile >> number)
    {
        fls[pointer / p % 2] << number << " ";
        pointer++;
    }

    fls[0].close(); fls[1].close(); Ffile.close();
    delete[] fls;

    std::ifstream f2; 
    f2.open("Bfile.txt");
    if (f2 >> number)
    {
        f2.close();
        return false;
    }
    else {
        f2.close();
        Merge(fileName, p);
        return true;
    }
}

bool _checkSecondFile()
{
    std::ifstream secFl; secFl.open("Bfile.txt");
    int A;
    secFl >> A;
    if (secFl) 
    {
        secFl.close();
        return true;
    }
    else
    {
        secFl.close();
        return false;
    }
}

void sortFile(const std::string& fileName)
{
    int p = 1;

    Separate(fileName, p);

    while (_checkSecondFile())
    {
        Separate(fileName, p);
        Merge(fileName, p);
        p = p * 2;
        //std::cout << p << " ";
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

    unsigned long long lastNumber, currentNumber;
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
    if (!newCreateFileWithNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }

    sortFile(fileName); //Вызов вашей функции сортировки

    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }

    return 1;
}

int main1()
{
    std::string fileName = "file.txt";
    const int numbersCount = 100;
    const int maxNumberValue = 1000000000;

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
    }

    return 0;
}