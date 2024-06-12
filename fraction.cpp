#include <iostream>
#include <numeric>
#include <tgmath.h>
#include <regex>

#include "fraction.h"

using namespace std;

Fraction::Fraction(int num, int den)
{
    setNumerator(num);
    setDenominator(den);
    reduce();
}

Fraction::Fraction(const Fraction& other)
{
    setNumerator(other.getNumerator());
    setDenominator(other.getDenominator());
}

int Fraction::getNumerator() const
{
    return numerator;
}

void Fraction::setNumerator(int num)
{
    numerator = num;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::setDenominator(int den)
{
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

void Fraction::operator=(const Fraction& other)
{
    setNumerator(other.getNumerator());
    setDenominator(other.getDenominator());
}

void Fraction::operator=(const int other)
{
    setNumerator(other);
    setDenominator(1);
}

Fraction Fraction::operator+(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator() + other.getNumerator() * getDenominator(),
        getDenominator() * other.getDenominator()
    );
}

void Fraction::operator+=(const Fraction& other)
{
    setNumerator(getNumerator() * other.getDenominator() + other.getNumerator() * getDenominator());
    setDenominator(getDenominator() * other.getDenominator());
    reduce();
}

Fraction Fraction::operator+(const int other) const
{
    return Fraction(
        getNumerator() + other * getDenominator(),
        getDenominator()
    );
}

void Fraction::operator+=(const int other)
{
    setNumerator(getNumerator() + other * getDenominator());
}

Fraction Fraction::operator-(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator() - other.getNumerator() * getDenominator(),
        getDenominator() * other.getDenominator()
    );
}

void Fraction::operator-=(const Fraction& other)
{
    setNumerator(getNumerator() * other.getDenominator() - other.getNumerator() * getDenominator());
    setDenominator(getDenominator() * other.getDenominator());
    reduce();
}

Fraction Fraction::operator-(const int other) const
{
    return Fraction(
        getNumerator() - other * getDenominator(),
        getDenominator()
    );
}

void Fraction::operator-=(const int other)
{
    setNumerator(getNumerator() - other * getDenominator());
}

Fraction Fraction::operator*(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getNumerator(),
        getDenominator() * other.getDenominator()
    );
}

void Fraction::operator*=(const Fraction& other)
{
    setNumerator(getNumerator() * other.getNumerator());
    setDenominator(getDenominator() * other.getDenominator());
    reduce();
}

Fraction Fraction::operator*(const int other) const
{
    return Fraction(
        getNumerator() * other,
        getDenominator()
    );
}

void Fraction::operator*=(const int other)
{
    setNumerator(getNumerator() * other);
    reduce();
}

Fraction Fraction::operator/(const Fraction& other) const
{
    return Fraction(
        getNumerator() * other.getDenominator(),
        getDenominator() * other.getNumerator()
    );
}

void Fraction::operator/=(const Fraction& other)
{
    setNumerator(getNumerator() * other.getDenominator());
    setDenominator(getDenominator() * other.getNumerator());
    reduce();
}

Fraction Fraction::operator/(const int other) const
{
    return Fraction(
        getNumerator(),
        getDenominator() * other
    );
}

void Fraction::operator/=(const int other)
{
    setDenominator(getDenominator() * other);
    reduce();
}

void Fraction::invert()
{
    int numerator = getNumerator();
    setNumerator(getDenominator());
    setDenominator(numerator);
}

Fraction Fraction::getInverted() const
{
    return Fraction(
        getDenominator(),
        getNumerator()
    );
}

bool Fraction::operator==(const Fraction& other) const
{
    Fraction firstReduced = getReduced();
    Fraction secondReduced = other.getReduced();

    return (firstReduced.getNumerator() == secondReduced.getNumerator() &&
        firstReduced.getDenominator() == secondReduced.getDenominator());
}

bool Fraction::operator!=(const Fraction& other) const
{
    return !(*this == other);
}

bool Fraction::operator==(const int other) const
{
    Fraction reduced = getReduced();

    return (reduced.getDenominator() == 1 &&
        reduced.getNumerator() == other);
}

bool Fraction::operator!=(const int other) const
{
    return !(*this == other);
}

string Fraction::toLaTeX() const
{
    string retVal = ((getNumerator() < 0) == (getDenominator() < 0)) ? "$" : "$-";

    if (abs(getDenominator()) == 1)
        return retVal + to_string(abs(getNumerator())) + "$";

    return retVal + "\\frac{" + to_string(abs(getNumerator())) + "}{" + to_string(abs(getDenominator())) + "}$";
}

unsigned int Fraction::getPrintLength() const
{
    Fraction reduced = getReduced();
    unsigned int length = (reduced.getNumerator() != 0) ? (floor(log10(abs(reduced.getNumerator()))) + 1) : 1;
    if (reduced.getDenominator() != 1) { // "Over 1" gets simplified to the numerator
        length++; // '/' sign
        length += floor(log10(reduced.getDenominator())) + 1;
    }
    if (reduced.getNumerator() < 0) length++;

    return length;
}

Fraction::operator double() const
{
    return (double)getNumerator() / getDenominator();
}

string getFirstRegexMatch(const string& str, const regex& regexObj)
{
    auto begin = sregex_iterator(str.begin(), str.end(), regexObj);
    auto end = sregex_iterator();

    return (distance(begin, end) != 0) ? ((smatch)*(sregex_iterator)begin).str() : "";
}

Fraction Fraction::parseString(const string& originalString)
{
    regex leadingSpaces = regex("^ +");
    regex leadingNumber = regex("^-?[0-9]+");

    string str = originalString;

    // Remove leading spaces
    str = regex_replace(str, leadingSpaces, "");

    size_t slashPos = str.find('/');
    if (slashPos == string::npos || slashPos == str.size() - 1) {
        // Fetch uninterrupted sequence of numbers directly after leading spaces
        return Fraction(stoi(getFirstRegexMatch(str, leadingNumber)));
    }

    string numeratorSection = str.substr(0, slashPos);
    string denominatorSection = str.substr(slashPos + 1, str.size());
    denominatorSection = regex_replace(denominatorSection, leadingSpaces, "");

    int numerator, denominator;
    try {
        numerator = stoi(getFirstRegexMatch(numeratorSection, leadingNumber));
    } catch(invalid_argument& e) {
        numerator = 0;
    }

    try {
        denominator = stoi(getFirstRegexMatch(denominatorSection, leadingNumber));
    } catch(invalid_argument& e) {
        denominator = 0;
    }

    return Fraction(numerator, denominator);
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

    os << reduced.getNumerator();
    if (reduced.getDenominator() != 1)
        os << '/' << reduced.getDenominator();

    return os;
}
