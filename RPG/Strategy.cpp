#include "Strategy.h"

// ���������� ������� ���������
void AggressiveStrategy::execute(Unit* unit) {
    std::cout << unit->getName() << " ���������� ����������� ���������!\n";
    // ��������� ����� � �����
    unit->applyAttackBonus(10);
    std::cout << "�����: +10 � �����.\n";
}

void DefensiveStrategy::execute(Unit* unit) {
    std::cout << unit->getName() << " ���������� �������������� ���������!\n";
    // ��������� ����� � ������
    unit->applyDefenseBonus(10);
    std::cout << "�����: +10 � ������.\n";
}
