#include <iostream>
#include <vector>

// Component
class Passenger {
protected:
    int baggageWeight;

public:
    virtual int getBaggageWeight() const = 0;
    virtual void checkBaggage() const = 0;
    virtual ~Passenger() {}
};

// Leaf
class Pilot : public Passenger {
public:
    int getBaggageWeight() const override {
        return 0;
    }

    void checkBaggage() const override {
        std::cout << "Pilots do not have baggage.\n";
    }
};

// Leaf
class Stewardess : public Passenger {
public:
    int getBaggageWeight() const override {
        return 0;
    }

    void checkBaggage() const override {
        std::cout << "Stewardesses do not have baggage.\n";
    }
};

// Composite
class FlightClass : public Passenger {
protected:
    std::vector<Passenger*> passengers;
    int maxPassengers;
    int baggageLimit;

public:
    FlightClass(int maxPass, int bagLimit) : maxPassengers(maxPass), baggageLimit(bagLimit) {}

    int getBaggageWeight() const override {
        int totalWeight = 0;
        for (const auto& passenger : passengers) {
            totalWeight += passenger->getBaggageWeight();
        }
        return totalWeight;
    }

    void checkBaggage() const override {
        std::cout << "Checking baggage for " << passengers.size() << " passengers.\n";
        int totalWeight = getBaggageWeight();
        if (totalWeight > baggageLimit) {
            std::cout << "Excess baggage detected. Removing baggage from flight.\n";
            // Logic to remove baggage from flight
        }
    }

    void addPassenger(Passenger* passenger) {
        if (passengers.size() < maxPassengers) {
            passengers.push_back(passenger);
        } else {
            std::cout << "Flight class is full. Cannot add more passengers.\n";
        }
    }

    virtual ~FlightClass() {
        for (auto p : passengers) {
            delete p;
        }
    }
};

// Concrete Composite
class FirstClass : public FlightClass {
public:
    FirstClass() : FlightClass(10, INT_MAX) {}
};

// Concrete Composite
class BusinessClass : public FlightClass {
public:
    BusinessClass() : FlightClass(20, 35) {}
};

// Concrete Composite
class EconomyClass : public FlightClass {
public:
    EconomyClass() : FlightClass(150, 20) {}
};

// Client
int main() {
    Pilot* pilot1 = new Pilot();
    Pilot* pilot2 = new Pilot();
    Stewardess* stewardess1 = new Stewardess();
    Stewardess* stewardess2 = new Stewardess();
    FirstClass* firstClass = new FirstClass();
    BusinessClass* businessClass = new BusinessClass();
    EconomyClass* economyClass = new EconomyClass();

    firstClass->addPassenger(new Passenger());
    firstClass->addPassenger(new Passenger());
    // Add more passengers as needed

    businessClass->addPassenger(new Passenger());
    businessClass->addPassenger(new Passenger());
    // Add more passengers as needed

    economyClass->addPassenger(new Passenger());
    economyClass->addPassenger(new Passenger());
    // Add more passengers as needed

    std::vector<FlightClass*> flightClasses = {firstClass, businessClass, economyClass};

    for (auto flightClass : flightClasses) {
        flightClass->checkBaggage();
    }

    // Clean up
    delete pilot1;
    delete pilot2;
    delete stewardess1;
    delete stewardess2;
    delete firstClass;
    delete businessClass;
    delete economyClass;

    return 0;
}
