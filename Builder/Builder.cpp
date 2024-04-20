#include <iostream>
#include <vector>
using namespace std;


// Class BusPassenger 
class BusPassenger
{
private:
    string category;
public:
    void info() {
        cout << "Board Taxi Driver\n" << endl;
    };
    BusPassenger(string category) : category(category) {};
    void getCategory() {
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


// Class TaxiPassenger
class TaxiPassenger
{
private:
    string category;
public:
    void info() {
        cout << "Board Taxi Driver\n" << endl;
    };
    TaxiPassenger(string category) : category(category) {};
    void getCategory() {
        if (category == "Adult")
            std::cout << "Correct category. 10$\n";
        else if (category == "Child") 
            std::cout << "Correct category. 5$\n";
        else
            std::cout << "Incorrect category! Not paid.\n";
    }
};


// Class BusDriver
class BusDriver
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


// Class TaxiDriver
class TaxiDriver
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


// Class Bus
class Bus
{
private:
    BusDriver* driver;
    vector<BusPassenger*> vectorPassenger;
public:
    Bus() : driver(nullptr) {};
    void addDriver(BusDriver* driver) {
        if (this->driver == nullptr) {
            this->driver = driver;
            std::cout << "Driver added\n";
        }
        else
            std::cout << "Driver already added!\n";
    }
    void addPassenger(BusPassenger* passenger) {
        vectorPassenger.push_back(passenger);
        std::cout << "Passenger added\n";
    }
    void isReadyToDepart() {
        if (driver != nullptr && vectorPassenger.size() > 0 && vectorPassenger.size() <= 30)
            cout << "Bus is ready to depart!\n";
        else
            cout << "Bus is not ready to depart!\n";
    }
    ~Bus() {
        delete driver;
        for (auto passenger : vectorPassenger)
            delete passenger;
    }
};

// Class Taxi
class Taxi
{
private:
    TaxiDriver* driver;
    vector<TaxiPassenger*> vectorPassenger;
public:
    Taxi() : driver(nullptr) {};
    void addDriver(TaxiDriver* driver) {
        if (this->driver == nullptr) {
            this->driver = driver;
            std::cout << "Driver added\n";

        }
        else
            std::cout << "Driver already added!\n";
    }
    void addPassenger(TaxiPassenger* passenger) {
        vectorPassenger.push_back(passenger);
        std::cout << "Passenger added\n";
    }
    void isReadyToDepart() {
        if (driver != nullptr && vectorPassenger.size() > 0 && vectorPassenger.size() <= 4)
            cout << "Taxi is ready to depart!\n";
        else
            cout << "Taxi is not ready to depart!\n";
    }
};


// Concrete class TaxiBuilder
class TaxiBuilder
{
private:
    Taxi* taxi;
public:
    TaxiBuilder() : taxi(nullptr) {}
    TaxiDriver* createDriver() {
        return new TaxiDriver(); 
    }
    TaxiPassenger* createPassenger(string category) {
        return new TaxiPassenger(category); 
    };
    Taxi* getVehicle()  {
        if (taxi == nullptr)
            taxi = new Taxi();
        return taxi;
    }
};


// Concrete class BusBuilder
class BusBuilder
{
private:
    Bus* bus;
public:
    BusBuilder() : bus(nullptr) {}
    BusDriver* createDriver() {
        return new BusDriver();
    }
    BusPassenger* createPassenger(string category) {
        return new BusPassenger(category);
    };
    Bus* getVehicle() {
        if (bus == nullptr)
            bus = new Bus();
        return bus;
    }
};


// Class  Director
class Director
{
public:
    Bus* createVehicle(BusBuilder& builder, vector<string> passengerCategories)
    {
        Bus* vehicle = builder.getVehicle();
        BusDriver* driver = builder.createDriver();
        vehicle->addDriver(driver);
        for (auto category : passengerCategories) {
            BusPassenger* passenger = builder.createPassenger(category);
            vehicle->addPassenger(passenger);
        }
        vehicle->isReadyToDepart();
        return vehicle;
    }
    Taxi* createVehicle(TaxiBuilder& builder, vector<string> passengerCategories)
    {
        Taxi* vehicle = builder.getVehicle();
        TaxiDriver* driver = builder.createDriver();
        vehicle->addDriver(driver);
        for (auto category : passengerCategories) {
            TaxiPassenger* passenger = builder.createPassenger(category);
            vehicle->addPassenger(passenger);
        }
        vehicle->isReadyToDepart();
        return vehicle;
    }
};



int main()
{
    Director dir;

    // Build Bus
    std::cout << "Bus:\n";

    BusBuilder bus_builder1;
    vector<string> busPassengerCategories12 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Bus* bus1 = dir.createVehicle(bus_builder1, busPassengerCategories12);

    // Trying add second Driver
    //BusDriver* secondDriver = bus_builder1.createDriver();
    //bus1->addDriver(secondDriver);  

    delete bus1;

    // Build Bus with 36 Passengers
    BusBuilder bus_builder2;
    vector<string> busPassengerCategories36 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Bus* bus2 = dir.createVehicle(bus_builder2, busPassengerCategories36);

    delete bus2;

  
    // Build Taxi
    std::cout << "\nTaxi:\n";

    TaxiBuilder taxi_Builder1;
    vector<string> taxiPassengerCategories4 = { "Adult", "Child", "Child", "Child" };
    Taxi* taxi1 = dir.createVehicle(taxi_Builder1, taxiPassengerCategories4);

    delete taxi1;

    // Build Taxid with 5 Passengers
    TaxiBuilder taxi_Builder2;
    vector<string> taxiPassengerCategories5 = { "Adult", "Child", "Child", "Child", "Adult" };
    Taxi* taxi2 = dir.createVehicle(taxi_Builder2, taxiPassengerCategories5);

    delete taxi2;

    return 0;
}

