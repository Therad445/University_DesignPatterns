#include <iostream>
#include <vector>
#include <random>

enum class PassengerType {
    Adult,
    Child,
    Discount
};

enum class LicenseType {
    Bus,
    Taxi
};


PassengerType getPassengerTypeFromString(const std::string& typeString) {
    if (typeString == "Adult") {
        return PassengerType::Adult;
    }
    else if (typeString == "Child") {
        return PassengerType::Child;
    }
    else if (typeString == "Discount") {
        return PassengerType::Discount;
    }
    else {
        return PassengerType::Adult;
    }
}

std::string passengerTypeToString(PassengerType type) {
    switch (type) {
    case PassengerType::Adult:
        return "Adult";
    case PassengerType::Child:
        return "Child";
    case PassengerType::Discount:
        return "Discount";
    default:
        return "Unknown";
    }
}


std::vector<PassengerType> generateRandomPassengerTypes(int numPassengers) {
    std::vector<PassengerType> passengerTypes;

    // Инициализируем генератор случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numPassengers; ++i) {
        // Генерируем случайное число в диапазоне от 0 до 2
        int randomIndex = rand() % 3;
        // Преобразуем полученное случайное число в PassengerType и добавляем в вектор
        passengerTypes.push_back(static_cast<PassengerType>(randomIndex));
    }

    return passengerTypes;
}


// Abstract class Passenger

class Passenger
{
public:
    virtual void info() = 0;
    virtual void getCategory() = 0;
    virtual ~Passenger() = default;
};
    
// Concrete class BusPassenger 
class BusPassenger : public Passenger
{
private:
    PassengerType type;
public:
    BusPassenger(PassengerType type) : type(type) {}
    void info() override {
        std::cout << "Board Bus Driver\n" << std::endl;
    };
    void getCategory() override {
        switch (type) {
        case PassengerType::Adult:
            std::cout << "Correct category: " << passengerTypeToString(type) << " 3$\n";
            break;
        case PassengerType::Child:
            std::cout << "Correct category: " << passengerTypeToString(type) << " 2$\n";
            break;
        case PassengerType::Discount:
            std::cout << "Correct category: " << passengerTypeToString(type) << " 1$\n";
            break;
        default:
            std::cout << "Incorrect category! Not paid.\n";
            break;
        }
    }
};



// Concrete class TaxiPassenger
class TaxiPassenger : public Passenger
{
private:
    PassengerType type;
public:
    TaxiPassenger(PassengerType type) : type(type) {}
    void info() override {
        std::cout << "Board Taxi Driver\n" << std::endl;
    };
    void getCategory() override {
        switch (type) {
        case PassengerType::Adult:
            std::cout << "Correct category: " << passengerTypeToString(type) << " 10$\n";
            break;
        case PassengerType::Child:
            std::cout << "Correct category: " << passengerTypeToString(type) << " 5$\n";
            break;
        default:
            std::cout << "Incorrect category! Not paid.\n";
            break;
        }
    }
};


// Abstract class Driver
class Driver
{
public:
    virtual void info() = 0;
    virtual std::string getLicense() = 0;
    virtual ~Driver() = default;
};

// Concrete class BusDriver
class BusDriver : public Driver
{
private:
    std::string license = "D";
public:
    void info() override {
        std::cout << "Bus Driver\n" << std::endl;
    }
    std::string getLicense() override {
        return license;
    }
};


// Concrete class TaxiDriver
class TaxiDriver : public Driver
{
private:
    std::string license = "D";
public:
    void info() override {
        std::cout << "Taxi Driver\n" << std::endl;
    }
    std::string getLicense() override {
        return license;
    }
};


// Abstract class Vehicle
class Vehicle
{
protected:
    Driver* driver;
    std::vector<Passenger*> passengers;
public:
    Vehicle() : driver(nullptr) {}
    virtual void isReadyToDepart() = 0;
    virtual ~Vehicle() {
        delete driver;
        for (auto passenger : passengers)
            delete passenger;
    }
    void addDriver(Driver* driver) {
        if (this->driver == nullptr) {
            this->driver = driver;
            std::cout << "Driver added\n";
        }
        else
            std::cout << "Driver already added!\n";
    }
    void addPassenger(Passenger* passenger) {
        passengers.push_back(passenger);
        passenger->getCategory();
        std::cout << "Passenger added\n";
    }
};


// Abstracxt class Bus
class Bus : public Vehicle
{
public:
    void isReadyToDepart() override {
        if (driver != nullptr && passengers.size() > 0 && passengers.size() <= 30)
            std::cout << "Bus is ready to depart!\n";
        else
            std::cout << "Bus is not ready to depart!\n";
    }
};

