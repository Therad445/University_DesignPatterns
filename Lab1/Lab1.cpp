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
public:
    virtual void boardDriver() = 0;
    virtual void boardPassengers() = 0;
    virtual ~BoardAnyCar() {}
};

class BoardTaxi : public BoardAnyCar {
public:
    void boardDriver() override {
        Driver* driver = Driver::getInstance();
        // Boarding taxi driver logic
        std::cout << "Taxi driver boarded.\n";
    }

    void boardPassengers() override {
        // Boarding taxi passengers logic
        std::cout << "Passengers boarded taxi.\n";
    }
};

class BoardBus : public BoardAnyCar {
public:
    void boardDriver() override {
        Driver* driver = Driver::getInstance();
        // Boarding bus driver logic
        std::cout << "Bus driver boarded.\n";
    }

    void boardPassengers() override {
        // Boarding bus passengers logic
        std::cout << "Passengers boarded bus.\n";
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

int main() {
    CarBoardFactory* taxiFactory = new TaxiBoardFactory();
    BoardAnyCar* taxiBoard = taxiFactory->createCarBoard();
    taxiBoard->boardDriver();
    taxiBoard->boardPassengers();

    CarBoardFactory* busFactory = new BusBoardFactory();
    BoardAnyCar* busBoard = busFactory->createCarBoard();
    busBoard->boardDriver();
    busBoard->boardPassengers();

    delete taxiFactory;
    delete taxiBoard;
    delete busFactory;
    delete busBoard;

    return 0;
}
