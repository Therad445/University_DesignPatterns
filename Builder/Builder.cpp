#include <iostream>
#include <vector>
using namespace std;



// Abstract class Passenger
class Passenger
{
public:
    void info() {
        cout << "Board Taxi Driver\n" << endl;
    };
    virtual void getCategory() = 0;
    virtual ~Passenger() {};
};

// Concrete class BusPassenger 
class BusPassenger : public Passenger
{
private:
    string category;
public:
    BusPassenger(string category) : category(category) {};
    void getCategory() override {
        if (category == "Adult")
            std::cout << "Correct category. 3$\n";
        else if (category == "Child") 
            std::cout << "Correct category. 2$\n";
        else if (category == "Discount")
            std::cout << "Correct category. 1$\n";
        else
            std::cout << "Incorrect category! Not paid.\n";
    }
};


// Concrete class TaxiPassenger
class TaxiPassenger : public Passenger
{
private:
    string category;
public:
    TaxiPassenger(string category) : category(category) {};
    void getCategory() override {
        if (category == "Adult")
            std::cout << "Correct category. 10$\n";
        else if (category == "Child") 
            std::cout << "Correct category. 5$\n";
        else
            std::cout << "Incorrect category! Not paid.\n";
    }
};


// Abstract class Driver
class Driver
{
public:
    virtual void info() = 0;
    virtual string getLicense() = 0;
    virtual ~Driver() {};
};


// Concrete class BusDriver
class BusDriver : public Driver
{
private:
    string license = "D";
public:
    void info() {
        cout << "Board Bus Driver\n" << endl;
    }
    string getLicense() {
        return license;
    }
};


// Concrete class TaxiDriver
class TaxiDriver : public Driver
{
private:
    string license = "D";
public:
    void info() {
        cout << "Board Taxi Driver\n" << endl;
    }
    string getLicense() {
        return license;
    }
};

// Abstract class Vehicle
class Vehicle
{
protected:
    Driver* driver;
    vector<Passenger*> vectorPassenger;
public:
    virtual void addDriver(Driver* driver) = 0;
    virtual void addPassenger(Passenger* passenger) = 0;
    virtual void isReadyToDepart() = 0;
    virtual ~Vehicle() {
        delete driver;
        for (auto passenger : vectorPassenger)
            delete passenger;
    }
};

// Concrete class Bus
class Bus : public Vehicle
{
private:
    Driver* driver;
    vector<Passenger*> vectorPassenger;
public:
    Bus() : driver(nullptr) {};
    void addDriver(Driver* driver) override {
        if (this->driver == nullptr) {
            this->driver = driver;
            std::cout << "Driver added\n";
        }
        else
            std::cout << "Driver already added!\n";
    }
    void addPassenger(Passenger* passenger) override {
        vectorPassenger.push_back(passenger);
        std::cout << "Passenger added\n";
    }
    void isReadyToDepart() override {
        if (driver != nullptr && vectorPassenger.size() > 0 && vectorPassenger.size() <= 30)
            cout << "Bus is ready to depart!\n";
        else
            cout << "Bus is not ready to depart!\n";
    }
};

// Concrete class Taxi
class Taxi : public Vehicle
{
private:
    Driver* driver;
    vector<Passenger*> vectorPassenger;
public:
    Taxi() : driver(nullptr) {};
    void addDriver(Driver* driver) override {
        if (this->driver == nullptr) {
            this->driver = driver;
            std::cout << "Driver added\n";

        }
        else
            std::cout << "Driver already added!\n";
    }
    void addPassenger(Passenger* passenger) override {
        vectorPassenger.push_back(passenger);
        std::cout << "Passenger added\n";
    }
    void isReadyToDepart() override {
        if (driver != nullptr && vectorPassenger.size() > 0 && vectorPassenger.size() <= 4)
            cout << "Taxi is ready to depart!\n";
        else
            cout << "Taxi is not ready to depart!\n";
    }
};


// Abstract class VehicleBuilder 
class VehicleBuilder
{
public:
    //virtual void createUnits() {};
    virtual Driver* createDriver() = 0;
    virtual Passenger* createPassenger(string category) = 0;
    virtual Vehicle* getVehicle() = 0;
    virtual ~VehicleBuilder() {};
};


// Concrete class TaxiBuilder
class TaxiBuilder : public VehicleBuilder
{
private:
    Taxi* taxi;
public:
    TaxiBuilder() : taxi(nullptr) {}
    Driver* createDriver() override { 
        return new TaxiDriver(); 
    }
    Passenger* createPassenger(string category) override { 
        return new TaxiPassenger(category); 
    };
    Vehicle* getVehicle() override {
        if (taxi == nullptr)
            taxi = new Taxi();
        return taxi;
    }
};


// Concrete class BusBuilder
class BusBuilder : public VehicleBuilder
{
private:
    Bus* bus;
public:
    BusBuilder() : bus(nullptr) {}
    Driver* createDriver() override {
        return new BusDriver();
    }
    Passenger* createPassenger(string category) override {
        return new BusPassenger(category);
    };
    Vehicle* getVehicle() override {
        if (bus == nullptr)
            bus = new Bus();
        return bus;
    }
};


// Class  Director
class Director
{
public:
    Vehicle* createVehicle(VehicleBuilder& builder, vector<string> passengerCategories)
    {
        Vehicle* vehicle = builder.getVehicle();
        Driver* driver = builder.createDriver();
        vehicle->addDriver(driver);
        for (auto category : passengerCategories) {
            Passenger* passenger = builder.createPassenger(category);
            vehicle->addPassenger(passenger);
        }
        return vehicle;
    }
};



int main()
{
    Director dir;

    // Create Bus
    std::cout << "Bus:\n";

    BusBuilder bus_builder1;
    vector<string> busPassengerCategories12 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Vehicle* bus1 = dir.createVehicle(bus_builder1, busPassengerCategories12);
    bus1->isReadyToDepart();

    // Trying add second Driver
    Driver* secondDriver = bus_builder1.createDriver();
    bus1->addDriver(secondDriver);  

    delete bus1;

    // Trying add 36 Passengers
    BusBuilder bus_builder2;
    vector<string> busPassengerCategories36 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Vehicle* bus2 = dir.createVehicle(bus_builder2, busPassengerCategories36);
    bus2->isReadyToDepart();

    delete bus2;

  
    // Create Taxi
    std::cout << "\nTaxi:\n";

    TaxiBuilder taxi_Builder1;
    vector<string> taxiPassengerCategories4 = { "Adult", "Child", "Child", "Child" };
    Vehicle* taxi1 = dir.createVehicle(taxi_Builder1, taxiPassengerCategories4);
    taxi1->isReadyToDepart();

    delete taxi1;

    // Trying add 5 Passengers
    TaxiBuilder taxi_Builder2;
    vector<string> taxiPassengerCategories5 = { "Adult", "Child", "Child", "Child", "Adult" };
    Vehicle* taxi2 = dir.createVehicle(taxi_Builder2, taxiPassengerCategories5);
    taxi2->isReadyToDepart();

    delete taxi2;

    return 0;
}

