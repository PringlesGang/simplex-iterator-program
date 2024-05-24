#pragma once

#include <vector>

#include "fraction.h"

using namespace std;

class SimplexTable {
    public:
        SimplexTable(unsigned int columns, unsigned int rows);

        unsigned int getColumnAmount() const;
        unsigned int getRowAmount() const;

        Fraction getCell(unsigned int column, unsigned int row) const;
        void setCell(unsigned int column, unsigned int row, const Fraction& val);
        void setRow(unsigned int row, const vector<Fraction>& rowVals);
        void setColumn(unsigned int column, const vector<Fraction>& columnVals);

        void printLaTeX() const;
        friend ostream& operator<<(ostream& os, const SimplexTable& table);

        void reduce();

    private:
        vector<vector<Fraction>> table;

        unsigned int getColumnPrintLength(unsigned int column) const;
        unsigned int getRowPrintLength() const;
};