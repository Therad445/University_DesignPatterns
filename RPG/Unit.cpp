#include "Unit.h"

// ���������� ������� Unit
Unit::Unit(const std::string& name, int health, int attackPower, int defensePower)
    : name(name), health(health), attackPower(attackPower), defensePower(defensePower), attackBonus(0), defenseBonus(0) {}

std::string Unit::getName() const {
    return name;
}

int Unit::getHealth() const {
    return health;
}

void Unit::takeDamage(int damage) {
    health -= (damage - defensePower);
    if (health < 0) health = 0;
}

void Unit::attack(Unit* target) {
    target->takeDamage(attackPower + attackBonus);
    std::cout << name << " ����� " << (attackPower + attackBonus) << " �����.\n";
}

void Unit::printInfo() const {
    std::cout << "Unit: " << name << " | Health: " << health << " | Attack: " << attackPower + attackBonus << " | Defense: " << defensePower + defenseBonus << std::endl;
}

void Unit::applyAttackBonus(int bonus) {
    attackBonus += bonus;
}

void Unit::applyDefenseBonus(int bonus) {
    defenseBonus += bonus;
}

void Unit::resetBonuses() {
    attackBonus = 0;
    defenseBonus = 0;
}

//void Unit::move(int newX, int newY, GameMap& gameMap) {
//    if (gameMap.isValidMove(newX, newY)) {
//        gameMap.moveUnit(x, y, newX, newY, name[0]); // ������������� ������ ������ ��� ����������� �����
//        x = newX;
//        y = newY;
//    }
//    else {
//        std::cout << "������������ ���!\n";
//    }
//}


// ���������� ������� Elf
Elf::Elf(const std::string& name) : Unit("Elf: " + name, 100, 15, 5) {}

// ���������� ������� Orc
Orc::Orc(const std::string& name) : Unit("Orc: " + name, 120, 10, 10) {}

// ���������� ������� ElfFactory
std::unique_ptr<Unit> ElfFactory::createUnit(const std::string& name) {
    return std::make_unique<Elf>(name);
}

// ���������� ������� OrcFactory
std::unique_ptr<Unit> OrcFactory::createUnit(const std::string& name) {
    return std::make_unique<Orc>(name);
}
