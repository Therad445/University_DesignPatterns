#include "Unit.h"
#include "State.h"
#include "Strategy.h"
#include <iostream>
#include <vector>

int main() {
    setlocale(LC_ALL, "Russian");
    // Создание фабрик юнитов
    ElfFactory elfFactory;
    OrcFactory orcFactory;

    // Вектор для хранения созданных юнитов
    std::vector<std::unique_ptr<Unit>> units;

    // Создание состояний
    AttackingState attackingState;
    MovingState movingState;

    // Создание стратегий
    AggressiveStrategy aggressiveStrategy;
    DefensiveStrategy defensiveStrategy;

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать юнита\n";
        std::cout << "2. Применить состояние к юниту\n";
        std::cout << "3. Применить стратегию к юниту\n";
        std::cout << "4. Атака юнита\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите опцию: ";

        int choice;
        std::cin >> choice;

        if (choice == 5) break;

        switch (choice) {
        case 1: {
            std::cout << "Выберите тип юнита (1 - Elf, 2 - Orc): ";
            int type;
            std::cin >> type;
            std::cout << "Введите имя юнита: ";
            std::string name;
            std::cin >> name;

            if (type == 1) {
                units.push_back(elfFactory.createUnit(name));
            }
            else if (type == 2) {
                units.push_back(orcFactory.createUnit(name));
            }
            else {
                std::cout << "Неверный тип юнита!\n";
            }
            break;
        }
        case 2: {
            std::cout << "Выберите юнита для изменения состояния:\n";
            for (size_t i = 0; i < units.size(); ++i) {
                std::cout << i << ". " << units[i]->getName() << " (Health: " << units[i]->getHealth() << ")\n";
            }
            size_t unitIndex;
            std::cin >> unitIndex;

            if (unitIndex >= units.size()) {
                std::cout << "Неверный индекс юнита!\n";
                break;
            }

            std::cout << "Выберите состояние (1 - Атака, 2 - Движение): ";
            int stateChoice;
            std::cin >> stateChoice;

            if (stateChoice == 1) {
                attackingState.handle(units[unitIndex].get());
            }
            else if (stateChoice == 2) {
                movingState.handle(units[unitIndex].get());
            }
            else {
                std::cout << "Неверное состояние!\n";
            }
            break;
        }
        case 3: {
            std::cout << "Выберите юнита для применения стратегии:\n";
            for (size_t i = 0; i < units.size(); ++i) {
                std::cout << i << ". " << units[i]->getName() << " (Health: " << units[i]->getHealth() << ")\n";
            }
            size_t unitIndex;
            std::cin >> unitIndex;

            if (unitIndex >= units.size()) {
                std::cout << "Неверный индекс юнита!\n";
                break;
            }

            std::cout << "Выберите стратегию (1 - Агрессивная, 2 - Оборонительная): ";
            int strategyChoice;
            std::cin >> strategyChoice;

            if (strategyChoice == 1) {
                aggressiveStrategy.execute(units[unitIndex].get());
            }
            else if (strategyChoice == 2) {
                defensiveStrategy.execute(units[unitIndex].get());
            }
            else {
                std::cout << "Неверная стратегия!\n";
            }
            break;
        }
        case 4: {
            std::cout << "Выберите атакующего юнита:\n";
            for (size_t i = 0; i < units.size(); ++i) {
                std::cout << i << ". " << units[i]->getName() << " (Health: " << units[i]->getHealth() << ")\n";
            }
            size_t attackerIndex;
            std::cin >> attackerIndex;

            if (attackerIndex >= units.size()) {
                std::cout << "Неверный индекс юнита!\n";
                break;
            }

            std::cout << "Выберите цель для атаки:\n";
            for (size_t i = 0; i < units.size(); ++i) {
                if (i != attackerIndex) {
                    std::cout << i << ". " << units[i]->getName() << " (Health: " << units[i]->getHealth() << ")\n";
                }
            }
            size_t targetIndex;
            std::cin >> targetIndex;

            if (targetIndex >= units.size() || targetIndex == attackerIndex) {
                std::cout << "Неверный индекс цели!\n";
                break;
            }

            units[attackerIndex]->attack(units[targetIndex].get());
            std::cout << units[targetIndex]->getName() << " получил урон! Здоровье: " << units[targetIndex]->getHealth() << "\n";

            if (units[targetIndex]->getHealth() == 0) {
                std::cout << units[targetIndex]->getName() << " убит!\n";
                units.erase(units.begin() + targetIndex);
            }

            break;
        }
        default:
            std::cout << "Неверный выбор!\n";
        }
    }

    return 0;
}
