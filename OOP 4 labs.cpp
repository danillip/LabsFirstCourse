#include "Pair.h"
#include <iostream>

Pair::Pair(int a, int b) : first(a), second(b) {}

bool Pair::operator==(const Pair& other) const {
    return (first == other.first) && (second == other.second);
}

Pair Pair::operator*(const Pair& other) const {
    return Pair(first * other.first, second * other.second);
}

Pair Pair::operator-(const Pair& other) const {
    return Pair(first - other.first, second - other.second);
}

Pair Pair::operator+(const Pair& other) const {
    return Pair(first + other.first, second + other.second);
}

Pair Pair::operator/(const Pair& other) const {
    if (other.first == 0 || other.second == 0) {
        std::cerr << "Ошибка: Деление на ноль." << std::endl;
        return Pair(0, 1); // Вернуть значение по умолчанию
    }
    return Pair(first * other.second, second * other.first);
}

void Pair::print() const {
    std::cout << "(" << first << ", " << second << ")";
}

int Pair::getFirst() const { return first; }

int Pair::getSecond() const { return second; }

///////////////////////////////////////////////////

#ifndef PAIR_H
#define PAIR_H

class Pair {
public:
    Pair(int a, int b);

    bool operator==(const Pair& other) const;
    Pair operator*(const Pair& other) const;
    Pair operator-(const Pair& other) const;
    Pair operator+(const Pair& other) const;
    Pair operator/(const Pair& other) const;

    void print() const;
    int getFirst() const;
    int getSecond() const;

 

protected:
    int first;
    int second;
};

#endif

///////////////////////////////////////////////////

#include "Rational.h"
#include <iostream>

Rational::Rational(const Pair& pair) : Pair(pair) {}

Rational::Rational(int a, int b) : Pair(a, b) {
    reduce();
}

void Rational::print() const {
    std::cout << "(" << first << "/" << second << ")";
}

void Rational::reduce() {
    int gcd = findGCD(first, second);
    first /= gcd;
    second /= gcd;
}

int Rational::findGCD(int a, int b) {
    if (b == 0)
        return a;
    return findGCD(b, a % b);
}

Rational Rational::operator*(const Rational& other) const
{
    Pair tmp = Pair::operator*(other);
    Rational res(tmp.getFirst(), tmp.getSecond());
    res.reduce();
    return res;
}

Rational Rational::operator+(const Rational& other) const {
    int new_first = (first * other.getSecond) + (other.getFirst() * second);
    int new_second = second * other.getSecond();
    return Rational(new_first, new_second);
}

Rational Rational::operator-(const Rational& other) const {
    int new_first = (first * other.getSecond()) - (other.getFirst() * second);
    int new_second = second * other.getSecond();
    return Rational(new_first, new_second);
}

Rational Rational::operator/(const Rational& other) const {
    Pair tmp = Pair::operator/(other);
    Rational res(tmp.getFirst(), tmp.getSecond());
    res.reduce();
    return res;
}

//////////////////////////////////////////////////////////////

#ifndef RATIONAL_H
#define RATIONAL_H
#include "Pair.h"

class Rational : public Pair {
public:
    Rational(const Pair& pair);
    Rational(int a, int b);
    void reduce();
    static int findGCD(int a, int b);
    Rational operator*(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator+(const Rational& other) const;
    void print() const;
};

#endif

////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Pair.h"
#include "Rational.h"

int getRandomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int main() {
    setlocale   (LC_ALL,"RU");
    srand(static_cast<unsigned>(time(0)));

    char inputMethod;
    std::cout << "Введите 'K' для ввода с клавиатуры или 'R' для случайного ввода: ";
    std::cin >> inputMethod;

    Pair pair1(0, 0);
    Pair pair2(0, 0);

    if (inputMethod == 'K') {
        int a, b, c, d;
        std::cout << "Введите значения для pair1 (a, b): ";
        std::cin >> a >> b;

        std::cout << "Введите значения для pair2 (c, d): ";
        std::cin >> c >> d;

        pair1 = Pair(a, b);
        pair2 = Pair(c, d);
    }
    else if (inputMethod == 'R') {
        pair1 = Pair(getRandomInt(1, 10), getRandomInt(1, 10));
        pair2 = Pair(getRandomInt(1, 10), getRandomInt(1, 10));
    }
    else {
        std::cerr << "Неверный метод ввода. Введите 'K' или 'R'." << std::endl;
        return 1;
    }

    std::cout << "Pair1: ";
    pair1.print();
    std::cout << std::endl;

    std::cout << "Pair2: ";
    pair2.print();
    std::cout << std::endl;

    Pair productPair = pair1 * pair2;
    std::cout << "Pair1 * Pair2: ";
    productPair.print();
    std::cout << std::endl;

    Pair sumPair = pair1 + pair2;
    std::cout << "Pair1 + Pair2: ";
    sumPair.print();
    std::cout << std::endl;

    Pair differencePair = productPair - pair1;
    std::cout << "Pair1 * Pair2 - Pair1: ";
    differencePair.print();
    std::cout << std::endl;

    Rational rational1(pair1);
    Rational rational2(pair2);

    std::cout << "Rational1: ";
    rational1.print();
    std::cout << std::endl;

    std::cout << "Rational2: ";
    rational2.print();
    std::cout << std::endl;

    Rational productRational = rational1 * rational2;
    std::cout << "Rational1 * Rational2: ";
    productRational.print();
    std::cout << std::endl;

    Rational sumRational = rational1 + rational2;
    std::cout << "Rational1 + Rational2: ";
    sumRational.print();
    std::cout << std::endl;

    Rational subtractionRational = productRational - rational1;
    std::cout << "Rational1 * Rational2 - Rational1: ";
    subtractionRational.print();
    std::cout << std::endl;

    return 0;
}