#include <iostream>
#include <memory>  
#include <string>


class Pizza {
public:
    std::string dough;
    std::string sauce;
    std::string topping;
    std::string size;

    void show() const {
        std::cout << "Pizza (" << size << "): " << dough << " dough, "<< sauce << " sauce, and "<< topping << " topping." << std::endl;
    }
};

class PizzaBuilder {
public:
    virtual ~PizzaBuilder() {}
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual void buildSize(const std::string& size) = 0;
    virtual std::unique_ptr<Pizza> getPizza() = 0;
};

class PepperoniPizzaBuilder : public PizzaBuilder {
private:
    std::unique_ptr<Pizza> pizza;
public:
    PepperoniPizzaBuilder() { pizza = std::make_unique<Pizza>(); }
    void buildDough() override { pizza->dough = "thick"; }
    void buildSauce() override { pizza->sauce = "tomato"; }
    void buildTopping() override { pizza->topping = "pepperoni"; }
    void buildSize(const std::string& size) override { pizza->size = size; }
    std::unique_ptr<Pizza> getPizza() override { return std::move(pizza); }
};

class MargheritaPizzaBuilder : public PizzaBuilder {
private:
    std::unique_ptr<Pizza> pizza;
public:
    MargheritaPizzaBuilder() { pizza = std::make_unique<Pizza>(); }
    void buildDough() override { pizza->dough = "thin"; }
    void buildSauce() override { pizza->sauce = "basil"; }
    void buildTopping() override { pizza->topping = "mozzarella and tomatoes"; }
    void buildSize(const std::string& size) override { pizza->size = size; }
    std::unique_ptr<Pizza> getPizza() override { return std::move(pizza); }
};

class Cook {
private:
    PizzaBuilder* builder;
public:
    void setBuilder(PizzaBuilder* b) { builder = b; }
    std::unique_ptr<Pizza> getPizza() { return builder->getPizza(); }
    void constructPizza(const std::string& size) {
        builder->buildDough();
        builder->buildSauce();
        builder->buildTopping();
        builder->buildSize(size);
    }
};

int main() {
    Cook cook;

    PepperoniPizzaBuilder pepperoniBuilder;
    cook.setBuilder(&pepperoniBuilder);
    cook.constructPizza("Large");
    std::unique_ptr<Pizza> pepperoniPizza = cook.getPizza();
    pepperoniPizza->show();

    MargheritaPizzaBuilder margheritaBuilder;
    cook.setBuilder(&margheritaBuilder);
    cook.constructPizza("Medium");
    std::unique_ptr<Pizza> margheritaPizza = cook.getPizza();
    margheritaPizza->show();

    return 0;
}