// Abstracxt class Taxi
class Taxi: public Vehicle
{
public:
    void isReadyToDepart() override {
        if (driver != nullptr && passengers.size() > 0 && passengers.size() <= 4)
            std::cout << "Taxi is ready to depart!\n";
        else
            std::cout << "Taxi is not ready to depart!\n";
    }
};


// Abstract class Builder
class Builder
{
public:
    virtual void buildDriver() = 0;
    virtual void buildPassenger(PassengerType type) = 0;
    virtual Vehicle* getVehicle() = 0;
    virtual ~Builder() = default;
};

// Concrete class TaxiBuilder
class TaxiBuilder: public Builder
{
private:
    Taxi* taxi;
public:
    TaxiBuilder() : taxi(nullptr) {}
    //Driver* buildDriver() override {
    void buildDriver() override {
        if (taxi == nullptr) {
            taxi = new Taxi();
        }
        taxi->addDriver(new TaxiDriver());
    }
    //Passenger* buildPassenger(std::string category) override {
    void buildPassenger(PassengerType type) override {
        if (taxi == nullptr) {
            taxi = new Taxi();
        }
        taxi->addPassenger(new TaxiPassenger(type));
    };
    Vehicle* getVehicle() override {
        if (taxi == nullptr)
            taxi = new Taxi();
        return taxi;
    }
};


// Concrete class BusBuilder
class BusBuilder: public Builder
{
private:
    Bus* bus;
public:
    BusBuilder() : bus(nullptr) {}
    //Driver* buildDriver() override {
    void buildDriver() override {
        if (bus == nullptr) {
            bus = new Bus();
        }
        bus->addDriver(new BusDriver());
    }
    //Passenger* buildPassenger(std::string category) override {
    void buildPassenger(PassengerType type) override {
        if (bus == nullptr) {
            bus = new Bus();
        }
        bus->addPassenger(new BusPassenger(type));
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
    Vehicle* makeVehicle(Builder& builder, std::vector<PassengerType> passengerCategories)
    {
        //Vehicle* vehicle = builder.getVehicle();
        // Create.childseat
        builder.buildDriver();
        //vehicle->addDriver(driver); // Убрать в Builder
        for (const auto& type : passengerCategories) {
            //Passenger* passenger = builder.buildPassenger(category);
            //vehicle->addPassenger(passenger); // Убрать в Builder
            builder.buildPassenger(type);
        }
        Vehicle* vehicle = builder.getVehicle();
        vehicle->isReadyToDepart();
       
        return vehicle;
    }
};


int main()
{
    Director dir;

    // Build Bus
    std::cout << "Bus:\n";
    BusBuilder busBuilder;

    //std::vector<PassengerType> busPassengerCategories12 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    std::vector<PassengerType> busPassengerTypes12 = generateRandomPassengerTypes(12);
    Vehicle* bus = dir.makeVehicle(busBuilder, busPassengerTypes12);

    // Trying add second Driver
    //BusDriver* secondDriver = bus_builder1.buildDriver();
    //bus1->addDriver(secondDriver);  

    delete bus;

    BusBuilder busBuilder36;
    // Build Bus with 36 Passengers
    //std::vector<PassengerType> busPassengerCategories36 = { "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child", "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    std::vector<PassengerType> busPassengerTypes36 = generateRandomPassengerTypes(12);
    Vehicle* bus36 = dir.makeVehicle(busBuilder36, busPassengerTypes36);

    delete bus36;

  
    // Build Taxi
    std::cout << "\nTaxi:\n";

    TaxiBuilder taxiBuilder;
    //std::vector<PassengerType> taxiPassengerCategories4 = { "Adult", "Child", "Child", "Child" };
    std::vector<PassengerType> taxiPassengerTypes4 = generateRandomPassengerTypes(12);
    Vehicle* taxi = dir.makeVehicle(taxiBuilder, taxiPassengerTypes4);
    delete taxi;

    // Build Taxid with 5 Passengers
    TaxiBuilder taxiBuilder5;
    //std::vector<PassengerType> taxiPassengerCategories5 = { "Adult", "Child", "Child", "Child", "Adult" };
    std::vector<PassengerType> taxiPassengerTypes5 = generateRandomPassengerTypes(12);
    Vehicle* taxi5 = dir.makeVehicle(taxiBuilder5, taxiPassengerTypes5);

    delete taxi5;

    return 0;
}

//  Добавить абстраактный Vehichle, Builder, 