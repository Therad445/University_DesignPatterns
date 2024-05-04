#include <iostream>
#include <vector>
#include <cassert>

// Components
class Stewardess
{
public:
	void board() {
		std::cout << "Stewardess boarded";
	};
	~Stewardess() {};
};


class Pilot
{
public:
	void board() {
		std::cout << "Pilot boarded";
	};
	~Pilot() {};
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
class Composite : public Passenger, public Pilot, public Stewardess
{
private:
	std::vector<Passenger*> pas;
	std::vector<Pilot*> pil;
	std::vector<Stewardess*> stew;
public:
	void setWeight(int input_weight) override {};
	int getWeight() override {
		int total = 0;
		for (int i = 0; i < pas.size(); i++)
			total += pas[i]->getWeight();
		return total;
	}
	void addPassenger(Passenger* pa) override {
		pas.push_back(pa);
	}
	void addPilot(Pilot* pi) {
		pil.push_back(pi);
	}
	void addStewardess(Stewardess* st) {
		stew.push_back(st);
	}


	void unloadPaidEconomyPassenger(int max_weight) {
		for (auto it = pas.begin(); it != pas.end(); ++it) {
			EconomyClass* ec = dynamic_cast<EconomyClass*>(*it);
			if (ec && ec->isPaid()) {
				ec->unloadBaggage();  // Change flag
				if (getWeight() <= max_weight) break;
			}
			if (it == pas.end() - 1 && getWeight() > max_weight) {
				std::cout << "Unfortunetly, but this airplane is still overweight. Please, change the limit or remove some passengers." << std::endl;
				break;
			}
		}
	}

	void isReady() {
		if (pil.size() == 2 && stew.size() == 6 && pas.size() != 0)
		{
			std::cout << "Airplane is ready.\n";
		}
		else
		{
			std::cout << "Airplane is NOT ready.\n";
			//std::cin >> NULL;
		}
	}


	bool isPaid() override {
		return false;
	}
	~Composite() {
		for (int i = 0; i < pas.size(); i++)
			delete pas[i];
	}
};

Composite* createAirplane(int max_weight)
{
	Composite* airplane = new Composite;
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
	// 2 Pilot
	for (size_t i = 0; i < 2; i++)
	{
		Pilot* pi = new Pilot;
		airplane->addPilot(pi);
	}
	// 6 Stewardess
	for (size_t i = 0; i < 6; i++)
	{
		Stewardess* st = new Stewardess;
		airplane->addStewardess(st);
	}
	airplane->isReady();
	std::cout << "Total baggage weight is " << airplane->getWeight() << std::endl;
	if (airplane->getWeight() > max_weight)
	{
		std::cout << "Overweight  baggages weight! Limit is " << max_weight << std::endl;
	}
	if (airplane->getWeight() > max_weight) {
		airplane->unloadPaidEconomyPassenger(max_weight);
	}
	std::cout << "After unload, total baggage weight is " << airplane->getWeight() << std::endl;
	return airplane;
}

int main()
{
	Composite* airplane = new Composite;
	airplane->addPassenger(createAirplane(1100));
	delete airplane;
    return 0;
}
