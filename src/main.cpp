#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "../header/main.h"

using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::ios;
using std::setiosflags;
using std::setw;

int main() {
    srand(time(NULL));
    int currentMethod = -1;
    int sets = 0;
    greetings();
    while (currentMethod != 0) {
        currentMethod = pickMethod();
        if (currentMethod != 0) {
            sets = getSets();
            cout << "Here are your stats:" << endl << "---" << endl;
            switch (currentMethod) {
                case 1:
                    classic3d6(sets);
                    break;
                case 2:
                    droplow4d6(sets);
                    break;
                case 3:
                    droplow5d6(sets);
                    break;
                case 4:
                    haydenalgo(sets);
                    break;
                default:
                    break;
            }
            cout << "---" << endl;
        }
    }
    cout << "Thanks for using this program! Have fun building your character!" << endl;
}

void greetings()
{
    cout << "Welcome to the dice roller!" << endl << endl;
}

int pickMethod()
{
    bool validData = false;
    int rollmethod;
    while (!validData) {
        try{
            cout << "Which method of rolling would you like to use? " << endl;
            cout << "(enter the number that corresponds with your choice)" << endl;
            cout << "0 - stop rolling and quit the program" << endl;
            cout << "1 - classic 3d6" << endl;
            cout << "2 - 4d6, drop the lowest roll" << endl;
            cout << "3 - 5d6, drop the lowest two rolls" << endl;
            cout << "4 - Hayden's mixed algorithm, with 2 stats made from each of the previous 3 methods" << endl;
            cin >> rollmethod;
            if (cin.fail()) {
                throw("that was not a valid number entry");
            }
            if (rollmethod < 0) {
                throw("that was a negative number");
            }
            if (rollmethod > NumMethods) {
                throw("that choice number doesn't exist");
            }
            validData = true;
        }
        catch(char const* errMessage) {
            cout << "Sorry, " << errMessage << ". Please try again." << endl;
        }
    }
    return rollmethod;
}

int getSets()
{
    {
        bool validData = false;
        int numsets;
        while (!validData) {
            try{
                cout << "How many sets of stats would you like rolled?" << endl;
                cin >> numsets;
                if (cin.fail()) {
                    throw("that was not a valid number entry");
                }
                if (numsets < 0) {
                    throw("that was a negative number");
                }
                if (numsets == 0) {
                    throw("you need to roll at least once");
                }
                if (numsets > ReasonableRolls) {
                    throw("I think you know that's an unreasonable number of rolls");
                }
                validData = true;
            }
            catch(char const* errMessage) {
                cout << "Sorry, " << errMessage << ". Please try again." << endl;
            }
        }
        return numsets;
    }
}

void classic3d6(int sets)
{
    for(int currSet = 1; currSet <= sets; currSet++) {
        for(int stat = 1; stat <= NumStats; stat++) {
            int r1, r2, r3, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            total = r1 + r2 + r3;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
        }
        cout << endl;
    }
}

void droplow4d6(int sets)
{
    for(int currSet = 1; currSet <= sets; currSet++) {
        for(int stat = 1; stat <= NumStats; stat++) {
            int r1, r2, r3, r4, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            r4 = (rand() % 6) + 1;
            int* lowest = &r1;
            if (r2 < *lowest) {
                lowest = &r2;
            }
            if (r3 < *lowest) {
                lowest = &r3;
            }
            if (r4 < *lowest) {
                lowest = &r4;
            }
            *lowest = 0;
            total = r1 + r2 + r3 + r4;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
        }
        cout << endl;
    }
}

void droplow5d6(int sets)
{
    for(int currSet = 1; currSet <= sets; currSet++) {
        for(int stat = 1; stat <= NumStats; stat++) {
            int r1, r2, r3, r4, r5, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            r4 = (rand() % 6) + 1;
            r5 = (rand() % 6) + 1;
            //time to negate the lowest number rolled
            int* lowest = &r1;
            if (r2 < *lowest) {
                lowest = &r2;
            }
            if (r3 < *lowest) {
                lowest = &r3;
            }
            if (r4 < *lowest) {
                lowest = &r4;
            }
            if (r5 < *lowest) {
                lowest = &r5;
            }
            *lowest = 0;
            //now we negate the second lowest
            if (r1 != 0) {
                lowest = &r1;
            } else {
                lowest = &r2;
            }
            if ((r2 < *lowest)&&(r2 !=0)) {
                lowest = &r2;
            }
            if ((r3 < *lowest)&&(r3 !=0)) {
                lowest = &r3;
            }
            if ((r4 < *lowest)&&(r4 !=0)) {
                lowest = &r4;
            }
            if ((r5 < *lowest)&&(r5 !=0)) {
                lowest = &r5;
            }
            *lowest = 0;
            total = r1 + r2 + r3 + r4 + r5;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
        }
        cout << endl;
    }
}

void haydenalgo(int sets)
{
    for(int currSet = 1; currSet <= sets; currSet++) {
        int stat = 1;
        while (stat < 3) {
            int r1, r2, r3, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            total = r1 + r2 + r3;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
            stat ++;
        }
        while (stat < 5) {
            int r1, r2, r3, r4, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            r4 = (rand() % 6) + 1;
            int* lowest = &r1;
            if (r2 < *lowest) {
                lowest = &r2;
            }
            if (r3 < *lowest) {
                lowest = &r3;
            }
            if (r4 < *lowest) {
                lowest = &r4;
            }
            *lowest = 0;
            total = r1 + r2 + r3 + r4;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
            stat ++;
        }
        while (stat <= NumStats ) {
            int r1, r2, r3, r4, r5, total;
            r1 = (rand() % 6) + 1;
            r2 = (rand() % 6) + 1;
            r3 = (rand() % 6) + 1;
            r4 = (rand() % 6) + 1;
            r5 = (rand() % 6) + 1;
            //time to negate the lowest number rolled
            int* lowest = &r1;
            if (r2 < *lowest) {
                lowest = &r2;
            }
            if (r3 < *lowest) {
                lowest = &r3;
            }
            if (r4 < *lowest) {
                lowest = &r4;
            }
            if (r5 < *lowest) {
                lowest = &r5;
            }
            *lowest = 0;
            //now we negate the second lowest
            if (r1 != 0) {
                lowest = &r1;
            } else {
                lowest = &r2;
            }
            if ((r2 < *lowest)&&(r2 !=0)) {
                lowest = &r2;
            }
            if ((r3 < *lowest)&&(r3 !=0)) {
                lowest = &r3;
            }
            if ((r4 < *lowest)&&(r4 !=0)) {
                lowest = &r4;
            }
            if ((r5 < *lowest)&&(r5 !=0)) {
                lowest = &r5;
            }
            *lowest = 0;
            total = r1 + r2 + r3 + r4 + r5;
            cout << setiosflags(ios::fixed);
            cout << setw(2) << total << " ";
            stat ++;
        }
        cout << endl;
    }
}