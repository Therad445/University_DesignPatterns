#include <iostream>
#include <vector>
#include <cassert>

enum class PassengerType {
	FirstClass,
	BusinessClass,
	EconomyClass
};

// Abstract Unit (Component)
class Unit
{
public:
	virtual void board() = 0;
	virtual void setWeight(int input_weight) = 0;
	virtual int getWeight() = 0;
	virtual void addPassenger(Unit* p, PassengerType type) {
		assert(false);
	};
	virtual bool isPaid() = 0;
	~Unit() = default;
};


// Components
class Stewardess: public Unit
{
public:
	void board() override {
		std::cout << "Stewardess boarded";
	};
	void setWeight(int input_weight) override {
		assert(false);
	}
	int getWeight() override {
		return 0;
	}
	bool isPaid() override {
		return false;
	}
};


class Pilot : public Unit
{
public:
	void board() override {
		std::cout << "Pilot boarded";
	};
	void setWeight(int input_weight) override {
		assert(false);
	}
	int getWeight() override {
		return 0;
	}
	bool isPaid() override {
		return false;
	}
};


//class Passenger
//{
//public:
//	virtual void setWeight(int input_weight) = 0;
//	virtual int getWeight() = 0;
//	virtual void addPassenger(Passenger* p) {
//		assert(false);
//	}
//	virtual bool isPaid() = 0;
//	virtual ~Passenger() {};
//};


// Primitives
class FirstClass : public Unit
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
	void addPassenger(Unit* p, PassengerType type) override {
		assert(false);
	};
	void board() override {
		std::cout << "FirstClass passenger boarded\n";
	};
};


class BusinessClass : public Unit
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
	void addPassenger(Unit* p, PassengerType type) override {
		assert(false);
	};
	void board() override {
		std::cout << "BusinessClass passenger boarded\n";
	};
};


class EconomyClass : public Unit
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
	void addPassenger(Unit* p, PassengerType type) override {
		assert(false);
	};
	void board() override {
		std::cout << "EconomyClass passenger boarded\n";
	};
};


