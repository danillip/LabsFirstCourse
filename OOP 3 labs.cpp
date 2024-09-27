#include <iostream>
#include <cmath>

class Angle {
    int degrees; // Изменили тип данных на int

public:
    Angle() : degrees(0) {}
    Angle(int deg) {
    if (deg >= 0 && deg < 360) {
        setDegrees(deg);
    } else {
        std::cerr << "Недопустимое значение угла! Угол должен быть в диапазоне [0, 360)." << std::endl;
        // По умолчанию устанавливаем угол в 0 градусов, но вы можете выбрать другое действие.
        setDegrees(0);
    }
    }
    void setDegrees(int deg) {
    // Приводим угол к диапазону [0, 360) градусов
    degrees = deg % 360;
    if (degrees < 0) {
        degrees += 360;
    }
    }
    int getDegrees() const {
        return degrees;
    }
    double toRadians() const {
        return static_cast<double>(degrees) * M_PI / 180.0;
    }
    void increase(int deg) {
        degrees += deg;
        setDegrees(degrees);
    }
    void decrease(int deg) {
        degrees -= deg;
        setDegrees(degrees);
    }
    double sin() const {
        return std::sin(toRadians());
    }
    bool operator==(const Angle& other) const {
        return degrees == other.degrees;
    }
    bool operator!=(const Angle& other) const {
        return !(*this == other);
    }
};

class Triangle {
    Angle angles[3];
    double sides[3];

public:
    Triangle(double side1, double side2, double side3) {
        sides[0] = side1;
        sides[1] = side2;
        sides[2] = side3;
        calculateAngles();
    }
    void calculateAngles() {
        for (int i = 0; i < 3; i++) {
            int j = (i + 1) % 3;
            int k = (i + 2) % 3;
            angles[i].setDegrees(static_cast<int>(acos((sides[j] * sides[j] + sides[k] * sides[k] - sides[i] * sides[i]) / (2 * sides[j] * sides[k])) * 180.0 / M_PI));
        }
    }
    double getSide(int index) const {
        if (index >= 0 && index < 3) {
            return sides[index];
        }
        else {
            std::cerr << "Неверный индекс стороны!" << std::endl;
            return -1.0;
        }
    }
    void setSide(int index, double value) {
        if (index >= 0 && index < 3) {
            sides[index] = value;
            calculateAngles();
        }
        else {
            std::cerr << "Неверный индекс стороны!" << std::endl;
        }
    }
    double calculateArea() const {
        double s = calculatePerimeter() / 2;
        return sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2]));
    }
    double calculatePerimeter() const {
        return sides[0] + sides[1] + sides[2];
    }
    double calculateHeight(int sideIndex) const {
        if (sideIndex >= 0 && sideIndex < 3) {
            return (2.0 * calculateArea()) / sides[sideIndex];
        }
        else {
            std::cerr << "Неверный индекс стороны!" << std::endl;
            return -1.0;
        }
    }
    std::string determineType() const {
        if (sides[0] == sides[1] && sides[1] == sides[2]) {
            return "Равносторонний";
        }
        else if (sides[0] == sides[1] || sides[1] == sides[2] || sides[0] == sides[2]) {
            return "Равнобедренный";
        }
        else {
            bool isRightAngle = false;
            for (int i = 0; i < 3; i++) {
                if (angles[i].getDegrees() == 90) { // Изменили тип на int
                    isRightAngle = true;
                    break;
                }
            }

            if (isRightAngle) {
                return "Прямоугольный";
            }
            else {
                return "Произвольный";
            }
        }
    }

    int getAngle1Degrees() const {
        return angles[0].getDegrees();
    }
    int getAngle2Degrees() const {
        return angles[1].getDegrees();
    }
    int getAngle3Degrees() const {
        return angles[2].getDegrees();
    }
    // Оператор вывода для класса Triangle
    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
        os << "Сторона 1: " << triangle.getSide(0) << std::endl;
        os << "Сторона 2: " << triangle.getSide(1) << std::endl;
        os << "Сторона 3: " << triangle.getSide(2) << std::endl;
        os << "Угол 1: " << triangle.getAngle1Degrees() << " градусов" << std::endl;
        os << "Угол 2: " << triangle.getAngle2Degrees() << " градусов" << std::endl;
        os << "Угол 3: " << triangle.getAngle3Degrees() << " градусов" << std::endl;
        os << "Площадь треугольника: " << triangle.calculateArea() << std::endl;
        os << "Периметр треугольника: " << triangle.calculatePerimeter() << std::endl;
        os << "Высота к стороне 1: " << triangle.calculateHeight(0) << std::endl;
        os << "Высота к стороне 2: " << triangle.calculateHeight(1) << std::endl;
        os << "Высота к стороне 3: " << triangle.calculateHeight(2) << std::endl;
        os << "Тип треугольника: " << triangle.determineType() << std::endl;
        return os;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    double side1 = 3.0;
    double side2 = 4.0;
    double side3 = 5.0;

    Triangle triangle(side1, side2, side3);

    // Теперь можно использовать оператор вывода для объекта треугольника
    std::cout << triangle;

    return 0;
}
