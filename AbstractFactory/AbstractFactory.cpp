#include <iostream>
#include <vector>
using namespace std;

// Абстрактные базовые классы всех видов
class Driver
{
public:
    virtual void info() = 0;
    virtual string license_type() = 0;
    virtual ~Driver() { };

};

class Passenger
{
public:
    void info() {
        cout << "Board Passenger" << endl;
    };
    ~Passenger() {};
};


// Классы всех видов водителей
class BusDriver : public Driver
{
public:
    virtual void info() override {
        cout << "Board Bus Driver" << endl;
    }
    virtual string license_type() {
        return "D";
    }
};

class TaxiDriver : public Driver
{
public:
    virtual void info() {
        cout << "Board Taxi Driver" << endl;
    }
    virtual string license_type() {
        return "B";
    }
};

// Абстрактная фабрика для производства Водителей
class BoardAnyCar
{
protected:
    bool driverBoarded;
    int passengerCount;
    int maxPassengerCount;

public:
    BoardAnyCar(int maxPassCount) : driverBoarded(false), passengerCount(0), maxPassengerCount(maxPassCount) {}
    virtual Driver* boardDriver(string license) = 0;
    virtual Passenger* boardPassenger() = 0;
    virtual void start() = 0;
    virtual ~BoardAnyCar() {};
};

// Фабрика для производитства Водителей Автобусов и Таксистов 
class BoardBus : public BoardAnyCar
{
public:
    BoardBus() : BoardAnyCar(30) {}
    Driver* boardDriver(string license) override {
        if (!driverBoarded && license == "D")
        {
            driverBoarded = true;
            std::cout << "Bus driver boarded.\n";
            return new BusDriver;
        }
        else if (driverBoarded)
        {
            std::cout << "Bus driver has already boarded.\n";
        }
        else
        {
            std::cout << "Wrong license.\n";
        }
        return nullptr;
    }
    Passenger* boardPassenger() {
        if (passengerCount < maxPassengerCount) {
            std::cout << "Passenger boarded bus.\n";
            ++passengerCount;
            return new Passenger;
        }
        else
        {
            std::cout << "Bus is full. Cannot board more passengers.\n";
            return nullptr;
        }

    }
    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Bus is ready to depart.\n";
        }
        else {
            std::cout << "Bus is not ready to depart. Board driver and passengers first.\n";
        }
    }
};


class BoardTaxi : public BoardAnyCar
{
public:
    BoardTaxi() : BoardAnyCar(4) {}
    Driver* boardDriver(string license) override {
        if (!driverBoarded && license == "B")
        {
            driverBoarded = true;
            std::cout << "Taxi driver boarded.\n";
            return new TaxiDriver;
        }
        else if (driverBoarded)
        {
            std::cout << "Taxi driver has already boarded.\n";
        }
        else
        {
            std::cout << "Wrong license.\n";
        }
        return nullptr;
    }
    Passenger* boardPassenger() {
        if (passengerCount < maxPassengerCount) {
            std::cout << "Passenger boarded taxi.\n";
            ++passengerCount;
            return new Passenger;
        }
        else
        {
            std::cout << "Taxi is full. Cannot board more passengers.\n";
            return nullptr;
        }
    }
    void start() override {
        if (driverBoarded && passengerCount > 0) {
            std::cout << "Taxi is ready to depart.\n";
        }
        else {
            std::cout << "Taxi is not ready to depart. Board driver and passengers first.\n";
        }
    }
};


int main() {
    TaxiDriver* taxiDriver = new TaxiDriver();
    BusDriver* busDriver = new BusDriver();

    std::cout << "Taxi test:\n";
    BoardAnyCar* taxiBoard = new BoardTaxi();
    taxiBoard->boardDriver(busDriver->license_type());
    taxiBoard->boardDriver(taxiDriver->license_type());
    for (size_t i = 0; i < 5; i++)
    {
        taxiBoard->boardPassenger();
    }
    taxiBoard->start();

    std::cout << "\nBus test:\n";
    BoardAnyCar* busBoard = new BoardBus();
    busBoard->boardDriver(taxiDriver->license_type());
    busBoard->boardDriver(busDriver->license_type());
    for (size_t i = 0; i < 31; i++)
    {
        busBoard->boardPassenger();
    }
    busBoard->start();

    delete taxiBoard;
    delete busBoard;
    return 0;
}