//// Composite
//class Composite : public Unit
//{
//private:
//	std::vector<Unit*> passengersFirst;
//	std::vector<Unit*> passengersBusiness;
//	std::vector<Unit*> passengersEconomy;
//
//	std::vector<Unit*> pilots;
//	std::vector<Unit*> stewardeses;
//public:
//	void setWeight(int input_weight) override {};
//	int getWeight() override {
//		int total = 0;
//		for (Unit* passenger : passengersFirst)
//			total += passenger->getWeight();
//		for (Unit* passenger : passengersBusiness)
//			total += passenger->getWeight();
//		for (Unit* passenger : passengersEconomy)
//			total += passenger->getWeight();
//		return total;
//	}
//	void addPassenger(Unit* pa, PassengerType type) override {
//		switch (type) {
//		case PassengerType::FirstClass:
//			passengersFirst.push_back(pa);
//			break;
//		case PassengerType::BusinessClass:
//			passengersBusiness.push_back(pa);
//			break;
//		case PassengerType::EconomyClass:
//			passengersEconomy.push_back(pa);
//			break;
//		}
//	}
//	void board() override {
//		// Реализация метода board для Composite
//		std::cout << "Boarding all members of the airplane...\n";
//		for (Unit* pilot : pilots) {
//			pilot->board();
//		}
//		for (Unit* stewardess : stewardeses) {
//			stewardess->board();
//		}
//		for (Unit* passenger : passengersFirst) {
//			passenger->board();
//		}
//		for (Unit* passenger : passengersBusiness) {
//			passenger->board();
//		}
//		for (Unit* passenger : passengersEconomy) {
//			passenger->board();
//		}
//	}
//	bool isPaid() override {
//		return false;
//	}
//	void addPilot(Unit* pil) {
//		pilots.push_back(pil);
//	}
//	void addStewardess(Unit* stew) {
//		stewardeses.push_back(stew);
//	}
//
//	void unloadPaidEconomyPassenger(int max_weight) {
//		for (auto it = passengersEconomy.begin(); it != passengersEconomy.end(); ++it) {
//			EconomyClass* ec = dynamic_cast<EconomyClass*>(*it);
//			if (ec && ec->isPaid()) {
//				ec->unloadBaggage();  // Change flag
//				if (getWeight() <= max_weight) break;
//			}
//			if (it == passengersEconomy.end() - 1 && getWeight() > max_weight) {
//				std::cout << "Unfortunetly, but this airplane is still overweight. Please, change the limit or remove some passengers." << std::endl;
//				break;
//			}
//		}
//	}
//
//	void isReady() {
//		if (pilots.size() == 2 && stewardeses.size() == 6 /*&& pas.size() != 0*/)
//		{
//			std::cout << "Airplane is ready.\n";
//		}
//		else
//		{
//			std::cout << "Airplane is NOT ready.\n";
//			//std::cin >> NULL;
//		}
//	}
//	~Composite() {
//		for (int i = 0; i < passengersFirst.size(); i++)
//			delete passengersFirst[i];
//		for (int i = 0; i < passengersBusiness.size(); i++)
//			delete passengersBusiness[i];
//		for (int i = 0; i < passengersEconomy.size(); i++)
//			delete passengersEconomy[i];
//		for (int i = 0; i < pilots.size(); i++)
//			delete pilots[i];
//		for (int i = 0; i < stewardeses.size(); i++)
//			delete stewardeses[i];
//	}
//};
//
//Composite* createAirplane(int max_weight)
//{
//	Composite* airplane = new Composite;
//	// 10 FirstClass Passsengers
//	for (int i = 0; i < 10; i++)
//	{
//		FirstClass* fc = new FirstClass;
//		fc->setWeight(50);  // Set weight for each passenger
//		airplane->addPassenger(fc, PassengerType::FirstClass);
//		std::cout << "Added FirstClass passenger with 50kg baggage" << std::endl;
//	}
//	// 20 BusinessClass Passsengers
//	for (int i = 0; i < 20; i++)
//	{
//		BusinessClass* bc = new BusinessClass;
//		bc->setWeight(40);  // Set weight for each passenger
//		airplane->addPassenger(bc, PassengerType::BusinessClass);
//		std::cout << "Added BusinessClass passenger with 40kg baggage" << std::endl;
//	}
//	// 150 EconomyClass Passsengers
//	for (int i = 0; i < 150; i++)
//	{
//		EconomyClass* ec = new EconomyClass;
//		ec->setWeight(30);  // Set weight for each passenger
//		airplane->addPassenger(ec, PassengerType::EconomyClass);
//		std::cout << "Added EconomyClass passenger with 30kg baggage" << std::endl;
//	}
//	// 2 Pilot
//	for (size_t i = 0; i < 2; i++)
//	{
//		Pilot* pi = new Pilot;
//		airplane->addPilot(pi);
//	}
//	// 6 Stewardess
//	for (size_t i = 0; i < 6; i++)
//	{
//		Stewardess* st = new Stewardess;
//		airplane->addStewardess(st);
//	}
//	airplane->isReady();
//	std::cout << "Total baggage weight is " << airplane->getWeight() << std::endl;
//	if (airplane->getWeight() > max_weight)
//	{
//		std::cout << "Overweight  baggages weight! Limit is " << max_weight << std::endl;
//		airplane->unloadPaidEconomyPassenger(max_weight);
//	}
//	std::cout << "After unload, total baggage weight is " << airplane->getWeight() << std::endl;
//	return airplane;
//}
//
//int main()
//{
//	Composite* airplane = createAirplane(1500);
//	delete airplane;
//    return 0;
//}


class PassengerComposite : public Unit {
private:
	std::vector<Unit*> passengersFirst;
	std::vector<Unit*> passengersBusiness;
	std::vector<Unit*> passengersEconomy;
public:
	void setWeight(int input_weight) override {}
	int getWeight() override {
		int total = 0;
		for (Unit* passenger : passengersFirst)
			total += passenger->getWeight();
		for (Unit* passenger : passengersBusiness)
			total += passenger->getWeight();
		for (Unit* passenger : passengersEconomy)
			total += passenger->getWeight();
		return total;
	}
	void addPassenger(Unit* pa, PassengerType type) override {
		switch (type) {
		case PassengerType::FirstClass:
			passengersFirst.push_back(pa);
			break;
		case PassengerType::BusinessClass:
			passengersBusiness.push_back(pa);
			break;
		case PassengerType::EconomyClass:
			passengersEconomy.push_back(pa);
			break;
		}
	}
	void board() override {
		std::cout << "Boarding all passengers...\n";
		for (Unit* passenger : passengersFirst)
			passenger->board();
		for (Unit* passenger : passengersBusiness)
			passenger->board();
		for (Unit* passenger : passengersEconomy)
			passenger->board();
	}
	bool isPaid() override {
		return false; // Composite сам по себе не является пассажиром
	}
	void unloadPaidEconomyPassenger(int max_weight) {
		for (auto it = passengersEconomy.begin(); it != passengersEconomy.end(); ++it) {
			EconomyClass* ec = dynamic_cast<EconomyClass*>(*it);
			if (ec && ec->isPaid()) {
				ec->unloadBaggage();
				if (getWeight() <= max_weight) break;
			}
			if (it == passengersEconomy.end() - 1 && getWeight() > max_weight) {
				std::cout << "Unfortunately, this airplane is still overweight. Please, change the limit or remove some passengers." << std::endl;
				break;
			}
		}
	}
	~PassengerComposite() {
		for (Unit* passenger : passengersFirst)
			delete passenger;
		for (Unit* passenger : passengersBusiness)
			delete passenger;
		for (Unit* passenger : passengersEconomy)
			delete passenger;
	}
};

