#include <iostream>

class Button {
    public:
        virtual void paint() = 0;
};

class winButton : public Button{
    public:
        void paint(){
            std::cout<<"Painting a Windows button\n";
        }
};

class macButton : public Button{
    public:
        void paint(){
            std::cout<<"Paintin a macOS button\n";
        }
};

class GUIFactory {
    public:
        virtual Button* createButton() = 0;
};

class winFactory : public GUIFactory {
    public:
        Button* createButton() {
            return new winButton();
        }
};

class macFactory : public GUIFactory {
    public:
        Button* createButton(){
            return new macButton();
        }
};

void clientCode (GUIFactory* factory){
    Button* btn = factory->createButton();
    btn->paint();
}

int main(){
    GUIFactory* factory;

    factory = new winFactory();
    clientCode(factory);

    factory = new macFactory();
    clientCode(factory);

    return 0;
}