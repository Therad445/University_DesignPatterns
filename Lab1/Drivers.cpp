// #include "Driver.h"
#include <iostream>

// Singleton Driver
class Driver
{
    private:
        static Driver * instance;
        Driver() {}
        Driver( const Driver&);
        Driver& operator=(Driver&);
    public:
        static Driver * getInstance() {
            if(!instance)
                instance = new Driver();
            return instance;
        }
};

Driver * Driver::instance = 0;

// Abstract Factory Class
class BoardAnyCar
{
    public:
        virtual void boardDriver() = 0;
        virtual void boardPassengers() = 0;
        virtual ~BoardAnyCar() {}
};

class BoardTaxi : public BoardAnyCar
{
    public:
        void boardDriver() override
        {
            Driver * driver = Driver::getInstance();
            std::cout << "Taxi driver boarded." << std::endl;
        }

        void boardPassengers() override
        {
            std::cout << "Passengers boarded taxi." << std::endl;
        }
};

class BoardBus : 












int main(int argc, char const *argv[])
{
    return 0;
}

