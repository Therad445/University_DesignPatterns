
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Абстрактный класс Водитель
class Driver {
public:
    virtual bool hasRequiredLicense() = 0;
    virtual ~Driver() {}
};

// Абстрактный класс Пассажир
class Passenger {
public:
    virtual int getTicketPrice() = 0;
    virtual ~Passenger() {}
};

// Конкретный класс Водитель для автобуса
class BusDriver : public Driver {
public:
    bool hasRequiredLicense() override {
        // Проверка наличия необходимых прав для водителя автобуса
        return true; // Предположим, что у всех водителей автобусов есть необходимые права
    }
};

// Конкретный класс Водитель для такси
class TaxiDriver : public Driver {
public:
    bool hasRequiredLicense() override {
        // Проверка наличия необходимых прав для водителя такси
        return true; // Предположим, что у всех водителей такси есть необходимые права
    }
};

// Конкретный класс Пассажир для автобуса
class BusPassenger : public Passenger {
private:
    string category; // Категория пассажира: "Adult", "Child" или "Discount"
public:
    BusPassenger(string category) : category(category) {}
    int getTicketPrice() override {
        if (category == "Adult")
            return 3;
        else if (category == "Child")
            return 2;
        else if (category == "Discount")
            return 1;
        else
            return 0; // В случае некорректной категории вернуть 0
    }
};

// Конкретный класс Пассажир для такси
class TaxiPassenger : public Passenger {
private:
    string category; // Категория пассажира: "Adult" или "Child"
public:
    TaxiPassenger(string category) : category(category) {}
    int getTicketPrice() override {
        if (category == "Adult")
            return 10;
        else if (category == "Child")
            return 5;
        else
            return 0; // В случае некорректной категории вернуть 0
    }
};

// Абстрактный класс Транспортное средство
class Vehicle {
protected:
    Driver* driver;
    vector<Passenger*> passengers;
public:
    virtual void addDriver(Driver* driver) = 0;
    virtual void addPassenger(Passenger* passenger) = 0;
    virtual bool isReadyToDepart() = 0;
    virtual ~Vehicle() {
        delete driver;
        for (auto passenger : passengers)
            delete passenger;
    }
};

// Конкретный класс Автобус
class Bus : public Vehicle {
private:
    Driver* driver;
public:
    Bus() : driver(nullptr) {}
    void addDriver(Driver* driver) override {
        if (this->driver == nullptr)
            this->driver = driver;
    }
    void addPassenger(Passenger* passenger) override {
        passengers.push_back(passenger);
    }
    bool isReadyToDepart() override {
        return driver != nullptr && passengers.size() > 0 && passengers.size() <= 30; // Предположим, что лимит загрузки автобуса - 30 пассажиров
    }
};

// Конкретный класс Такси
class Taxi : public Vehicle {
private:
    Driver* driver;
public:
    Taxi() : driver(nullptr) {}
    void addDriver(Driver* driver) override {
        if (this->driver == nullptr)
            this->driver = driver;
    }
    void addPassenger(Passenger* passenger) override {
        passengers.push_back(passenger);
    }
    bool isReadyToDepart() override {
        return driver != nullptr && passengers.size() > 0 && passengers.size() <= 4; // Предположим, что лимит загрузки такси - 4 пассажира
    }
};


// Абстрактный класс Строитель транспортного средства
class VehicleBuilder {
public:
    virtual Driver* createDriver() = 0;
    virtual Passenger* createPassenger(string category) = 0;
    virtual Vehicle* getVehicle() = 0;
    virtual ~VehicleBuilder() {}
};

// Конкретный класс Строитель для автобуса
class BusBuilder : public VehicleBuilder {
private:
    Bus* bus;
public:
    BusBuilder() : bus(nullptr) {}
    Driver* createDriver() override {
        return new BusDriver();
    }
    Passenger* createPassenger(string category) override {
        return new BusPassenger(category);
    }
    Vehicle* getVehicle() override {
        if (bus == nullptr)
            bus = new Bus();
        return bus;
    }
};

// Конкретный класс Строитель для такси
class TaxiBuilder : public VehicleBuilder {
private:
    Taxi* taxi;
public:
    TaxiBuilder() : taxi(nullptr) {}
    Driver* createDriver() override {
        return new TaxiDriver();
    }
    Passenger* createPassenger(string category) override {
        return new TaxiPassenger(category);
    }
    Vehicle* getVehicle() override {
        if (taxi == nullptr)
            taxi = new Taxi();
        return taxi;
    }
    
};


// Класс Директор
class Director {
public:
    Vehicle* createVehicle(VehicleBuilder& builder, vector<string> passengerCategories) {
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

int main() {
    Director dir;

    // Создаем автобус
    BusBuilder busBuilder;
    vector<string> busPassengerCategories = { "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Vehicle* bus = dir.createVehicle(busBuilder, busPassengerCategories);
    if (bus->isReadyToDepart())
        cout << "Bus is ready to depart!" << endl;
    else
        cout << "Bus is not ready to depart!" << endl;

    delete bus;

    // Создаем такси
    TaxiBuilder taxiBuilder;
    vector<string> taxiPassengerCategories = { "Adult", "Child", "Child", "Child" };
    Vehicle* taxi = dir.createVehicle(taxiBuilder, taxiPassengerCategories);
    if (taxi->isReadyToDepart())
        cout << "Taxi is ready to depart!" << endl;
    else
        cout << "Taxi is not ready to depart!" << endl;

    delete taxi;

    return 0;
}
