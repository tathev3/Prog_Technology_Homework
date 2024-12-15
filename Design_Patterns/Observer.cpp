#include <iostream>
#include <vector>
#include <memory>

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update(float temperature, float humidity, float pressure) = 0;
};

class Subject
{
public:
    virtual ~Subject() = default;
    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
};

class WeatherStation : public Subject
{
private:
    std::vector<std::shared_ptr<Observer>> observers;
    float temperature, humidity, pressure;
public:
    void registerObserver(std::shared_ptr<Observer> observer) override
    {
        observers.push_back(observer);
    }
    void removeObserver(std::shared_ptr<Observer> observer) override
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notifyObservers() override
    {
        for (auto& observer : observers) observer->update(temperature, humidity, pressure);
    }
    void setMeasurements(float temp, float hum, float press)
    {
        temperature = temp;
        humidity = hum;
        pressure = press;
        notifyObservers();
    }
};

class CurrentConditionsDisplay : public Observer
{
private:
    float temperature, humidity;
public:
    void update(float temp, float hum, float pressure) override
    {
        temperature = temp;
        humidity = hum;
        display();
    }
    void display()
    {
        std::cout << "Current conditions: " << temperature << "C degrees and " << humidity << "% humidity.\n";
    }
};

class StatisticsDisplay : public Observer
{
private:
    float maxTemp = -1e9, minTemp = 1e9, tempSum = 0;
    int numReadings = 0;
public:
    void update(float temp, float hum, float pressure) override
    {
        tempSum += temp;
        numReadings++;
        maxTemp = std::max(maxTemp, temp);
        minTemp = std::min(minTemp, temp);
        display();
    }
    void display()
    {
        std::cout << "Avg/Max/Min temperature = " << (tempSum / numReadings) << "/" << maxTemp << "/" << minTemp << "\n";
    }
};

int main()
{
    auto weatherStation = std::make_shared<WeatherStation>();
    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>();
    auto statisticsDisplay = std::make_shared<StatisticsDisplay>();

    weatherStation->registerObserver(currentDisplay);
    weatherStation->registerObserver(statisticsDisplay);

    weatherStation->setMeasurements(25.0f, 65.0f, 1013.0f);
    weatherStation->setMeasurements(27.0f, 70.0f, 1012.0f);
    weatherStation->setMeasurements(23.0f, 60.0f, 1011.0f);

    return 0;
}
