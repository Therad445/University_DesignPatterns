#include <iostream>
#include <vector>
#include <string>

// Абстрактный класс наблюдателя (Observer)
class Observer {
public:
    virtual void update(bool reportCreated) = 0;
};

// Абстрактный класс предмета (Subject)
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// Конкретный класс предмета (ConcreteSubject)
class Department : public Subject {
private:
    std::vector<Observer*> observers;
    bool isReportCreated;

public:
    Department() : isReportCreated(false) {}

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(isReportCreated);
        }
    }

    void createReport() {
        isReportCreated = true;
        notify();
    }

    bool isReportAvailable() {
        return isReportCreated;
    }
};

// Конкретный класс наблюдателя (ConcreteObserver)
class Faculty : public Observer {
private:
    std::string name;

public:
    Faculty(const std::string& name) : name(name) {}

    void update(bool reportCreated) override {
        if (!reportCreated) {
            std::cout << "Department has not created the report yet. Faculty: " << name << " should be notified.\n";
        }
        else {
            std::cout << "Report is available. Faculty: " << name << " can access the report.\n";
        }
    }
};

int main() {
    // Создаем деканат (предмет)
    Department department;

    // Создаем факультеты (наблюдателей)
    Faculty faculty1("Faculty of Computer Science");
    Faculty faculty2("Faculty of Mathematics");

    // Подписываем факультеты на уведомления от деканата
    department.attach(&faculty1);
    department.attach(&faculty2);

    // Преподаватель создает отчет
    department.createReport();

    // Преподаватель не создал отчет вовремя
     department.createReport();

    // Преподаватель создает отчет снова
    // department.createReport();

    return 0;
}

//------------------------       ---------------------- -
//| Subject         |     |        Observer |
//------------------------       ---------------------- -
//|                        |     |                       |
//------------------------       ---------------------- -
//| +attach(observer: Observer*) | | +update(reportCreated: bool) |
//| +detach(observer: Observer*) | |
//| +notify()             |     |                       |
//------------------------       ---------------------- -
//|                           |
//|                           |
//------------------                |
//|   Department    |               |
//------------------                |
//| -observers: vector<Observer*>  |
//| -isReportCreated : bool |
//------------------                |
//| +createReport()                |
//| +isReportAvailable() : bool |
//------------------ |


// Добавить реализацию невовромя сдачи отчёта, добавить в UML факультеты