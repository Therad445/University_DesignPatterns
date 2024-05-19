#pragma once
#ifndef STRATEGY_H
#define STRATEGY_H

#include "Unit.h"

class IStrategy {
public:
    virtual ~IStrategy() = default;
    virtual void execute(Unit* unit) = 0;
};

// Конкретная стратегия - агрессивная
class AggressiveStrategy : public IStrategy {
public:
    void execute(Unit* unit) override;
};

// Конкретная стратегия - оборонительная
class DefensiveStrategy : public IStrategy {
public:
    void execute(Unit* unit) override;
};

#endif // STRATEGY_H
