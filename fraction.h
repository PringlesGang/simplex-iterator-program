#pragma once

#include <iostream>

using namespace std;

class Fraction
{
    public:
        Fraction(int numerator = 0, int denominator = 1);
        Fraction(const Fraction& other);

        int getNumerator() const;
        void setNumerator(int numerator);

        int getDenominator() const;
        void setDenominator(int denominator);

        Fraction getReduced() const;
        void reduce();

        void operator=(const Fraction& other);
        void operator=(const int other);

        Fraction operator+(const Fraction& other) const;
        void operator+=(const Fraction& other);
        Fraction operator+(const int other) const;
        void operator+=(const int other);

        Fraction operator-(const Fraction& other) const;
        void operator-=(const Fraction& other);
        Fraction operator-(const int other) const;
        void operator-=(const int other);

        Fraction operator*(const Fraction& other) const;
        void operator*=(const Fraction& other);
        Fraction operator*(const int other) const;
        void operator*=(const int other);

        Fraction operator/(const Fraction& other) const;
        void operator/=(const Fraction& other);
        Fraction operator/(const int other) const;
        void operator/=(const int other);
        void invert();
        Fraction getInverted() const;

        bool operator==(const Fraction& other) const;
        bool operator!=(const Fraction& other) const;
        bool operator==(const int other) const;
        bool operator!=(const int other) const;

        string toLaTeX() const;
        friend ostream& operator<<(ostream& os, const Fraction& fraction);
        unsigned int getPrintLength() const;

        operator double() const;

        static Fraction parseString(const string& str);

    private:
        int numerator, denominator;

        int gcd(int a, int b) const;
};
