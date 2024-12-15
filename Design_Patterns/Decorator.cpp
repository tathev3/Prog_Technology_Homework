#include <iostream>
#include <string>

class Cake 
{
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};

class PlainCake : public Cake
{
public:
    std::string getDescription() const override
    {
        return "Plain Cake";
    }

    double cost() const override { return 300.0; }
};

class CakeDecorator : public Cake
{
protected:
    Cake* cake;

public:
    CakeDecorator(Cake* c)
        : cake(c)
    {
    }

    std::string getDescription() const override
    {
        return cake->getDescription();
    }

    double cost() const override { return cake->cost(); }
};


class ChocolateDecorator : public CakeDecorator
{
public:
    ChocolateDecorator(Cake* c)
        : CakeDecorator(c)
    {
    }

    std::string getDescription() const override
    {
        return cake->getDescription() + " with Chocolate";
    }

    double cost() const override
    {
        return cake->cost() + 200.0;
    }
};

class FruitDecorator : public CakeDecorator 
{
public:
    FruitDecorator(Cake* c)
        : CakeDecorator(c)
    {
    }

    std::string getDescription() const override
    {
        return cake->getDescription() + " with Fruits";
    }

    double cost() const override
    {
        return cake->cost() + 150.0;
    }
};

int main()
{
    Cake* plainCake = new PlainCake();
    std::cout << "Plain Cake:" << plainCake->getDescription()
         << "\nCost:Rs." << plainCake->cost() << std::endl;

    Cake* chocolateCake = new ChocolateDecorator(plainCake);
    std::cout << "\nChocolate Cake:"
         << chocolateCake->getDescription() << "\nCost:Rs."
         << chocolateCake->cost() << std::endl;


    Cake* fruitCake1 = new FruitDecorator(chocolateCake);
    std::cout << "\nFruit Cake:" << fruitCake1->getDescription()
         << "\nCost:Rs." << fruitCake1->cost() << std::endl;

    delete chocolateCake;
    delete fruitCake1;

    Cake* fruitCake2 = new FruitDecorator(plainCake);
    std::cout << "\nFruit Cake:" << fruitCake2->getDescription()
         << "\nCost:Rs." << fruitCake2->cost() << std::endl;

    delete plainCake;
    delete fruitCake2;

    return 0;
}