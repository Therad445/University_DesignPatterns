#include <iostream>
#include <vector>
#include <cassert>

// Components
class Stewardess
{
public:
	Stewardess();
	~Stewardess();
};


class Pilot
{
public:
	Pilot();
	~Pilot();
};


class Passenger
{
public:
	virtual void setWeight(int input_weight) = 0;
	virtual int getWeight() = 0;
	virtual void addPassenger(Passenger* p) {
		assert(false);
	}
	virtual bool isPaid() = 0;
	virtual ~Passenger() {};
};


// Primitives
class FirstClass : public Passenger
{
private:
	int weight; //Baggage weight
	bool paid; //Baggage paid if overweight
	bool unloaded; // Baggage unloaded
public:
	FirstClass() : weight(0), paid(false), unloaded(false) {} // Initialisation in constructor
	void setWeight(int input_weight) override {
		if (input_weight > 60)
		{
			std::cout << "Absolute overweight baggage. Incorrect!";
		}
		else if (input_weight >= 0 && input_weight <= 60)
		{
			std::cout << "Free baggage";
			paid = false;
			weight = input_weight;
		}
	}
	int getWeight() override {
		return unloaded ? 0 : weight;
	}
	bool isPaid() override {
		return paid;
	}
	void unloadBaggage() {
		unloaded = true;
	}
};


class BusinessClass : public Passenger
{
private:
	int weight;
	bool paid;
	bool unloaded;
public:
	BusinessClass() : weight(0), paid(false), unloaded(false) {}
	void setWeight(int input_weight) override {
		if (input_weight > 60)
		{
			std::cout << "Absolute overweight baggage. Incorrect!";
		}
		else if (input_weight > 35 && input_weight <= 60)
		{
			std::cout << "Paid baggage";
			paid = true;
			weight = input_weight;
		}
		else if (input_weight >= 0 && input_weight <= 35)
		{
			std::cout << "Free baggage";
			paid = false;
			weight = input_weight;
		}
	}
	int getWeight() override {
		return unloaded ? 0 : weight;
	}
	bool isPaid() override {
		return paid;
	}
	void unloadBaggage() {
		unloaded = true;
	}
};


class EconomyClass : public Passenger
{
private:
	int weight;
	bool paid;
	bool unloaded;
public:
	EconomyClass() : weight(0), paid(false), unloaded(false) {}
	void setWeight(int input_weight) override {
		if (input_weight > 60)
		{
			std::cout << "Absolute overweight baggage. Incorrect!";
		}
		else if (input_weight > 20 && input_weight <= 60)
		{
			std::cout << "Paid baggage";
			paid = true;
			weight = input_weight;
		}
		else if (input_weight >= 0 && input_weight <= 20)
		{
			std::cout << "Free baggage";
			paid = false;
			weight = input_weight;
		}
	}
	int getWeight() override {
		return unloaded ? 0 : weight;
	}
	bool isPaid() override {
		return paid;
	}
	void unloadBaggage() {
		unloaded = true;
	}
};


// Composite
class CompositePassenger : public Passenger
{
private:
	std::vector<Passenger*> c;
public:
	void setWeight(int input_weight) override {};
	int getWeight() override {
		int total = 0;
		for (int i = 0; i < c.size(); i++)
			total += c[i]->getWeight();
		return total;
	}
	void addPassenger(Passenger* p) override {
		c.push_back(p);
	}

	//bool removeOnePaidEconomyPassenger() {
	//	for (auto it = c.begin(); it != c.end(); ++it) {
	//		EconomyClass* ec = dynamic_cast<EconomyClass*>(*it);
	//		if (ec && ec->isPaid()) {
	//			delete ec;  // Удаление объекта
	//			c.erase(it);  // Удаление указателя из вектора
	//			return true;  // Возвращает true, если удаление произошло
	//		}
	//	}
	//	return false;  // Нет больше эконом-класс пассажиров с платным багажом для удаления
	//}

	void unloadedOnePaidEconomyPassenger(int max_weight) {
		for (auto it = c.begin(); it != c.end(); ++it) {
			EconomyClass* ec = dynamic_cast<EconomyClass*>(*it);
			if (ec && ec->isPaid()) {
				ec->unloadBaggage();  // Change flag
				if (getWeight() <= max_weight) break;
			}
		}
	}


	bool isPaid() override {
		return false;
	}
	~CompositePassenger() {
		for (int i = 0; i < c.size(); i++)
			delete c[i];
	}
};

CompositePassenger* createAirplane(int max_weight)
{
	CompositePassenger* airplane = new CompositePassenger;
	// 10 FirstClass Passsengers
	for (int i = 0; i < 10; i++)
	{
		FirstClass* fc = new FirstClass;
		fc->setWeight(50);  // Set weight for each passenger
		airplane->addPassenger(fc);
		std::cout << "Added FirstClass passenger with 50kg baggage" << std::endl;
	}
	// 20 BusinessClass Passsengers
	for (int i = 0; i < 20; i++)
	{
		BusinessClass* bc = new BusinessClass;
		bc->setWeight(40);  // Set weight for each passenger
		airplane->addPassenger(bc);
		std::cout << "Added BusinessClass passenger with 40kg baggage" << std::endl;
	}
	// 150 EconomyClass Passsengers
	for (int i = 0; i < 150; i++)
	{
		EconomyClass* ec = new EconomyClass;
		ec->setWeight(30);  // Set weight for each passenger
		airplane->addPassenger(ec);
		std::cout << "Added EconomyClass passenger with 30kg baggage" << std::endl;
	}
	std::cout << "Total baggage weight is " << airplane->getWeight() << std::endl;
	if (airplane->getWeight() > max_weight)
	{
		std::cout << "Overweight  baggages weight! Limit is " << max_weight << std::endl;
	}
	while (airplane->getWeight() > max_weight) {
		//airplane->removeOnePaidEconomyPassenger();  // Delete 
		airplane->unloadedOnePaidEconomyPassenger(max_weight);
		if (airplane->getWeight() <= max_weight) break;
	}
	std::cout << "After unload, total baggage weight is " << airplane->getWeight() << std::endl;
	return airplane;
}

int main()
{
	CompositePassenger* airplane = new CompositePassenger;
	airplane->addPassenger(createAirplane(5500));
	delete airplane;
    return 0;
}
