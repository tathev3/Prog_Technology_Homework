#include <iostream>
#include <string>

class stateManager{
    private:
        static stateManager* instance;
        std::string currentState;

        stateManager(){
            currentState = "Initialled\n";
        }
        stateManager(const stateManager& ) = delete;
        stateManager& operator=(const stateManager&) = delete;

    public:
        static stateManager* getInstance(){
            if (instance == nullptr){
                instance = new stateManager();
            }
            return instance;
        }
        void setState ( const std::string& state){
            currentState = state;
        }
        std::string getState() const {
            return currentState;
        }
};

stateManager* stateManager:: instance = nullptr;

int main(){
    stateManager* s1 = stateManager::getInstance();
    s1->setState("Processing \n");
    std::string state = s1->getState();
    std::cout << "Current state :: " <<state;

    return 0;
}