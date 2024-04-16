#include <iostream>
#include <vector>
using namespace std;

class Passenger
{
public:
    void info() {
        cout << "Board Passenger" << endl;
    };
    ~Passenger() {};
};


class Driver
{
public:
    void info() {
        cout << "Board Driver" << endl;
    }
    string license_type() {
        return "";
    }
};


class BusDriver
{
public:
    void info() {
        cout << "Board Bus Driver" << endl;
    }
    string license_type() {
        return "D";
    }
};

class TaxiDriver 
{
public:
    void info() {
        cout << "Board Taxi Driver" << endl;
    }
    string license_type() {
        return "B";
    }
};

class Units
{
public:
    vector<Passenger> vp;
    vector<Driver> vd;
    void info() {
        int i;
        for (i = 0; i < vp.size(); i++) vp[i].info();
        for (i = 0; i < vd.size(); i++) vd[i].info();
    }
};


class UnitsBuilder
{
protected:
    Units* u;
public:
    UnitsBuilder() : u(0) {};
    virtual ~UnitsBuilder() {};
    virtual void createUnits() {};
    virtual void boardDriver() {};
    virtual void boardPassenger() {};
    virtual Units* getUnits() { return u; };
};

class TaxiBuilder : public UnitsBuilder
{
public:
    void createUnits() { u = new Units; };
    void boardDriver() { u->vd.push_back(Driver()); };
    void boardPassenger() { u->vp.push_back(Passenger()); };
};

class BusBuilder : public UnitsBuilder
{
public:
    void createUnits() { u = new Units; };
    void boardDriver() { u->vd.push_back(Driver()); };
    void boardPassenger() { u->vp.push_back(Passenger()); };
};

class Director
{
public:
    Units* createUnits(UnitsBuilder& builder)
    {
        builder.createUnits();
        builder.boardDriver();
        builder.boardPassenger();
        return (builder.getUnits());
    }
};



int main()
{
    Director dir;
    BusBuilder b_builder;
    TaxiBuilder t_builder;

    Units* b = dir.createUnits(b_builder);
    Units* t = dir.createUnits(t_builder);
    b->info();
    t->info();
    return 0;
}
