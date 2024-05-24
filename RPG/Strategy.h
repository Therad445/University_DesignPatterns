#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

#include "Unit.h"

class IStrategy {
public:
    virtual ~IStrategy() = default;
    virtual void execute(Unit* unit) = 0;
};

// ���������� ��������� - �����������
class AggressiveStrategy : public IStrategy {
public:
    void execute(Unit* unit) override;
};

// ���������� ��������� - ��������������
class DefensiveStrategy : public IStrategy {
public:
    void execute(Unit* unit) override;
};

#endif // STRATEGY_H
