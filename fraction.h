#pragma once

class Fraction {
    public:
        Fraction();
        Fraction(int numerator, int denominator = 1, bool reduce = false);

        int getNumerator() const;
        void setNumerator(int numerator);

        int getDenominator() const;
        void setDenominator(int denominator);

        Fraction getReduced() const;
        void reduce();

        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

        friend ostream& operator<<(ostream& os, const Fraction& fraction);
        unsigned int getPrintLength() const;

        operator double() const;

    private:
        int numerator, denominator;

        int gcd(int a, int b) const;
};
