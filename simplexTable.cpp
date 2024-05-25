#include <stdexcept>
#include <tgmath.h>
#include <string>
#include <vector>

#include "simplexTable.h"

using namespace std;

SimplexTable::SimplexTable(unsigned int columns, unsigned int rows)
{
    table = vector<vector<Fraction>>(columns, vector<Fraction>(rows, Fraction()));
    columnNames = vector<VarName>(columns - 1, VarName(false, 0));
    rowNames = vector<VarName>(rows, VarName(true, 0));

    for (unsigned int column = 0; column < columns - 1; column++)
        columnNames[column].number = column + 1;

    for (unsigned int row = 0; row < rows - 1; row++)
        rowNames[row].number = row + 1;
    rowNames[rows - 1] = VarName(false, 0u);
}

unsigned int SimplexTable::getColumnAmount() const
{
    return table.capacity();
}

unsigned int SimplexTable::getRowAmount() const
{
    return table[0].capacity();
}

Fraction SimplexTable::getCell(unsigned int column, unsigned int row) const
{
    return table[column][row];
}

void SimplexTable::setCell(unsigned int column, unsigned int row, const Fraction& val)
{
    table[column][row] = val;
}

void SimplexTable::setRow(unsigned int row, const vector<Fraction>& rowVals)
{
    if (rowVals.size() != table[0].size())
        throw invalid_argument("Row did not have the right amount of values.");

    for (unsigned int column = 0; column < rowVals.size(); column++)
        setCell(column, row, rowVals[column]);
}

void SimplexTable::setColumn(unsigned int column, const vector<Fraction>& columnVals)
{
    if (columnVals.size() != table.size())
        throw invalid_argument("Row did not have the right amount of values.");

    for (unsigned int row = 0; row < columnVals.size(); row++)
        setCell(column, row, columnVals[row]);
}

void SimplexTable::print() const
{
    cout << *this;
}

void printString(ostream& os, string str, unsigned int amount)
{
    for (unsigned int space = 0; space < amount; space++)
        os << str;
}

void SimplexTable::printLaTeX() const
{
    cout << "\\begin{tabular}{r|c|";
    printString(cout, "c", getColumnAmount() - 1);
    cout << "}" << endl;

    printString(cout, " ", 4); // tab
    cout << '&';
    for (unsigned int column = 0; column < getColumnAmount() - 1; column++)
        cout << " & " << columnNames[column].toLaTeX();
    cout << " \\\\ \\hline" << endl;

    for (unsigned int row = 0; row < getRowAmount(); row++) {
        printString(cout, " ", 4); // tab
        cout << rowNames[row].toLaTeX();
        for (unsigned int column = 0; column < getColumnAmount(); column++)
            cout << " & " << getCell(column, row).toLaTeX();

        if (row != getRowAmount() - 1) cout << " \\\\";
        if (row == getRowAmount() - 2) cout << " \\hline";
        cout << endl;
    }

    cout << "\\end{tabular}" << endl << endl;
}

void SimplexTable::reduce()
{
    for (vector<Fraction>& column : table)
        for (Fraction& fraction : column)
            fraction.reduce();
}

void SimplexTable::pivot(unsigned int pivotColumn, unsigned int pivotRow)
{
    Fraction pivot = getCell(pivotColumn, pivotRow);

    for (unsigned int column = 0; column < getColumnAmount(); column++) {
        if (column == pivotColumn) continue;

        Fraction columnVal = getCell(column, pivotRow);

        for (unsigned int row = 0; row < getRowAmount(); row++) {
            if (row == pivotRow) continue;

            Fraction newValue = getCell(column, row) - columnVal * getCell(pivotColumn, row) / pivot;
            setCell(column, row, newValue);
        }

        setCell(column, pivotRow, columnVal / pivot);
    }

    for (unsigned int row = 0; row < getRowAmount(); row++) {
        if (row == pivotRow) continue;
        setCell(pivotColumn, row, Fraction(-1) * getCell(pivotColumn, row) / pivot);
    }

    setCell(pivotColumn, pivotRow, Fraction(1) / pivot);

    if (pivotColumn == 0) return;
    VarName temp = columnNames[pivotColumn - 1];
    columnNames[pivotColumn - 1] = rowNames[pivotRow];
    rowNames[pivotRow] = temp;
}

unsigned int SimplexTable::getColumnPrintLength(unsigned int column) const
{
    if (column == 0) return floor(log10(getRowAmount() - 1)) + 2; // Variable name row

    unsigned int maxLength = (column >= 2) ? floor(log10(getColumnAmount() - 1)) + 2 : 0; // Variable name column

    for (unsigned int row = 1; row <= getRowAmount(); row++) {
        unsigned int length = getCell(column - 1, row - 1).getPrintLength();
        maxLength = max(length, maxLength);
    }
    
    return maxLength;
}

unsigned int SimplexTable::getColumnStartChar(unsigned int column) const
{
    unsigned int sum = 2 * min(column, 2u); // Column separators
    for (unsigned int col = 0; col < column; col++)
        sum += getColumnPrintLength(col) + 1; // Number length + space

    return sum;
}

unsigned int SimplexTable::getRowPrintLength() const
{
    return getColumnStartChar(getColumnAmount() + 1);
}

void SimplexTable::printHLine(ostream& os) const
{
    for (unsigned int cell = 0; cell <= 1u; cell++) {
        printString(os, "─", getColumnPrintLength(cell) + 1 + cell);
        os << "┼";
    }

    for (unsigned int cell = 2; cell <= getColumnAmount(); cell++)
        printString(os, "─", getColumnPrintLength(cell) + 1);

    os << endl;
}

ostream& operator<<(ostream& os, const SimplexTable& table)
{
    os << endl;
    
    for (unsigned int cell = 0; cell <= 1u; cell++) {
        printString(os, " ", table.getColumnPrintLength(cell) + 1);
        os << "│ ";
    }
    for (unsigned int cell = 2; cell <= table.getColumnAmount(); cell++) {
        printString(os, " ", table.getColumnPrintLength(cell) - table.columnNames[cell - 2].toString().size());
        os << table.columnNames[cell - 2].toString();
        os << ' ';
    }
    os << endl;
    table.printHLine(os);

    for (unsigned int row = 1; row <= table.getRowAmount(); row++) {
        printString(os, " ", table.getColumnPrintLength(0) - table.rowNames[row - 1].toString().size());
        os << table.rowNames[row - 1].toString();
        os << " │ ";

        for (unsigned int column = 1; column <= table.getColumnAmount(); column++) {
            printString(os, " ", table.getColumnPrintLength(column) - table.getCell(column - 1, row - 1).getPrintLength());
            os << table.getCell(column - 1, row - 1);
            os << ' ';

            if (column == 1)
                os << "│ ";
        }

        cout << endl;

        if (row == table.getRowAmount() - 1)
            table.printHLine(os);
    }

    os << endl;

    return os;
}

VarName::VarName(bool b, unsigned int num)
{
    basis = b;
    number = num;
}

char VarName::getCharacter() const
{
    return basis ? 'y' : 'x';
}

string VarName::toString() const
{
    return getCharacter() + to_string(number);
}

string VarName::toLaTeX() const
{
    return string("$", 1) + getCharacter() + "_{" + to_string(number) + "}$";
}
