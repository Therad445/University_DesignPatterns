#include <iostream>
#include <vector>

// Singleton pattern implementation for Driver class
class Driver {
private:
    static Driver* instance;
    Driver() {} // Private constructor to prevent instantiation

public:
    static Driver* getInstance() {
        if (!instance) {
            instance = new Driver();
        }
        return instance;
    }
};

Driver* Driver::instance = nullptr;

// Abstract Factory pattern implementation
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
            // Boarding taxi driver logic
            std::cout << "Taxi driver boarded.\n";
            driverBoarded = true;
        } else {
            std::cout << "Taxi already has a driver.\n";
        }
    }

    void boardPassenger() override {
        if (passengerCount < maxPassengerCount) {
            // Boarding taxi passenger logic
            std::cout << "Passenger boarded taxi.\n";
            ++passengerCount;
        } else {
            std::cout << "Taxi is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Taxi is ready to depart.\n";
        } else {
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
            // Boarding bus driver logic
            std::cout << "Bus driver boarded.\n";
            driverBoarded = true;
        } else {
            std::cout << "Bus already has a driver.\n";
        }
    }

    void boardPassenger() override {
        if (passengerCount < maxPassengerCount) {
            // Boarding bus passenger logic
            std::cout << "Passenger boarded bus.\n";
            ++passengerCount;
        } else {
            std::cout << "Bus is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Bus is ready to depart.\n";
        } else {
            std::cout << "Bus is not ready to depart. Board driver and passengers first.\n";
        }
    }
};

// Factory for creating specific car boards
class CarBoardFactory {
public:
    virtual BoardAnyCar* createCarBoard() = 0;
    virtual ~CarBoardFactory() {}
};

class TaxiBoardFactory : public CarBoardFactory {
public:
    BoardAnyCar* createCarBoard() override {
        return new BoardTaxi();
    }
};

class BusBoardFactory : public CarBoardFactory {
public:
    BoardAnyCar* createCarBoard() override {
        return new BoardBus();
    }
};

// Client code
int main() {
    CarBoardFactory* taxiFactory = new TaxiBoardFactory();
    BoardAnyCar* taxiBoard = taxiFactory->createCarBoard();
    taxiBoard->boardDriver();
    taxiBoard->boardPassenger();
    taxiBoard->start();

    CarBoardFactory* busFactory = new BusBoardFactory();
    BoardAnyCar* busBoard = busFactory->createCarBoard();
    busBoard->boardDriver();
    busBoard->boardPassenger();
    busBoard->start();

    // Trying to board more passengers than the limit
    for (int i = 0; i < 30; ++i) {
        busBoard->boardPassenger();
    }
    busBoard->start();

    delete taxiFactory;
    delete taxiBoard;
    delete busFactory;
    delete busBoard;

    return 0;
}
