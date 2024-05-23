#include <iostream>
#include <numeric>
#include <tgmath.h>

#include "fraction.h"

using namespace std;

Fraction::Fraction() {
    setNumerator(0);
    setDenominator(1);
}

Fraction::Fraction(int num, int den, bool red) {
    setNumerator(num);
    setDenominator(den);
    if (red) reduce();
}

int Fraction::getNumerator() const {
    return numerator;
}

void Fraction::setNumerator(int num) {
    numerator = num;
}

int Fraction::getDenominator() const {
    return denominator;
}

void Fraction::setDenominator(int den) {
    if (den == 0)
        throw invalid_argument("Cannot divide by 0.");

    denominator = den;
}

Fraction Fraction::getReduced() const
{
    Fraction fraction(*this);
    fraction.reduce();
    return fraction;
}

void Fraction::reduce()
{
    if (getNumerator() == 0) {
        setDenominator(1);
        return;
    }

    int divisor = gcd(getNumerator(), getDenominator());
    int sign = ((getNumerator() < 0) == (getDenominator() < 0)) ? 1 : -1;

    setNumerator(sign * abs(getNumerator()) / divisor);
    setDenominator(abs(getDenominator()) / divisor);
}

Fraction Fraction::operator+(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator() + other.getNumerator() * getDenominator(),
        getDenominator() * other.getDenominator(),
        true
    );
}

Fraction Fraction::operator-(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator() - other.getNumerator() * getDenominator(),
        getDenominator() * other.getDenominator(),
        true
    );
}

Fraction Fraction::operator*(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getNumerator(),
        getDenominator() * other.getDenominator(),
        true
    );
}

Fraction Fraction::operator/(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator(),
        getDenominator() * other.getNumerator(),
        true
    );
}

unsigned int Fraction::getPrintLength() const
{
    return ceil(log10(getNumerator())) + 1 + ceil(log10(getDenominator()));
}

Fraction::operator double() const
{
    return (double)getNumerator() / getDenominator();
}

int Fraction::gcd(int a, int b) const
{
    // Euclid's algorithm
    int smaller = min(abs(a), abs(b));
    int larger = max(abs(a), abs(b));

    while (true) {
        int remainder = larger % smaller;
        if (remainder == 0) return smaller;

        larger = smaller;
        smaller = remainder;
    }
}

ostream& operator<<(ostream& os, const Fraction& fraction)
{
    Fraction reduced = fraction.getReduced();
    os << reduced.getNumerator() << '/' << reduced.getDenominator();
    return os;
}
