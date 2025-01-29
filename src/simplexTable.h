#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "fraction.h"

using namespace std;

class VarName
{
    public:
        bool basis;
        unsigned int number;

        VarName(bool basis, unsigned int number);

        char getCharacter() const;
        string toString() const;
        string toLaTeX() const;
};

class SimplexTable
{
    public:
        SimplexTable(unsigned int columns, unsigned int rows);

        unsigned int getColumnAmount() const;
        unsigned int getRowAmount() const;

        Fraction getCell(unsigned int column, unsigned int row) const;
        void setCell(unsigned int column, unsigned int row, const Fraction& val);
        void setRow(unsigned int row, const vector<Fraction>& rowVals);
        void setColumn(unsigned int column, const vector<Fraction>& columnVals);

        void print() const;
        void printLaTeX() const;
        friend ostream& operator<<(ostream& os, const SimplexTable& table);

        void reduce();
        void pivot(unsigned int column, unsigned int row);

    private:
        vector<vector<Fraction>> table;
        vector<VarName> columnNames;
        vector<VarName> rowNames;

        unsigned int getColumnPrintLength(unsigned int column) const;
        unsigned int getRowPrintLength() const;
        unsigned int getColumnStartChar(unsigned int column) const;
        void printHLine(ostream& os) const;
};