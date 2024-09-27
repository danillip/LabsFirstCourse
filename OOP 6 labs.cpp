#include <iostream>
#include <set>

template <typename T>
class Set {
private:
    std::set<T> elements;

public:
    // Добавление элемента в множество
    void add(const T& element) {
        elements.insert(element);
    }

    // Удаление элемента из множества
    void remove(const T& element) {
        elements.erase(element);
    }

    // Объединение множеств
    Set<T> unionSet(const Set<T>& otherSet) const {
        Set<T> result = *this;
        for (const auto& element : otherSet.elements) {
            result.add(element);
        }
        return result;
    }

    // Пересечение множеств
    Set<T> intersection(const Set<T>& otherSet) const {
        Set<T> result;
        for (const auto& element : elements) {
            if (otherSet.contains(element)) {
                result.add(element);
            }
        }
        return result;
    }

    // Вычитание множеств
    Set<T> difference(const Set<T>& otherSet) const {
        Set<T> result = *this;
        for (const auto& element : otherSet.elements) {
            result.remove(element);
        }
        return result;
    }

    // Количество элементов в множестве
    size_t size() const {
        return elements.size();
    }

    // Проверка присутствия элемента в множестве
    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    // Проверка включения одного множества в другое
    bool includes(const Set<T>& otherSet) const {
        for (const auto& element : otherSet.elements) {
            if (!contains(element)) {
                return false;
            }
        }
        return true;
    }

    // Вывод множества на экран
    void display() const {
        std::cout << "{ ";
        for (const auto& element : elements) {
            std::cout << element << " ";
        }
        std::cout << "}" << std::endl;
    }
};

int main() {
    // Пример использования
    Set<double> set1, set2;

    set1.add(1.1);
    set1.add(2.2);
    set1.add(3.3);

    set2.add(2.2);
    set2.add(3.3);
    set2.add(4.4);

    std::cout << "Множество 1: ";
    set1.display();

    std::cout << "Множество 2: ";
    set2.display();

    Set<double> unionResult = set1.unionSet(set2);
    std::cout << "Объединение: ";
    unionResult.display();

    Set<double> intersectionResult = set1.intersection(set2);
    std::cout << "Пересечение: ";
    intersectionResult.display();

    Set<double> differenceResult = set1.difference(set2);
    std::cout << "Разность: ";
    differenceResult.display();

    std::cout << "Размер множества 1: " << set1.size() << std::endl;
    std::cout << "Присутствует ли 4.4 в множестве 1? " << (set1.contains(4.4) ? "Да" : "Нет") << std::endl;
    std::cout << "Включено ли множество 1 в множество 2? " << (set2.includes(set1) ? "Да" : "Нет") << std::endl;

    return 0;
}
