#include <iostream>
#include <string>  
#include <random>
#include <fstream>
#include <vector>

class PrimeNumberContainer {
private:
    std::vector<long> container;

private:
    void readNumbersAndAssign() {
        std::fstream FILE;
        try {
            FILE.open("PrimeNumbers", std::ios::in);
            if (!FILE)
                throw "File can't be opened!";
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            system("pause");
        }
        while (FILE) {
            std::string newLine;
            getline(FILE, newLine);
            if (newLine == "") {
                break;
            }
            container.push_back(stoi(newLine));
        }
        FILE.close();
    }

public:
    PrimeNumberContainer() {
        readNumbersAndAssign();
    }
    std::pair<long, long> getPrimes(long key) {
        int first_choice = (key % 30) % (container.size() - 1);
        int second_choice = (key % 55) % (container.size() - 1);
        return std::make_pair(container[first_choice], container[second_choice]);
    }

};