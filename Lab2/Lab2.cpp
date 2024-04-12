#include <iostream>
#include <vector>

// Passenger class with different categories
class Passenger {
public:
    enum class Category { Adult, Concession, Child };
    Category category;
    double fare;

    Passenger(Category cat, double f) : category(cat), fare(f) {}
};

// Car interface
class Car {
public:
    virtual void boardDriver() = 0;
    virtual void boardPassenger(Passenger passenger) = 0;
    virtual void start() = 0;
    virtual ~Car() {}
};

// Builder interface
class CarBuilder {
public:
    virtual void buildDriver() = 0;
    virtual void buildPassenger(Passenger passenger) = 0;
    virtual void buildChildSeat(bool hasChildSeat) = 0;
    virtual Car* getResult() = 0;
    virtual ~CarBuilder() {}
};

// Concrete builder for Bus
class BusBuilder : public CarBuilder {
private:
    std::vector<Passenger> passengers;
    bool hasDriver;
    bool hasChildSeat;

public:
    BusBuilder() : hasDriver(false), hasChildSeat(false) {}

    void buildDriver() override {
        hasDriver = true;
        std::cout << "Bus driver boarded.\n";
    }

    void buildPassenger(Passenger passenger) override {
        if (passengers.size() < 30) {
            passengers.push_back(passenger);
            std::cout << "Passenger boarded bus.\n";
        } else {
            std::cout << "Bus is full. Cannot board more passengers.\n";
        }
    }

    void buildChildSeat(bool hasSeat) override {
        hasChildSeat = hasSeat;
        if (hasSeat) {
            std::cout << "Child seat installed in the bus.\n";
        }
    }

    Car* getResult() override {
        // Construct and return Bus object
        return new Bus(passengers, hasDriver, hasChildSeat);
    }
};

// Concrete builder for Taxi
class TaxiBuilder : public CarBuilder {
private:
    std::vector<Passenger> passengers;
    bool hasDriver;
    bool hasChildSeat;

public:
    TaxiBuilder() : hasDriver(false), hasChildSeat(false) {}

    void buildDriver() override {
        hasDriver = true;
        std::cout << "Taxi driver boarded.\n";
    }

    void buildPassenger(Passenger passenger) override {
        if (passengers.size() < 4) {
            passengers.push_back(passenger);
            std::cout << "Passenger boarded taxi.\n";
        } else {
            std::cout << "Taxi is full. Cannot board more passengers.\n";
        }
    }

    void buildChildSeat(bool hasSeat) override {
        hasChildSeat = hasSeat;
        if (hasSeat) {
            std::cout << "Child seat installed in the taxi.\n";
        }
    }

    Car* getResult() override {
        // Construct and return Taxi object
        return new Taxi(passengers, hasDriver, hasChildSeat);
    }
};

// Director class
class CarDirector {
public:
    Car* construct(CarBuilder& builder, std::vector<Passenger> passengers, bool hasChildSeat = false) {
        builder.buildDriver();
        for (const auto& passenger : passengers) {
            builder.buildPassenger(passenger);
        }
        builder.buildChildSeat(hasChildSeat);
        return builder.getResult();
    }
};

// Concrete implementation of Bus
class Bus : public Car {
private:
    std::vector<Passenger> passengers;
    bool hasDriver;
    bool hasChildSeat;

public:
    Bus(std::vector<Passenger> pass, bool driver, bool childSeat)
        : passengers(pass), hasDriver(driver), hasChildSeat(childSeat) {}

    void boardDriver() override {
        if (!hasDriver) {
            std::cout << "Bus driver boarded.\n";
            hasDriver = true;
        } else {
            std::cout << "Bus already has a driver.\n";
        }
    }

    void boardPassenger(Passenger passenger) override {
        if (passengers.size() < 30) {
            passengers.push_back(passenger);
            std::cout << "Passenger boarded bus.\n";
        } else {
            std::cout << "Bus is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (hasDriver && passengers.size() > 0) {
            std::cout << "Bus is ready to depart.\n";
        } else {
            std::cout << "Bus is not ready to depart. Board driver and passengers first.\n";
        }
    }
};

// Concrete implementation of Taxi
class Taxi : public Car {
private:
    std::vector<Passenger> passengers;
    bool hasDriver;
    bool hasChildSeat;

public:
    Taxi(std::vector<Passenger> pass, bool driver, bool childSeat)
        : passengers(pass), hasDriver(driver), hasChildSeat(childSeat) {}

    void boardDriver() override {
        if (!hasDriver) {
            std::cout << "Taxi driver boarded.\n";
            hasDriver = true;
        } else {
            std::cout << "Taxi already has a driver.\n";
        }
    }

    void boardPassenger(Passenger passenger) override {
        if (passengers.size() < 4) {
            passengers.push_back(passenger);
            std::cout << "Passenger boarded taxi.\n";
        } else {
            std::cout << "Taxi is full. Cannot board more passengers.\n";
        }
    }

    void start() override {
        if (hasDriver && passengers.size() > 0) {
            std::cout << "Taxi is ready to depart.\n";
        } else {
            std::cout << "Taxi is not ready to depart. Board driver first.\n";
        }
    }
};

// Client code
int main() {
    CarDirector director;

    // Building Bus
    BusBuilder busBuilder;
    std::vector<Passenger> busPassengers = {
        Passenger(Passenger::Category::Adult, 10.0),
        Passenger(Passenger::Category::Concession, 5.0),
        Passenger(Passenger::Category::Child, 3.0)
    };
    Car* bus = director.construct(busBuilder, busPassengers, true);
    bus->start();

    // Building Taxi
    TaxiBuilder taxiBuilder;
    Passenger taxiPassenger(Passenger::Category::Adult, 15.0);
    Car* taxi = director.construct(taxiBuilder, {taxiPassenger}, true);
    taxi->start();

    delete bus;
    delete taxi;

    return 0;
}
