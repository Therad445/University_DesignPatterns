#include <iostream>
#include <string>
#include <vector>

// Passenger class
class Passenger {
public:
    virtual std::string getType() const = 0;
    virtual ~Passenger() {}
};

class AdultPassenger : public Passenger {
public:
    std::string getType() const override {
        return "Adult";
    }
};

class ChildPassenger : public Passenger {
public:
    std::string getType() const override {
        return "Child";
    }
};

class ConcessionaryPassenger : public Passenger {
public:
    std::string getType() const override {
        return "Concessionary";
    }
};

// Car class
class Car {
protected:
    std::vector<Passenger*> passengers;

public:
    void addPassenger(Passenger* passenger) {
        passengers.push_back(passenger);
    }

    virtual void loadPassengers() = 0;
    virtual void readyToDepart() = 0;
    virtual ~Car() {
        for (auto p : passengers) {
            delete p;
        }
    }
};

// Taxi class
class Taxi : public Car {
public:
    void loadPassengers() override {
        if (passengers.size() != 4) {
            std::cout << "Taxi must have exactly 4 passengers.\n";
        } else {
            std::cout << "Taxi loaded with passengers.\n";
        }
    }

    void readyToDepart() override {
        if (passengers.size() == 4) {
            std::cout << "Taxi ready to depart.\n";
        } else {
            std::cout << "Taxi cannot depart without 4 passengers.\n";
        }
    }
};

// Bus class
class Bus : public Car {
public:
    void loadPassengers() override {
        int totalPassengers = passengers.size();
        if (totalPassengers <= 30) {
            std::cout << "Bus loaded with passengers.\n";
        } else {
            std::cout << "Bus overloaded! It cannot accommodate more passengers.\n";
        }
    }

    void readyToDepart() override {
        int totalPassengers = passengers.size();
        if (totalPassengers > 0) {
            std::cout << "Bus ready to depart.\n";
        } else {
            std::cout << "Bus cannot depart without any passengers.\n";
        }
    }
};

// Director class
class CarDirector {
public:
    Car* buildCar() {
        Car* car = createCar();
        car->loadPassengers();
        car->readyToDepart();
        return car;
    }

    virtual Car* createCar() = 0;
    virtual ~CarDirector() {}
};

// TaxiBuilder class
class TaxiBuilder : public CarDirector {
public:
    Car* createCar() override {
        Taxi* taxi = new Taxi();
        taxi->addPassenger(new AdultPassenger());
        taxi->addPassenger(new AdultPassenger());
        taxi->addPassenger(new ChildPassenger());
        taxi->addPassenger(new ChildPassenger());
        return taxi;
    }
};

// BusBuilder class
class BusBuilder : public CarDirector {
public:
    Car* createCar() override {
        Bus* bus = new Bus();
        for (int i = 0; i < 31; ++i) {
            if (i % 3 == 0) {
                bus->addPassenger(new AdultPassenger());
            } else if (i % 3 == 1) {
                bus->addPassenger(new ChildPassenger());
            } else {
                bus->addPassenger(new ConcessionaryPassenger());
            }
        }
        return bus;
    }
};

int main() {
    CarDirector* taxiDirector = new TaxiBuilder();
    Car* taxi = taxiDirector->buildCar();

    CarDirector* busDirector = new BusBuilder();
    Car* bus = busDirector->buildCar();

    delete taxiDirector;
    delete taxi;
    delete busDirector;
    delete bus;

    return 0;
}
