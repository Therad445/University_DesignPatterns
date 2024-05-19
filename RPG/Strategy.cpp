#include "Strategy.h"

// Реализация методов стратегий
void AggressiveStrategy::execute(Unit* unit) {
    std::cout << unit->getName() << " использует агрессивную стратегию!\n";
    // Применяем бонус к урону
    unit->applyAttackBonus(10);
    std::cout << "Бонус: +10 к атаке.\n";
}

void DefensiveStrategy::execute(Unit* unit) {
    std::cout << unit->getName() << " использует оборонительную стратегию!\n";
    // Применяем бонус к защите
    unit->applyDefenseBonus(10);
    std::cout << "Бонус: +10 к защите.\n";
}