class CrewComposite : public Unit {
private:
	std::vector<Unit*> pilots;
	std::vector<Unit*> stewardeses;
public:
	void setWeight(int input_weight) override {}
	int getWeight() override {
		return 0; // Экипаж не имеет багажа в данной модели
	}
	void addPilot(Unit* pil) {
		pilots.push_back(pil);
	}
	void addStewardess(Unit* stew) {
		stewardeses.push_back(stew);
	}
	void board() override {
		std::cout << "Boarding all crew members...\n";
		for (Unit* pilot : pilots)
			pilot->board();
		for (Unit* stewardess : stewardeses)
			stewardess->board();
	}
	bool isPaid() override {
		return false; // Composite сам по себе не является пассажиром
	}
	bool isReady() {
		return pilots.size() == 2 && stewardeses.size() == 6;
	}
	~CrewComposite() {
		for (Unit* pilot : pilots)
			delete pilot;
		for (Unit* stewardess : stewardeses)
			delete stewardess;
	}
};

PassengerComposite* createPassengers(int max_weight) {
	PassengerComposite* passengers = new PassengerComposite;

	// 10 пассажиров FirstClass
	for (int i = 0; i < 10; i++) {
		FirstClass* fc = new FirstClass;
		fc->setWeight(50);
		passengers->addPassenger(fc, PassengerType::FirstClass);
		std::cout << "Added FirstClass passenger with 50kg baggage\n";
	}

	// 20 пассажиров BusinessClass
	for (int i = 0; i < 20; i++) {
		BusinessClass* bc = new BusinessClass;
		bc->setWeight(40);
		passengers->addPassenger(bc, PassengerType::BusinessClass);
		std::cout << "Added BusinessClass passenger with 40kg baggage\n";
	}

	// 150 пассажиров EconomyClass
	for (int i = 0; i < 150; i++) {
		EconomyClass* ec = new EconomyClass;
		ec->setWeight(30);
		passengers->addPassenger(ec, PassengerType::EconomyClass);
		std::cout << "Added EconomyClass passenger with 30kg baggage\n";
	}

	std::cout << "Total baggage weight is " << passengers->getWeight() << std::endl;
	if (passengers->getWeight() > max_weight) {
		std::cout << "Overweight baggage! Limit is " << max_weight << std::endl;
		passengers->unloadPaidEconomyPassenger(max_weight);
	}
	std::cout << "After unload, total baggage weight is " << passengers->getWeight() << std::endl;

	return passengers;
}

CrewComposite* createCrew() {
	CrewComposite* crew = new CrewComposite;

	// 2 пилота
	for (size_t i = 0; i < 2; i++) {
		Pilot* pi = new Pilot;
		crew->addPilot(pi);
	}

	// 6 бортпроводников
	for (size_t i = 0; i < 6; i++) {
		Stewardess* st = new Stewardess;
		crew->addStewardess(st);
	}

	if (crew->isReady()) {
		std::cout << "Crew is ready.\n";
	}
	else {
		std::cout << "Crew is NOT ready.\n";
	}

	return crew;
}

int main() {
	int max_weight = 1700;

	// Создаем пассажиров и экипаж
	PassengerComposite* passengers = createPassengers(max_weight);
	CrewComposite* crew = createCrew();

	// Бординг пассажиров и экипажа
	crew->board();
	passengers->board();

	// Удаление объектов после использования
	delete passengers;
	delete crew;

	return 0;
}


// От unit наследовать все классы (Passenger, Stawedess, BusinessClass и другие)
// Несколько Composite для реализации