#include <iostream>
#include <vector>
using namespace std;

// Абстрактные базовые классы всех видов водителей
class Driver {
    public:
        virtual void info() = 0;
        virtual ~Driver() {}
};

// Классы всех видов водителей

class BusDriver: public Driver {
    public:
        virtual void info() {
            cout << "BusDriver" << endl;
        }
};


class TaxiDriver: public Driver {
    public:
        virtual void info() {
            cout << "TaxiDriver" << endl;
        }
};

// Абстрактная фабрика для производства Водителей
class BoardAnyCar 
{
    public:
        virtual Driver* createDriver() = 0;
        virtual ~BoardAnyCar() {}
};

// Фабрика для производитства Водителей Автобусов и Таксистов 
class BoardBus: public BoardAnyCar 
{
    public:
        Driver* createDriver() {
            return new BusDriver;
        }
};

 
class BoardTaxi: public BoardAnyCar
{
    public:
        Driver* createDriver() {
            return new TaxiDriver;
        }
};


class Drivers
{
    public:
        ~Drivers() {
            for(int i=0; i<vd.size(); ++i) delete vd[i];
        }
        void info() {
            for(int i=0; i<vd.size(); ++i) vd[i]->info();
        }
        vector<Driver*> vd;
};

class Passenger
{
    public:
        Drivers* createDriver (BoardAnyCar& factory) {
            Drivers* p = new Drivers;
            p->vd.push_back(factory.createDriver());
            return p;
        }
};


int main (){
    Passenger passenger;
    BoardBus bb_factory;
    BoardTaxi bt_factory;

    Drivers * bb = passenger.createDriver(bb_factory);
    Drivers * bt = passenger.createDriver(bt_factory);
    cout << "Bus:" << endl;
    bb->info();
    cout << "Taxi:" << endl;
    bt->info();
    delete bb;
    delete bt;
    return 0;
}