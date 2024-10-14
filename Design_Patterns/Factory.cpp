#include <iostream>

class Transport {
    public:
        virtual void Driving() = 0;
        virtual ~Transport() {}
};

class Car : public Transport{
    public:
        void Driving() override{
            std::cout<<"Driving a car\n";
        }
};

class Motorcycle : public Transport{
    public:
        void Driving() override {
            std::cout<<"Driving a motorcycle\n";
        }
};

class TransportFactory {
    public:
        virtual Transport* createTransport() =0;
        virtual ~TransportFactory() {}
};

class CarFactory : public TransportFactory {
    public:
        Transport* createTransport() override {
            return new Car();
        }
};

class MotorcycleFactory : public TransportFactory {
    public:
        Transport* createTransport() override {
            return new Motorcycle();
        }
};

int main(){
    TransportFactory* carFactory = new CarFactory();
    TransportFactory* motorcycleFactory = new   MotorcycleFactory();   

    Transport* car = carFactory->createTransport();
    Transport* motorcycle = motorcycleFactory->createTransport();

    car->Driving();
    motorcycle->Driving();

    return 0;
}