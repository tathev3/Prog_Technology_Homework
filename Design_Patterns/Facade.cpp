#include <iostream>
#include <string>

class TV
{
public:
    void on() { std::cout << "TV is ON.\n"; }
    void off() { std::cout << "TV is OFF.\n"; }
    void setInput(const std::string& input) { std::cout << "TV input set to " << input << ".\n"; }
};

class SoundSystem
{
public:
    void on() { std::cout << "Sound System is ON.\n"; }
    void off() { std::cout << "Sound System is OFF.\n"; }
    void setVolume(int level) { std::cout << "Sound System volume set to " << level << ".\n"; }
};

class Lights
{
public:
    void dim(int level) { std::cout << "Lights dimmed to " << level << "%.\n"; }
    void on() { std::cout << "Lights are ON.\n"; }
};

class HomeTheaterFacade
{
private:
    TV& tv;
    SoundSystem& soundSystem;
    Lights& lights;
public:
    HomeTheaterFacade(TV& tv, SoundSystem& soundSystem, Lights& lights) 
        : tv(tv), soundSystem(soundSystem), lights(lights) {}

    void watchMovie(const std::string& movie)
    {
        std::cout << "Preparing to watch \"" << movie << "\"...\n";
        lights.dim(20);
        tv.on();
        tv.setInput("HDMI");
        soundSystem.on();
        soundSystem.setVolume(10);
        std::cout << "Enjoy your movie!\n";
    }
    void endMovie()
    {
        std::cout << "Shutting down the home theater...\n";
        tv.off();
        soundSystem.off();
        lights.on();
    }
};

int main()
{
    TV tv;
    SoundSystem soundSystem;
    Lights lights;

    HomeTheaterFacade homeTheater(tv, soundSystem, lights);
    homeTheater.watchMovie("Inception");
    homeTheater.endMovie();

    return 0;
}
