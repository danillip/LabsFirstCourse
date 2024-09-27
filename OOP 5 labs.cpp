#ifndef FIGURE_H
#define FIGURE_H

#include <cmath>

class Figure {
protected:
    int* arr;
    int n;

public:
    Figure(int* mas, int N) : n(N) 
    {
        arr = new int[n];
        for (int i=0, i<n,i++)
         arr[i] = mas[i];
     }

    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    // массив + размерность 
};

class Rectangle : public Figure {
private:
    //double sides[2]; // 2D array
    //в каждом наследнике размерность фиксирована по кол-ву параметров

public:
    Rectangle(int* mas) : Figure(mas, 2) {};

    double area() const override;
    double perimeter() const override;
};

class Circle : public Figure {
private:
    double radius; // 1D array

public:
    Circle(int id, double r);

    double area() const override;
    double perimeter() const override;
};

class Trapezius : public Figure {
private:
    double sides[4]; // 4D array

public:
    Trapezius(int id, double a, double b, double h);

    double area() const override;
    double perimeter() const override;
};

#endif // FIGURE_H

///////////////////////////////////////////////////////

#include "Figure.h"
double M_PI = 3.14;

Rectangle::Rectangle(int id, double l, double w) : Figure(id) {
    sides[0] = l;
    sides[1] = w;
}

double Rectangle::area() const {
    return sides[0] * sides[1];
}

double Rectangle::perimeter() const {
    return 2 * (sides[0] + sides[1]);
}

Circle::Circle(int id, double r) : Figure(id), radius(r) {}

double Circle::area() const {
    return M_PI * radius * radius;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius;
}

Trapezius::Trapezius(int id, double a, double b, double h) : Figure(id) {
    sides[0] = a;
    sides[1] = b;
    sides[2] = h;
}

double Trapezius::area() const {
    return (sides[0] + sides[1]) * sides[2] / 2.0;
}

double Trapezius::perimeter() const {
    return sides[0] + sides[1] + 2 * sqrt(pow((sides[1] - sides[0]) / 2.0, 2) + pow(sides[2], 2));
}

//////////////////////////////////////////////////////////

#include <iostream>
#include "Figure.h"

int main() {
    setlocale(LC_ALL, "Ru");
    Figure* p = new Rectangle(1,4.0, 6.0);
    Figure* q = new Circle(2, 3.0);
    Figure* r = new Trapezius(3, 7.0, 5.0, 4.0);

    std::cout << "Площадь прямоугольника: " << p->area() << std::endl;
    std::cout << "Периметр прямоугольника: " << p->perimeter() << std::endl;

    std::cout << "Площадь круга: " << q->area() << std::endl;
    std::cout << "Периметр круга: " << q->perimeter() << std::endl;

    std::cout << "Площадь трапеции: " << r->area() << std::endl;
    std::cout << "Периметр трапеции: " << r->perimeter() << std::endl;

    delete p;
    delete q;
    delete r;

    return 0;
}

