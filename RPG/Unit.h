#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <memory>
#include <string>

// ������� ����� �����
class Unit {
protected:
    std::string name;
    int health;
    int attackPower;
    int defensePower;
    int attackBonus;
    int defenseBonus;

public:
    Unit(const std::string& name, int health, int attackPower, int defensePower);
    virtual ~Unit() = default;

    std::string getName() const;
    int getHealth() const;
    void takeDamage(int damage);
    void attack(Unit* target);
    void printInfo() const;
    void applyAttackBonus(int bonus);
    void applyDefenseBonus(int bonus);
    void resetBonuses();
};

// ���������� ����� ����� Elf
class Elf : public Unit {
public:
    Elf(const std::string& name);
};

// ���������� ����� ����� Orc
class Orc : public Unit {
public:
    Orc(const std::string& name);
};

// ����������� ������� ������
class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    virtual std::unique_ptr<Unit> createUnit(const std::string& name) = 0;
};

// ������� ������ Elf
class ElfFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(const std::string& name) override;
};

// ������� ������ Orc
class OrcFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(const std::string& name) override;
};

#endif // UNIT_H
