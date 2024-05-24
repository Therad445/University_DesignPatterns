#include "State.h"

// ���������� ������� ���������
void AttackingState::handle(Unit* unit) {
    std::cout << unit->getName() << " � ��������� �����!\n";
    // ��������� ����� � �����
    unit->applyAttackBonus(5);
    std::cout << "�����: +5 � �����.\n";
}

void MovingState::handle(Unit* unit) {
    std::cout << unit->getName() << " � ��������� ��������!\n";
    unit->applyDefenseBonus(5);
    std::cout << "�����: +5 � ������.\n";
}
