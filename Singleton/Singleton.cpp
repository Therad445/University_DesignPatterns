#include <iostream>
#include <vector>

class Driver {
private:
    static Driver* instance;
    Driver() {} 

public:
    static Driver* getInstance() {
        if (!instance) {
            instance = new Driver();
        }
        return instance;
    }
};

Driver* Driver::instance = nullptr;

class BoardAnyCar {
protected:
    bool driverBoarded;
    int passengerCount;
    int maxPassengerCount;

public:
    BoardAnyCar(int maxPassCount) : driverBoarded(false), passengerCount(0), maxPassengerCount(maxPassCount) {}

    virtual void boardDriver() = 0;
    virtual void boardPassenger() = 0;
    virtual void start() = 0;
    virtual ~BoardAnyCar() {}
};

class BoardTaxi : public BoardAnyCar {
public:
    BoardTaxi() : BoardAnyCar(4) {}

    void boardDriver() override {
        if (!driverBoarded) {
            Driver* driver = Driver::getInstance();
            std::cout << "Taxi driver boarded.\n";
            driverBoarded = true;
        }
        else {
            std::cout << "Taxi already has a driver.\n";
        }
    }

    void boardPassenger() override {
        if (passengerCount < maxPassengerCount) {
            std::cout << "Passenger boarded taxi.\n";
            ++passengerCount;
        }
        else {
            std::cout << "Taxi is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Taxi is ready to depart.\n";
        }
        else {
            std::cout << "Taxi is not ready to depart. Board driver and passengers first.\n";
        }
    }
};

class BoardBus : public BoardAnyCar {
public:
    BoardBus() : BoardAnyCar(30) {}

    void boardDriver() override {
        if (!driverBoarded) {
            Driver* driver = Driver::getInstance();
            std::cout << "Bus driver boarded.\n";
            driverBoarded = true;
        }
        else {
            std::cout << "Bus already has a driver.\n";
        }
    }

    void boardPassenger() override {
        if (passengerCount < maxPassengerCount) {
            std::cout << "Passenger boarded bus.\n";
            ++passengerCount;
        }
        else {
            std::cout << "Bus is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Bus is ready to depart.\n";
        }
        else {
            std::cout << "Bus is not ready to depart. Board driver and passengers first.\n";
        }
    }
};


int main() {
    BoardAnyCar* taxiBoard = new BoardTaxi();
    taxiBoard->boardDriver();
    taxiBoard->boardPassenger();
    taxiBoard->start();

    BoardAnyCar* busBoard = new BoardBus();
    busBoard->boardDriver();

    for (int i = 0; i < 21; ++i) {
        busBoard->boardPassenger();
    }
    busBoard->start();

    delete taxiBoard;
    delete busBoard;

    return 0;
}