#include <iostream>
#include <string>
#include <climits>

#include "simplexTable.h"

using namespace std;

Fraction getFraction()
{
    bool retry = false;
    string fractionString;
    Fraction fraction;

    do {
        try {
            getline(cin, fractionString);
            fraction = Fraction::parseString(fractionString);
            retry = false;
        } catch (exception& e) {
            cout << "Please enter a valid number." << endl;
            retry = true;
        }
    } while (retry);

    return fraction;
}

unsigned int getUInt(unsigned int lowerBound = 0, unsigned int upperBound = UINT_MAX)
{
    bool retry = false;
    string intString;
    unsigned int retVal;

    do {
        try {
            getline(cin, intString);
            retVal = stoi(intString);
            if (retVal < lowerBound || upperBound < retVal) throw out_of_range("Unsigned int out of range.");
            retry = false;
        } catch (exception& e) {
            cout << "Please enter a valid number." << endl;
            retry = true;
        }
    } while (retry);
    
    return retVal;
}

SimplexTable* inputTable()
{
    cout << "Please enter the amount of columns (> 1): ";
    unsigned int columns = getUInt(2);

    cout << "Please enter the amount of rows (> 1): ";
    unsigned int rows = getUInt(2);

    cout << endl;
    SimplexTable* table = new SimplexTable(columns, rows);

    for (unsigned int row = 0; row < rows; row++)
        for (unsigned int column = 0; column < columns; column++) {
            cout << "Please enter value for position (" << column + 1 << ',' << row + 1 << "): ";
            Fraction fraction = getFraction();
            table->setCell(column, row, fraction);
        }

    return table;
}

void printHelp()
{
    cout << "| p: pivot | n: new table | s: substitute cell | l: print in LaTeX | r: reduce all fractions | q: quit |" << endl;
}


void loop(SimplexTable* table)
{
    while (true) {
        string command;
        printHelp();
        cout << "Next command: ";
        getline(cin, command);
        if (command.size() == 0) continue;

        switch(tolower(command[0])) {
            case 'p':
                {
                    cout << "Please enter the pivot column: ";
                    unsigned int column = getUInt(1, table->getColumnAmount());
                    cout << "Please enter the pivot row: ";
                    unsigned int row = getUInt(1, table->getRowAmount());
                    table->pivot(column - 1, row - 1);
                    table->print();
                    break;
                }
            case 's':
                {
                    cout << "Please enter the substitution column: ";
                    unsigned int column = getUInt(1, table->getColumnAmount());
                    cout << "Please enter the substitution row: ";
                    unsigned int row = getUInt(1, table->getRowAmount());
                    cout << "Please enter the value to be substituted with: ";
                    Fraction fraction = getFraction();
                    table->setCell(column - 1, row - 1, fraction);
                    table->print();
                    break;
                }
            case 'n':
                delete table;
                table = inputTable();
                table->print();
                break;
            case 'l':
                table->printLaTeX();
                break;
            case 'r':
                table->reduce();
                table->print();
                break;
            case 'q':
                delete table;
                table = nullptr;
                return;
            default:
                cout << "Unknown command." << endl;
                break;
        }
    }
}

int main()
{
    SimplexTable* table = inputTable();

    table->print();

    loop(table);

    return 0;
}