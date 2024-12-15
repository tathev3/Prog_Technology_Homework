#include <iostream>
#include <memory>

class State {
public:
    virtual ~State() = default;
    virtual void start() = 0;
    virtual void stop() = 0;
};

class Context {
private:
    std::shared_ptr<State> currentState;
public:
    void setState(std::shared_ptr<State> state) { currentState = state; }
    void start() { currentState->start(); }
    void stop() { currentState->stop(); }
};

class StoppedState : public State {
private:
    Context* context;
public:
    explicit StoppedState(Context* context) : context(context) {}
    void start() override {
        std::cout << "Starting...\n";
        context->setState(std::make_shared<StartedState>(context));
    }
    void stop() override { std::cout << "Already stopped.\n"; }
};

class StartedState : public State {
private:
    Context* context;
public:
    explicit StartedState(Context* context) : context(context) {}
    void start() override { std::cout << "Already started.\n"; }
    void stop() override {
        std::cout << "Stopping...\n";
        context->setState(std::make_shared<StoppedState>(context));
    }
};

int main() {
    Context machine;
    auto stoppedState = std::make_shared<StoppedState>(&machine);
    machine.setState(stoppedState);

    machine.start();
    machine.start();
    machine.stop();
    machine.stop();

    return 0;
}
