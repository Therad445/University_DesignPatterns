#include "State.h"

// Реализация методов состояний
void AttackingState::handle(Unit* unit) {
    std::cout << unit->getName() << " в состоянии атаки!\n";
    // Применяем бонус к урону
    unit->applyAttackBonus(5);
    std::cout << "Бонус: +5 к атаке.\n";
}

void MovingState::handle(Unit* unit) {
    std::cout << unit->getName() << " в состоянии движения!\n";
    unit->applyDefenseBonus(5);
    std::cout << "Бонус: +5 к защите.\n";
}
