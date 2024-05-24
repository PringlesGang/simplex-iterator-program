#include <stdexcept>
#include <tgmath.h>
#include "simplexTable.h"

using namespace std;

SimplexTable::SimplexTable(unsigned int columns, unsigned int rows)
{
    table.reserve(columns);
    for (vector<Fraction>& column : table) {
        column.reserve(rows);

        for (Fraction& fraction : column)
            fraction = Fraction();
    }
}

unsigned int SimplexTable::getColumnAmount() const
{
    return table[0].capacity();
}

unsigned int SimplexTable::getRowAmount() const
{
    return table.capacity();
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

    for (int column = 0; column < rowVals.size(); column++)
        setCell(column, row, rowVals[column]);
}

void SimplexTable::setColumn(unsigned int column, const vector<Fraction>& columnVals)
{
    if (columnVals.size() != table.size())
        throw invalid_argument("Row did not have the right amount of values.");

    for (int row = 0; row < columnVals.size(); row++)
        setCell(column, row, columnVals[row]);
}

void SimplexTable::printLaTeX() const
{
    throw "Not yet implemented.";
}

void SimplexTable::reduce()
{
    for (vector<Fraction>& column : table)
        for (Fraction& fraction : column)
            fraction.reduce();
}

unsigned int SimplexTable::getColumnPrintLength(unsigned int column) const
{
    unsigned int maxLength = 0;

    for (const vector<Fraction>& column : table)
        for (const Fraction& fraction : column) {
            unsigned int length = fraction.getPrintLength();
            maxLength = max(length, maxLength);
        }
    
    return maxLength + 1;
}

unsigned int SimplexTable::getRowPrintLength() const
{
    unsigned int sum = 0;
    for (unsigned int column = 0; column < getColumnAmount(); column++)
        sum += getColumnPrintLength(column);

    return sum;
}

ostream& operator<<(ostream& os, const SimplexTable& table)
{
    os << endl;
    for (unsigned int row = 0; row < table.getRowAmount(); row++) {
        for (unsigned int column = 0; column < table.getColumnAmount(); column++) {
            os << table.getCell(column, row);

            for (int space = table.getCell(column, row).getPrintLength(); space < table.getColumnPrintLength(column); space++) {
                os << ' ';
            }

            if (column != table.getColumnAmount() - 1)
                os << '|';
        }

        if (row != table.getRowAmount() - 1) {
            os << endl;
            for (unsigned int character = 0; character < table.getRowPrintLength(); character++)
                os << '-';
        }
        os << endl;
    }
}
