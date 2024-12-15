#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Light
{
public:
    void turnOn() { std::cout << "The light is ON.\n"; }
    void turnOff() { std::cout << "The light is OFF.\n"; }
};

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class LightOnCommand : public Command
{
private:
    Light* light;
public:
    explicit LightOnCommand(Light* light) : light(light) {}
    void execute() override { light->turnOn(); }
    void undo() override { light->turnOff(); }
};

class LightOffCommand : public Command
{
private:
    Light* light;
public:
    explicit LightOffCommand(Light* light) : light(light) {}
    void execute() override { light->turnOff(); }
    void undo() override { light->turnOn(); }
};

class RemoteControl
{
private:
    std::vector<std::unique_ptr<Command>> history;
public:
    void setCommand(std::unique_ptr<Command> command) {
        command->execute();
        history.push_back(std::move(command));
    }
    void undoLastCommand() {
        if (!history.empty()) {
            history.back()->undo();
            history.pop_back();
        } else {
            std::cout << "No commands to undo.\n";
        }
    }
};

int main()
{
    Light livingRoomLight;
    auto lightOn = std::make_unique<LightOnCommand>(&livingRoomLight);
    auto lightOff = std::make_unique<LightOffCommand>(&livingRoomLight);
    RemoteControl remote;
    remote.setCommand(std::move(lightOn));
    remote.setCommand(std::move(lightOff));
    remote.undoLastCommand();
    remote.undoLastCommand();
    return 0;
}
