Для решения задачи Иосифа Флавия и задачи перестановки элементов списка по условию, давайте сначала добавим необходимые функции и затем решим обе задачи.

Вот функции, которые помогут решить задачу Иосифа Флавия:
Tlist josephusFlavius(int totalWarriors, int killInterval) {
    Tlist warriors = createByOrder(totalWarriors);

    Tlist currentWarrior = warriors;
    Tlist previousWarrior = nullptr;

    while (totalWarriors > 1) {
        for (int i = 0; i < killInterval - 1; ++i) {
            previousWarrior = currentWarrior;
            currentWarrior = currentWarrior->next;
        }

        Tlist nextWarrior = currentWarrior->next;
        if (previousWarrior == nullptr) {
            warriors = nextWarrior;
        } else {
            previousWarrior->next = nextWarrior;
        }

        delete currentWarrior;
        currentWarrior = nextWarrior;
        --totalWarriors;
    }

    return warriors;
}


......
Теперь давайте рассмотрим решение задачи перестановки элементов между первым и последним вхождением элемента E, 
если E входит в список не менее двух раз. В этом решении будет использоваться указатель middleList, который будет указывать на середину списка.
void reverseBetweenElements(Tlist& head, datatype elem) {
    Tlist firstElem = nullptr;
    Tlist lastElem = nullptr;
    Tlist current = head;
    Tlist middleList = nullptr;
    int count = 0;

    while (current) {
        if (current->data == elem) {
            if (firstElem == nullptr) {
                firstElem = current;
            } else {
                lastElem = current;
            }
            count++;
        }
        current = current->next;
    }

    if (count < 2) {
        return; // Элемент встречается менее двух раз
    }

    current = head;
    while (current != firstElem) {
        middleList = current;
        current = current->next;
    }

    Tlist reversedSublist = nullptr;
    Tlist next = nullptr;

    while (current != lastElem) {
        next = current->next;
        current->next = reversedSublist;
        reversedSublist = current;
        current = next;
    }

    middleList->next = reversedSublist;
    firstElem->next = lastElem->next;
    lastElem->next = current;
}


.........
Для объединения двух упорядоченных по не убыванию списков в один также упорядоченный по не убыванию, вы можете использовать следующую функцию:
Эта функция объединяет два упорядоченных списка list1 и list2 в новый список mergedList, который также будет 
упорядочен по неубыванию. Вы можете вызвать эту функцию, передав два списка в качестве аргументов, и она вернет объединенный список.
Tlist mergeSortedLists(Tlist list1, Tlist list2) {
    Tlist mergedList = nullptr;
    Tlist current = nullptr;

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data <= list2->data) {
            if (mergedList == nullptr) {
                mergedList = list1;
                current = list1;
            } else {
                current->next = list1;
                current = current->next;
            }
            list1 = list1->next;
        } else {
            if (mergedList == nullptr) {
                mergedList = list2;
                current = list2;
            } else {
                current->next = list2;
                current = current->next;
            }
            list2 = list2->next;
        }
    }

    if (list1 != nullptr) {
        if (mergedList == nullptr) {
            mergedList = list1;
        } else {
            current->next = list1;
        }
    }

    if (list2 != nullptr) {
        if (mergedList == nullptr) {
            mergedList = list2;
        } else {
            current->next = list2;
        }
    }

    return mergedList;
}
