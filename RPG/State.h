#pragma once
#ifndef STATE_H
#define STATE_H

#include "Unit.h"

class Unit; // ��������������� ����������

// ����������� ����� ��������� �����
class UnitState {
public:
    virtual ~UnitState() = default;
    virtual void handle(Unit* unit) = 0;
};

// ���������� ��������� - �����
class AttackingState : public UnitState {
public:
    void handle(Unit* unit) override;
};

// ���������� ��������� - ��������
class MovingState : public UnitState {
public:
    void handle(Unit* unit) override;
};

#endif // STATE_H
