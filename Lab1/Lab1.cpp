#include <iostream>
#include <vector>

// Абстрактные базовые классы всех видов водителей
class Driver {
    public:
        virtual void info() = 0;
        virtual ~Driver() {}
};

class BusDriver {
    public:
        virtual void info() = 0;
        virtual ~BusDriver() {}
};


class TaxiDriver {
    public:
        virtual void info() = 0;
        virtual ~TaxiDriver() {}
};

// 


int main (){
    return 0;
}