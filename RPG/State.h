#pragma once
#ifndef STATE_H
#define STATE_H

#include "Unit.h"

class Unit; // Предварительное объявление

// Абстрактный класс состояния юнита
class UnitState {
public:
    virtual ~UnitState() = default;
    virtual void handle(Unit* unit) = 0;
};

// Конкретное состояние - атака
class AttackingState : public UnitState {
public:
    void handle(Unit* unit) override;
};

// Конкретное состояние - движение
class MovingState : public UnitState {
public:
    void handle(Unit* unit) override;
};

#endif // STATE_H
