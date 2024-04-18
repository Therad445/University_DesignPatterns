
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ����������� ����� ��������
class Driver {
public:
    virtual bool hasRequiredLicense() = 0;
    virtual ~Driver() {}
};

// ����������� ����� ��������
class Passenger {
public:
    virtual int getTicketPrice() = 0;
    virtual ~Passenger() {}
};

// ���������� ����� �������� ��� ��������
class BusDriver : public Driver {
public:
    bool hasRequiredLicense() override {
        // �������� ������� ����������� ���� ��� �������� ��������
        return true; // �����������, ��� � ���� ��������� ��������� ���� ����������� �����
    }
};

// ���������� ����� �������� ��� �����
class TaxiDriver : public Driver {
public:
    bool hasRequiredLicense() override {
        // �������� ������� ����������� ���� ��� �������� �����
        return true; // �����������, ��� � ���� ��������� ����� ���� ����������� �����
    }
};

// ���������� ����� �������� ��� ��������
class BusPassenger : public Passenger {
private:
    string category; // ��������� ���������: "Adult", "Child" ��� "Discount"
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
            return 0; // � ������ ������������ ��������� ������� 0
    }
};

// ���������� ����� �������� ��� �����
class TaxiPassenger : public Passenger {
private:
    string category; // ��������� ���������: "Adult" ��� "Child"
public:
    TaxiPassenger(string category) : category(category) {}
    int getTicketPrice() override {
        if (category == "Adult")
            return 10;
        else if (category == "Child")
            return 5;
        else
            return 0; // � ������ ������������ ��������� ������� 0
    }
};

// ����������� ����� ������������ ��������
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

// ���������� ����� �������
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
        return driver != nullptr && passengers.size() > 0 && passengers.size() <= 30; // �����������, ��� ����� �������� �������� - 30 ����������
    }
};

// ���������� ����� �����
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
        return driver != nullptr && passengers.size() > 0 && passengers.size() <= 4; // �����������, ��� ����� �������� ����� - 4 ���������
    }
};


// ����������� ����� ��������� ������������� ��������
class VehicleBuilder {
public:
    virtual Driver* createDriver() = 0;
    virtual Passenger* createPassenger(string category) = 0;
    virtual Vehicle* getVehicle() = 0;
    virtual ~VehicleBuilder() {}
};

// ���������� ����� ��������� ��� ��������
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

// ���������� ����� ��������� ��� �����
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


// ����� ��������
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

    // ������� �������
    BusBuilder busBuilder;
    vector<string> busPassengerCategories = { "Adult", "Child", "Discount", "Adult", "Child", "Child" };
    Vehicle* bus = dir.createVehicle(busBuilder, busPassengerCategories);
    if (bus->isReadyToDepart())
        cout << "Bus is ready to depart!" << endl;
    else
        cout << "Bus is not ready to depart!" << endl;

    delete bus;

    // ������� �����
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
