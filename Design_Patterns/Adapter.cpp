#include <iostream>

class CoffeeMaker {
public:
    virtual void Coffee() = 0;
};

class EspressoMachine {
public:
    void Espresso() {
        std::cout << "Brewing a rich espresso shot!" << std::endl;
    }
};

class DripCoffeeMaker {
public:
    void DripCoffee() {
        std::cout << "Brewing a smooth drip coffee!" << std::endl;
    }
};

class EspressoAdapter : public CoffeeMaker {
private:
    EspressoMachine* espressoMachine;

public:
    EspressoAdapter(EspressoMachine* machine) : espressoMachine(machine) {}

    void Coffee() override {
        espressoMachine->Espresso();
    }
};

class DripAdapter : public CoffeeMaker {
private:
    DripCoffeeMaker* dripCoffeeMaker;

public:
    DripAdapter(DripCoffeeMaker* maker) : dripCoffeeMaker(maker) {}

    void Coffee() override {
        dripCoffeeMaker->DripCoffee();
    }
};

int main() {
    EspressoMachine* espressoMachine = new EspressoMachine();
    DripCoffeeMaker* dripCoffeeMaker = new DripCoffeeMaker();

    CoffeeMaker* espressoAdapter = new EspressoAdapter(espressoMachine);
    CoffeeMaker* dripAdapter = new DripAdapter(dripCoffeeMaker);

    std::cout << "Customer orders coffee:" << std::endl;
    espressoAdapter->Coffee();
    dripAdapter->Coffee();

    delete espressoAdapter;
    delete dripAdapter;
    delete espressoMachine;
    delete dripCoffeeMaker;

    return 0;
}